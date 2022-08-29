#include "dlx.h"

bool DLX(Matrix &matrix, vector<int> &solution, vector<int> &global_solution,
         H_Stack &history) {
  Column *column = choose_column(matrix);
  // matrix is empty => solution successfully found
  if (column == NULL) {
    return true;
  }
  for (Node *row = column->down(); row != static_cast<Node *>(column);
       row = row->down()) {
    update(matrix, solution, history, row);
    if (DLX(matrix, solution, global_solution, history)) {
      if (global_solution.empty() || global_solution.size() > solution.size()) {
        global_solution = solution;
      }
    }
    restore(matrix, solution, history);
  }
  // no solution exists
  return false;
}

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

void update(Matrix &matrix, vector<int> &solution, H_Stack &history,
            Node *row) {

  solution.push_back(row->row_id());

  RC_Stack temp_stack;
  RC_Item temp_item;

  for (Node *i = row->right(); i != row; i = i->right()) {
    for (Node *j = i->up(); j != i; j = j->up()) {
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

  for (Node *j = row->up(); j != row; j = j->up()) {
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

void restore(Matrix &matrix, vector<int> &solution, H_Stack &history) {
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
