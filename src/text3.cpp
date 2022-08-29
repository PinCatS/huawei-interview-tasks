#include <iostream>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

#include "dlx.h"
#include "linked_matrix.h"
#include "map_solver.h"

using namespace std;

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
        BuildBoolMatrix(map_width, map_height, pieces);
    const vector<int> &pieces_ids = FindLeastPiecesToCoverMap(
        map_matrix, pieces.size(), map_width * map_height);

    int result = (pieces_ids.empty()) ? -1 : pieces_ids.size();
    cout << result << endl;
    pieces.clear();
  }
}
