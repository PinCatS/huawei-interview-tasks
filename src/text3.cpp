#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Column;

class Node {
  int _row_id;
  Column* _column;
  Node* _right;
  Node* _left;
  Node* _up;
  Node* _down;

 public:
  Node(int row_id = -1, Column* column = NULL, Node* right = NULL,
       Node* left = NULL, Node* up = NULL, Node* down = NULL)
      : _row_id(row_id),
        _column(column),
        _right(right),
        _left(left),
        _up(up),
        _down(down) {}

  void set_row_id(int id) { _row_id = id; }
  int row_id() { return _row_id; }
  void set_column(Column* column) { _column = column; }
  Column* column() const { return _column; }
  Node* right() const { return _right; }
  Node* left() const { return _left; }
  Node* up() const { return _up; }
  Node* down() const { return _down; }
  void set_right(Node* right) { _right = right; }
  void set_left(Node* left) { _left = left; }
  void set_up(Node* up) { _up = up; }
  void set_down(Node* down) { _down = down; }
};

class Column : public Node {
  int _size;

 public:
  Column(int size = 0) : Node(-1, this), _size(size) {}

  int size() const { return _size; }
  void set_size(int size) { _size = size; }
  void add_to_size(int n) { _size += n; }
};

class Matrix {
  Node* _root;

 public:
  Matrix();
  Matrix(const vector<vector<bool>>& matrix, int m, int n);
  Node* head() const;

  bool is_empty() const;
  int number_of_rows() const;
  void remove_row(Node* node);
  void restore_row(Node* node);
  void remove_column(Node* node);
  void restore_column(Node* node);

  ~Matrix();
};

Matrix::Matrix() : _root(new Node()) {
  _root->set_right(_root);
  _root->set_left(_root);
}

