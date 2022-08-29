#include "map_solver.h"

namespace map_solver_huawei {
/**
 * Builds boolean matrix for map pieces.
 *
 * Rows represent pieces (its index number)
 * Columns represent points in space.
 *
 * 2d space is flattened to 1d by mapping each point
 * via function i * width + j where i is an Y-axis values
 * and j is an X-axis values.
 *
 * Thus, all space occupied by piece is marked with 1's
 * in the matrix in the row that corresponds to the piece.
 *
 * Time complexity is: O(width*height*N) where N is number of pieces
 * and width, height are the width and height of pieces
 *
 * Space complexity is: width*height*N since we build the matrix.
 */
vector<vector<bool>>
BuildBoolMatrix(int width, int height,
                const vector<std::tuple<int, int, int, int>> &pieces) {
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

/**
 * Searches for least number of pieces that covers entire map
 * without overlapping between each other.
 *
 * The problem is an ExactCover NP-problem that can be solved
 * using Knuth's DLX (AlgorithmX implemented via Dancing Link technique).
 *
 * To map the problem to the ExactCover problem we use rows to represent
 * each piece and we map 2d space of piece point to 1d space unwinding it.
 * (see the description of BuildBoolMatrix on how unwinding is accomplished)
 *
 * Algorithm uses DoubleLinked List Matrix to efficiently store nodes because
 * in most cases data is sparse and only 1's can be stored.
 * It also lets efficiently remove and restore nodes (dancing).
 *
 * @param map_matrix - matrix built by BuildMatrix function (see description
 * above)
 * @param rows_count - corresponds to number of input pieces
 * @param cols_count - corresponds to map width multiplied by map height
 * @return List of pieces ids (least number of pieces)
 */
vector<int> FindLeastPiecesToCoverMap(const vector<vector<bool>> &map_matrix,
                                      int rows_count, int cols_count) {
  lkedmatrix_huawei::Matrix matrix(map_matrix, rows_count, cols_count);
  dlx_huawei::HistoryStack history;
  vector<int> solution, global_solution;
  DLX(matrix, solution, global_solution, history);
  return global_solution;
}

} // namespace map_solver_huawei
