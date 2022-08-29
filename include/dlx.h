#ifndef DLX_H
#define DLX_H

#include <stack>
#include <vector>

#include "linked_matrix.h"

using namespace std;

enum class RC { row, column };
struct RC_Item {
  Node *node;
  RC type;
};

typedef stack<RC_Item> RC_Stack;

typedef stack<RC_Stack> H_Stack;

bool DLX(Matrix &matrix, vector<int> &solution, vector<int> &global_solution,
         H_Stack &history);
Column *choose_column(Matrix &matrix);
void update(Matrix &matrix, vector<int> &solution, H_Stack &history, Node *row);
void downdate(Matrix &matrix, vector<int> &solution, H_Stack &history);

tuple<bool, int, vector<int>>
FindLeastPiecesToCoverMap(const vector<vector<bool>> &map_matrix,
                          int rows_count, int cols_count);

#endif