Matrix::Matrix(const vector<vector<bool>>& matrix, int m, int n)
    : _root(new Node()) {
  if (m == 0 || n == 0) {
    return;
  }

  // create first column
  Node* cur_column = new Column(0);
  _root->set_right(cur_column);
  cur_column->set_left(_root);

  // create column header objects
  for (int j = 1; j < n; j++) {
    Node* new_column = new Column(0);
    cur_column->set_right(new_column);
    new_column->set_left(cur_column);
    cur_column = cur_column->right();
  }
  cur_column->set_right(_root);
  _root->set_left(cur_column);

  // initialize m x n array of Node pointers
  vector<vector<Node*>> ptr_matrix(m, vector<Node*>(n, NULL));

  // create nodes of Matrix, referenced by pointers in ptr_matrix
  // also link the nodes vertically
  Node* tmp;
  cur_column = _root->right();
  // j = column of matrix, i = row of matrix
  for (int j = 0; j < n; ++j, cur_column = cur_column->right()) {
    tmp = cur_column;
    for (int i = 0; i < m; ++i) {
      if (matrix[i][j]) {
        ptr_matrix[i][j] = new Node(i, static_cast<Column*>(cur_column));
        ptr_matrix[i][j]->set_up(tmp);
        tmp->set_down(ptr_matrix[i][j]);
        tmp = ptr_matrix[i][j];
        (static_cast<Column*>(cur_column))->add_to_size(1);
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
    if (first != NULL) {  // if row i is not a zero row
      prev->set_right(first);
      first->set_left(prev);
    }
  }
}

Node* Matrix::head() const {
  return _root;
}

bool Matrix::is_empty() const {
  return _root->right() == _root && _root->left() == _root;
}

int Matrix::number_of_rows() const {
  int max_column_size = 0;
  for (Node* node = _root->right(); node != _root; node = node->right()) {
    int column_size = static_cast<Column*>(node)->size();
    if (column_size > max_column_size) {
      max_column_size = column_size;
    }
  }
  return max_column_size;
}

void Matrix::remove_row(Node* node) {
  if (node == NULL || node == _root || node->column() == node) {
    return;
  }

  Node* cur = node;

  do {
    // remove cur by dancing with the up/down pointers
    cur->down()->set_up(cur->up());
    cur->up()->set_down(cur->down());

    cur->column()->add_to_size(-1);
    cur = cur->right();
  } while (cur != node);  // stop when we're back where we started
}

void Matrix::restore_row(Node* node) {
  Node* cur = node;

  do {
    cur->up()->set_down(cur);  // connect row back
    cur->down()->set_up(cur);  // into the matrix
    cur->column()->add_to_size(1);
    cur = cur->left();
  } while (cur != node);
}

void Matrix::remove_column(Node* node) {
  if (node == NULL || node == _root) {
    return;
  }

  Node* cur = node;
  do {
    cur->left()->set_right(cur->right());
    cur->right()->set_left(cur->left());
    cur = cur->up();
  } while (cur != node);  // stop when we're back where we started
}

void Matrix::restore_column(Node* node) {
  Node* cur = node;
  do {
    cur->right()->set_left(cur);
    cur->left()->set_right(cur);
    cur = cur->down();
  } while (cur != node);
}

Matrix::~Matrix() {
  Node *cur_col, *cur_node, *node_to_delete;
  // a iterates through the column headers horizontally
  // b iterates through each column vertically
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

enum class RC { row, column };
struct RC_Item {
  Node* node;
  RC type;
};

typedef stack<RC_Item> RC_Stack;

typedef stack<RC_Stack> H_Stack;

bool DLX(Matrix& matrix, vector<int>& solution, vector<int>& global_solution,
         H_Stack& history);
Column* choose_column(Matrix& matrix);
void update(Matrix& matrix, vector<int>& solution, H_Stack& history, Node* row);
void downdate(Matrix& matrix, vector<int>& solution, H_Stack& history);

tuple<bool, int, vector<int>> FindLeastPiecesToCoverMap(
    const vector<vector<bool>>& map_matrix, int rows_count, int cols_count) {
  Matrix matrix(map_matrix, rows_count, cols_count);
  H_Stack history;
  vector<int> solution, global_solution;
  DLX(matrix, solution, global_solution, history);
  int solution_exists = (global_solution.empty()) ? false : true;
  return {solution_exists, global_solution.size(), global_solution};
}

Column* choose_column(Matrix& matrix) {
  if (matrix.is_empty())
    return NULL;

  Column* cur_column = static_cast<Column*>(matrix.head()->right());
  Column* min_size_column = cur_column;

  while (cur_column != matrix.head()) {
    if (cur_column->size() < min_size_column->size()) {
      min_size_column = cur_column;
    }
    cur_column = static_cast<Column*>(cur_column->right());
  }
  return min_size_column;
}

bool DLX(Matrix& matrix, vector<int>& solution, vector<int>& global_solution,
         H_Stack& history) {
  Column* column = choose_column(matrix);
  // matrix is empty => solution successfully found
  if (column == NULL) {
    return true;
  }
  for (Node* row = column->down(); row != static_cast<Node*>(column);
       row = row->down()) {
    update(matrix, solution, history, row);
    if (DLX(matrix, solution, global_solution, history)) {
      if (global_solution.empty() || global_solution.size() > solution.size()) {
        global_solution = solution;
      }
    }
    downdate(matrix, solution, history);
  }
  // no solution exists
  return false;
}

void update(Matrix& matrix, vector<int>& solution, H_Stack& history,
            Node* row) {

  solution.push_back(row->row_id());

  RC_Stack temp_stack;
  RC_Item temp_item;

  for (Node* i = row->right(); i != row; i = i->right()) {
    for (Node* j = i->up(); j != i; j = j->up()) {
      if (j->column() == j)
        continue;
      matrix.remove_row(j);
      temp_item.node = j;
      temp_item.type = RC::row;
      temp_stack.push(temp_item);
    }
    matrix.remove_column(i);
    temp_item.node = i;
    temp_item.type = RC::column;
    temp_stack.push(temp_item);
  }

  for (Node* j = row->up(); j != row; j = j->up()) {
    if (j->column() == j)
      continue;
    matrix.remove_row(j);
    temp_item.node = j;
    temp_item.type = RC::row;
    temp_stack.push(temp_item);
  }
  matrix.remove_column(row);
  temp_item.node = row;
  temp_item.type = RC::column;
  temp_stack.push(temp_item);

  history.push(temp_stack);
}

void downdate(Matrix& matrix, vector<int>& solution, H_Stack& history) {
  if (history.empty()) {
    return;
  }
  solution.pop_back();
  RC_Stack last = history.top();
  RC_Item it;
  while (!last.empty()) {
    it = last.top();
    if (it.type == RC::row) {
      matrix.restore_row(it.node);
    } else if (it.type == RC::column) {
      matrix.restore_column(it.node);
    }
    last.pop();
  }
  history.pop();
}

vector<vector<bool>> BuildMatrix(
    int width, int height, const vector<tuple<int, int, int, int>>& pieces) {
  int number_of_columns = width * height;
  vector<vector<bool>> matrix(pieces.size(),
                              vector<bool>(number_of_columns, 0));

  for (size_t k = 0; k < pieces.size(); ++k) {
    auto [x1, y1, x2, y2] = pieces[k];
    // cout << "Piece: "s << x1 << " "s << y1 << " "s << x2 << " "s << y2 << endl;
    for (int i = y1; i < y2; ++i) {
      for (int j = x1; j < x2; ++j) {
        // cout << i << " "s << j << " "s << i * width + j << endl;
        matrix[k][i * width + j] = 1;
      }
      //   cout << endl;
    }
  }

  return matrix;
}

/**
 * Reading int from the in stream.
 */
int ReadTestCasesCount() {
  int count;
  cin >> count;
  return count;
}

tuple<int, int, int> ReadWidthHeighAndPiecesCount() {
  int width, height, count;
  cin >> width >> height >> count;
  return {width, height, count};
}

tuple<int, int, int, int> ReadPieceCoordinates() {
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  return {x1, y1, x2, y2};
}

int main() {
  int count = ReadTestCasesCount();
  vector<tuple<int, int, int, int>> pieces;
  for (int i = 0; i < count; ++i) {
    auto [map_width, map_height, pieces_count] = ReadWidthHeighAndPiecesCount();
    for (int j = 0; j < pieces_count; ++j) {
      pieces.push_back(ReadPieceCoordinates());
    }
    const vector<vector<bool>> map_matrix =
        BuildMatrix(map_width, map_height, pieces);
    const auto& [solution_exists, least_pieces, pieces_ids] =
        FindLeastPiecesToCoverMap(map_matrix, pieces.size(),
                                  map_width * map_height);

    int result = (solution_exists) ? least_pieces : -1;
    cout << result << endl;
    pieces.clear();
  }
}
