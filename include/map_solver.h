#ifndef MAP_SOLVER_H
#define MAP_SOLVER_H

#include <vector>

#include <tuple>

#include "dlx.h"
#include "linked_matrix.h"

using namespace std;

vector<vector<bool>>
BuildMatrix(int width, int height,
            const vector<tuple<int, int, int, int>> &pieces);

tuple<bool, int, vector<int>>
FindLeastPiecesToCoverMap(const vector<vector<bool>> &map_matrix,
                          int rows_count, int cols_count);

#endif
