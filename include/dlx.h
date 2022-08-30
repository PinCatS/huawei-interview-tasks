#ifndef DLX_H
#define DLX_H

#include <stack>
#include <tuple>
#include <vector>

#include "linked_matrix.h"

namespace dlx_huawei {

using std::vector;

using namespace lkedmatrix_huawei;

/**
 * Represents either "row" or "column"
 * Helps to remember what was removed
 * to be able to restore when we backtrack.
 */
enum class RowColumn { row, column };

/**
 * Item to encapsulate node information to
 * use later for restoring during backtracking.
 */
struct RowColumnItem {
  Node *node;
  RowColumn type;
};

/**
 * Stacks all nodes that was updated (removed).
 */
typedef std::stack<RowColumnItem> RowColumnStack;

/**
 * Stacks the rows/columns that are removed
 * during recursive dfs traversal to restore
 * them back while backtracking.
 */
typedef std::stack<RowColumnStack> HistoryStack;

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
bool DLX(Matrix &matrix, vector<int> &solution, vector<int> &global_solution,
         HistoryStack &history);

/**
 * Chooses column deterministically.
 *
 * To optimize performance for some cases the column
 * with the least number of 1's - hence nodes is picked.
 *
 * Time complexity: O(N) where N is a number of columns
 */
Column *choose_column(Matrix &matrix);

/**
 * Includes row into a partial solution and removes rows and columns.
 *
 * Under all columns where there are 1's at that row remove all row
 * where there are 1's. Remove the columns.
 *
 * Time complexity: O(N*M) where N - number of rows, M - number of columns.
 * It is the worst case when all matrix is 1's.
 */
void update(Matrix &matrix, vector<int> &solution, HistoryStack &history,
            Node *row);

/**
 * Restores rows and columns while backtracking and pops back the solution
 * candidate.
 *
 * History stack lets to restore the updates in exact reverse order that is
 * required for dlx.
 *
 * @param history - contains the history what row/column nodes were removed
 */
void restore(Matrix &matrix, vector<int> &solution, HistoryStack &history);

} // namespace dlx_huawei
#endif
