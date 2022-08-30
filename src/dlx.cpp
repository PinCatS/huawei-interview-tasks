#include "dlx.h"

namespace dlx_huawei {

/**
 * Implementation of the Knuth's AlgorithmX using DancingLinks technique.
 *
 * DLX doesn't stop as soon as it find first solution and
 * continues to search for all possible keeping track local solutions
 * and updating the best one - least number of subsets required to solve exact
 * cover problem.
 *
 * @param matrix - boolean double linked list matrix
 * @param solution - stores local solution
 * @param global_solution - stores best solution (minimum number of subsets that
 * solve exact cover)
 * @param history
 * @return true if solution found and false if it doesn't exist
 */
bool DLX(Matrix &matrix, vector<unsigned int> &solution,
         vector<unsigned int> &global_solution, HistoryStack &history) {
  Column *column = choose_column(matrix);
  // matrix is empty => solution successfully found
  if (column == NULL) {
    return true;
  }
  for (Node *row = column->down(); row != static_cast<Node *>(column);
       row = row->down()) {
    update(matrix, solution, history, row);
    if (DLX(matrix, solution, global_solution, history)) {
      // Solution found, check if it is the first one or if we need to update
      // the best one
      if (global_solution.empty() || global_solution.size() > solution.size()) {
        global_solution = solution;
      }
    }
    // Backtrack in any case
    restore(matrix, solution, history);
  }
  // no solution exists
  return false;
}

/**
 * Chooses column deterministically.
 *
 * To optimize performance for some cases the column
 * with the least number of 1's - hence nodes is picked.
 *
 * Time complexity: O(N) where N is a number of columns
 */
Column *choose_column(Matrix &matrix) {
  if (matrix.is_empty())
    return NULL;

  Column *cur_column = static_cast<Column *>(matrix.head()->right());
  Column *min_size_column = cur_column;

  while (cur_column != matrix.head()) {
    if (cur_column->size() < min_size_column->size()) {
      min_size_column = cur_column;
    }
    cur_column = static_cast<Column *>(cur_column->right());
  }
  return min_size_column;
}

/**
 * Includes row into a partial solution and removes rows and columns.
 *
 * Under all columns where there are 1's at that row remove all row
 * where there are 1's. Remove the columns.
 *
 * Time complexity: O(N*M) where N - number of rows, M - number of columns.
 * It is the worst case when all matrix is 1's.
 */
void update(Matrix &matrix, vector<unsigned int> &solution,
            HistoryStack &history, Node *row) {

  solution.push_back(row->row_id());

  RowColumnStack temp_stack;
  RowColumnItem temp_item;

  // Remove the columns where there are nodes (1's)
  for (Node *i = row->right(); i != row; i = i->right()) {
    // Remove all rows where there are nodes (1's)
    for (Node *j = i->up(); j != i; j = j->up()) {
      if (j->column() == j)
        continue;
      matrix.remove_row(j);
      temp_item.node = j;
      temp_item.type = RowColumn::row;
      temp_stack.push(temp_item);
    }
    matrix.remove_column(i);
    temp_item.node = i;
    temp_item.type = RowColumn::column;
    temp_stack.push(temp_item);
  }

  // Remove all rows under the column that is left
  for (Node *j = row->up(); j != row; j = j->up()) {
    if (j->column() == j)
      continue;
    matrix.remove_row(j);
    temp_item.node = j;
    temp_item.type = RowColumn::row;
    temp_stack.push(temp_item);
  }
  matrix.remove_column(row);
  temp_item.node = row;
  temp_item.type = RowColumn::column;
  temp_stack.push(temp_item);

  history.push(temp_stack);
}

/**
 * Restores rows and columns while backtracking and pops back the solution
 * candidate.
 *
 * History stack lets to restore the updates in reverse order that is required
 * for dlx.
 *
 * @param history - contains the history what row/column nodes were removed
 */
void restore(Matrix &matrix, vector<unsigned int> &solution,
             HistoryStack &history) {
  if (history.empty()) {
    return;
  }
  solution.pop_back();
  RowColumnStack last = history.top();
  RowColumnItem item;
  while (!last.empty()) {
    item = last.top();
    if (item.type == RowColumn::row) {
      matrix.restore_row(item.node);
    } else if (item.type == RowColumn::column) {
      matrix.restore_column(item.node);
    }
    last.pop();
  }
  history.pop();
}

} // namespace dlx_huawei
