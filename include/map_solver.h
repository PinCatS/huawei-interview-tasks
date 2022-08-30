#ifndef MAP_SOLVER_H
#define MAP_SOLVER_H

#include <tuple>
#include <vector>

#include "dlx.h"
#include "linked_matrix.h"

namespace map_solver_huawei {

using std::vector;

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
                const vector<std::tuple<int, int, int, int>> &pieces);

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
                                      int rows_count, int cols_count);

} // namespace map_solver_huawei
#endif
