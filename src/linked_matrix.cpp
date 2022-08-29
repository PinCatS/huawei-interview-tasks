#include "linked_matrix.h"

/**
 * Default constructor that has only root node
 * which points to itself.
 */
Matrix::Matrix() : _root(new Node()) {
  _root->set_right(_root);
  _root->set_left(_root);
}

/**
 * @brief Construct that builds the Matrix from array-based boolean matrix
 */
Matrix::Matrix(const vector<vector<bool>> &matrix, int m, int n)
    : _root(new Node()) {
  if (m == 0 || n == 0) {
    return;
  }

  // create first column
  Node *cur_column = new Column(0);
  _root->set_right(cur_column);
  cur_column->set_left(_root);

  // create column header objects
  for (int j = 1; j < n; j++) {
    Node *new_column = new Column(0);
    cur_column->set_right(new_column);
    new_column->set_left(cur_column);
    cur_column = cur_column->right();
  }
  cur_column->set_right(_root);
  _root->set_left(cur_column);

  // initialize m x n array of Node pointers
  vector<vector<Node *>> ptr_matrix(m, vector<Node *>(n, NULL));

  // create nodes of Matrix, referenced by pointers in ptr_matrix
  // also link the nodes vertically
  Node *tmp;
  cur_column = _root->right();
  // j = column of matrix, i = row of matrix
  for (int j = 0; j < n; ++j, cur_column = cur_column->right()) {
    tmp = cur_column;
    for (int i = 0; i < m; ++i) {
      if (matrix[i][j]) {
        ptr_matrix[i][j] = new Node(i, static_cast<Column *>(cur_column));
        ptr_matrix[i][j]->set_up(tmp);
        tmp->set_down(ptr_matrix[i][j]);
        tmp = ptr_matrix[i][j];
        (static_cast<Column *>(cur_column))->add_to_size(1);
      } else
        ptr_matrix[i][j] = NULL;
    }
    cur_column->set_up(tmp);
    tmp->set_down(cur_column);
  }

  // ignore zero rows at the bottom of the matrix
  int i;
  bool zero_row;
  for (i = m - 1; i >= 0; --i) {
    zero_row = 1;
    for (int j = 0; j < n; ++j) {
      if (matrix[i][j]) {
        zero_row = 0;
        break;
      }
    }
    if (!zero_row)
      break;
  }

  // link the nodes horizontally
  Node *first, *prev;
  // i = row, j = column
  for (; i >= 0; --i) {
    first = NULL;
    for (int j = 0; j < n; ++j) {
      // find first non-zero matrix entry in row i,
      // and make 'first' point to the corresponding node
      if (ptr_matrix[i][j] != NULL) {
        if (first == NULL) {
          first = ptr_matrix[i][j];
        } else {
          prev->set_right(ptr_matrix[i][j]);
          ptr_matrix[i][j]->set_left(prev);
        }
        prev = ptr_matrix[i][j];
      }
    }
    if (first != NULL) { // if row i is not a zero row
      prev->set_right(first);
      first->set_left(prev);
    }
  }
}

/**
 * Returns the head of the Matrix (root node)
 */
Node *Matrix::head() const { return _root; }

bool Matrix::is_empty() const {
  return _root->right() == _root && _root->left() == _root;
}

/**
 * Returns number of rows by running through columns
 * and getting the max number of nodes.
 *
 * Time complexity is: O(N) where N is a number of columns.
 */
int Matrix::number_of_rows() const {
  int max_column_size = 0;
  for (Node *node = _root->right(); node != _root; node = node->right()) {
    int column_size = static_cast<Column *>(node)->size();
    if (column_size > max_column_size) {
      max_column_size = column_size;
    }
  }
  return max_column_size;
}

/**
 * Removes row to which the input node represents.
 *
 * Note: Original links are stayed unchanged.
 * That lets to restore the raw afterward.
 *
 * Here you can see the code that is called (Dancing Links)
 */
void Matrix::remove_row(Node *node) {
  if (node == NULL || node == _root || node->column() == node) {
    return;
  }

  Node *cur = node;

  do {
    // remove cur by dancing with the up/down pointers
    cur->down()->set_up(cur->up());
    cur->up()->set_down(cur->down());

    cur->column()->add_to_size(-1);
    cur = cur->right();
  } while (cur != node); // stop when we're back where we started
}

/**
 * Restores the row.
 *
 * Note: The code relies on the fact that remove_row
 * doesn't change the original links of the removed nodes.
 */
void Matrix::restore_row(Node *node) {
  Node *cur = node;

  do {
    cur->up()->set_down(cur); // connect row back
    cur->down()->set_up(cur); // into the matrix
    cur->column()->add_to_size(1);
    cur = cur->left();
  } while (cur != node);
}

/**
 * Removes column to which the input node represents.
 *
 * Note: Original links are stayed unchanged.
 * That lets to restore the column afterward.
 */
void Matrix::remove_column(Node *node) {
  if (node == NULL || node == _root) {
    return;
  }

  Node *cur = node;
  do {
    cur->left()->set_right(cur->right());
    cur->right()->set_left(cur->left());
    cur = cur->up();
  } while (cur != node); // stop when we're back where we started
}

/**
 * Restores the column.
 *
 * Note: The code relies on the fact that remove_column
 * doesn't change the original links of the removed nodes.
 */
void Matrix::restore_column(Node *node) {
  Node *cur = node;
  do {
    cur->right()->set_left(cur);
    cur->left()->set_right(cur);
    cur = cur->down();
  } while (cur != node);
}

/**
 * Frees the allocated resources of the matrix.
 */
Matrix::~Matrix() {
  Node *cur_col, *cur_node, *node_to_delete;
  // cur_col iterates through the column headers horizontally
  // cur_node iterates through each column vertically
  cur_col = _root->right();
  while (cur_col != _root) {
    cur_node = cur_col->down();
    while (cur_node != cur_col) {
      node_to_delete = cur_node;
      cur_node = cur_node->down();
      delete node_to_delete;
    }
    node_to_delete = cur_col;
    cur_col = cur_col->right();
    delete node_to_delete;
  }
  delete _root;
}
