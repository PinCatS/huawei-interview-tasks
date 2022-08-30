#include <iostream>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

#include "dlx.h"
#include "linked_matrix.h"
#include "map_solver.h"

#define MAX_MAP_SIDE_LEN 30
#define MAX_PIECES_COUNT 100

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

bool IsValidCoordinates(int map_width, int map_height,
                        const tuple<int, int, int, int> &coordinates) {
  auto [x1, y1, x2, y2] = coordinates;

  if (x1 < 0 || x1 >= x2 || x1 > map_width) {
    return false;
  }

  if (y1 < 0 || y1 >= y2 || y1 > map_height) {
    return false;
  }

  return true;
}

int main() {
  int count = ReadTestCasesCount();

  if (count <= 0) {
    cout << "Number of test cases is either zero or invalid: "s << count
         << endl;
    return -1;
  }

  vector<tuple<int, int, int, int>> pieces;
  for (int i = 0; i < count; ++i) {
    auto [map_width, map_height, pieces_count] = ReadWidthHeighAndPiecesCount();

    if (map_width < 1 || map_width > MAX_MAP_SIDE_LEN) {
      cerr << "Invalid map width: "s << map_width
           << ". Should be in the range [1, "s << MAX_MAP_SIDE_LEN << "]."s
           << endl;
      return -1;
    }

    if (map_height < 1 || map_height > MAX_MAP_SIDE_LEN) {
      cerr << "Invalid map height: "s << map_height
           << ". Should be in the range [1, "s << MAX_MAP_SIDE_LEN << "]."s
           << endl;
      return -1;
    }

    if (pieces_count < 1 || pieces_count > MAX_PIECES_COUNT) {
      cerr << "Invalid pieces count: "s << pieces_count
           << ". Should be in the range [1, "s << MAX_PIECES_COUNT << "]."s
           << endl;
      return -1;
    }

    for (int j = 0; j < pieces_count; ++j) {
      const tuple<int, int, int, int> &coordinates = ReadPieceCoordinates();

      if (!IsValidCoordinates(map_width, map_height, coordinates)) {
        auto [x1, y1, x2, y2] = coordinates;
        cerr << "Invalid coordinates: ("s << x1 << ", "s << y1 << ") ("s << x2
             << ", "s << y2 << ")"s
             << ". Should be (0 <= x1 < x2 <= "s << map_width
             << ", 0 <= y1 < y2 <= "s << map_height << ")"s << endl;
        return -1;
      }
      pieces.push_back(coordinates);
    }

    const vector<vector<bool>> map_matrix =
        map_solver_huawei::BuildBoolMatrix(map_width, map_height, pieces);
    const vector<int> &pieces_ids =
        map_solver_huawei::FindLeastPiecesToCoverMap(map_matrix, pieces.size(),
                                                     map_width * map_height);

    int result = (pieces_ids.empty()) ? -1 : pieces_ids.size();
    cout << result << endl;
    pieces.clear();
  }
}
