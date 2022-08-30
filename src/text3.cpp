#include <iostream>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

#include "dlx.h"
#include "linked_matrix.h"
#include "map_solver.h"

using namespace std;

unsigned int ReadTestCasesCount() {
  unsigned int count;
  cin >> count;
  return count;
}

tuple<unsigned int, unsigned int, unsigned int> ReadWidthHeighAndPiecesCount() {
  unsigned int width, height, count;
  cin >> width >> height >> count;
  return {width, height, count};
}

tuple<unsigned int, unsigned int, unsigned int, unsigned int>
ReadPieceCoordinates() {
  unsigned int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  return {x1, y1, x2, y2};
}

int main() {
  unsigned int count = ReadTestCasesCount();

  if (count <= 0) {
    cout << "Number of test cases is either zero or invalid: "s << count
         << endl;
  }

  vector<tuple<unsigned int, unsigned int, unsigned int, unsigned int>> pieces;
  for (unsigned int i = 0; i < count; ++i) {
    auto [map_width, map_height, pieces_count] = ReadWidthHeighAndPiecesCount();
    for (unsigned int j = 0; j < pieces_count; ++j) {
      pieces.push_back(ReadPieceCoordinates());
    }
    const vector<vector<bool>> map_matrix =
        map_solver_huawei::BuildBoolMatrix(map_width, map_height, pieces);
    const vector<unsigned int> &pieces_ids =
        map_solver_huawei::FindLeastPiecesToCoverMap(map_matrix, pieces.size(),
                                                     map_width * map_height);

    int result = (pieces_ids.empty()) ? -1 : pieces_ids.size();
    cout << result << endl;
    pieces.clear();
  }
}
