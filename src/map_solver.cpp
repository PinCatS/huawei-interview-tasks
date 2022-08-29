#include "map_solver.h"

vector<vector<bool>>
BuildMatrix(int width, int height,
            const vector<tuple<int, int, int, int>> &pieces) {
  int number_of_columns = width * height;
  vector<vector<bool>> matrix(pieces.size(),
                              vector<bool>(number_of_columns, 0));

  for (size_t k = 0; k < pieces.size(); ++k) {
    auto [x1, y1, x2, y2] = pieces[k];
    for (int i = y1; i < y2; ++i) {
      for (int j = x1; j < x2; ++j) {
        matrix[k][i * width + j] = 1;
      }
    }
  }

  return matrix;
}

tuple<bool, int, vector<int>>
FindLeastPiecesToCoverMap(const vector<vector<bool>> &map_matrix,
                          int rows_count, int cols_count) {
  Matrix matrix(map_matrix, rows_count, cols_count);
  H_Stack history;
  vector<int> solution, global_solution;
  DLX(matrix, solution, global_solution, history);
  int solution_exists = (global_solution.empty()) ? false : true;
  return {solution_exists, global_solution.size(), global_solution};
}
