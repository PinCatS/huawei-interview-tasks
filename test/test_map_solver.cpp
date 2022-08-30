#include <assert.h>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

#include "map_solver.h"

#define NUM_TESTS 6

using namespace std::literals::string_literals;
using std::cout;
using std::endl;
using std::string;
using std::tuple;
using std::vector;
using namespace map_solver_huawei;
/****************************************************************************************************
 *                                   helper function
 * **************************************************************************************************/
vector<unsigned int> solve(
    unsigned int width, unsigned int height,
    const vector<tuple<unsigned int, unsigned int, unsigned int, unsigned int>>
        &pieces) {
  const vector<vector<bool>> map_matrix =
      BuildBoolMatrix(width, height, pieces);
  return FindLeastPiecesToCoverMap(map_matrix, pieces.size(), width * height);
}

vector<tuple<unsigned int, unsigned int, unsigned int, unsigned int>>
generate_pieces(unsigned int map_width, unsigned int map_height,
                unsigned int max_pieces_number) {
  std::random_device generator;
  std::uniform_int_distribution<unsigned int> distribution_height(1,
                                                                  map_height);
  std::uniform_int_distribution<unsigned int> distribution_width(1, map_width);

  vector<tuple<unsigned int, unsigned int, unsigned int, unsigned int>> pieces;
  for (unsigned int i = 1; i <= max_pieces_number; ++i) {
    unsigned int width = distribution_width(generator);
    unsigned int height = distribution_height(generator);
    std::uniform_int_distribution<unsigned int> distribution_x(0, map_width -
                                                                      width);
    std::uniform_int_distribution<unsigned int> distribution_y(0, map_height -
                                                                      height);
    unsigned int x = distribution_x(generator);
    unsigned int y = distribution_y(generator);
    pieces.push_back(std::make_tuple(x, y, x + width, y + height));
  }

  return pieces;
}
/****************************************************************************************************
 *                                   IMPLEMENTATION OF TESTS
 * **************************************************************************************************/
void TestMapWithMinWidthAndHeight() {
  cout << "TestMapWithMinWidthAndHeight"s << endl;
  unsigned int map_width = 1;
  unsigned int map_height = 1;
  vector<tuple<unsigned int, unsigned int, unsigned int, unsigned int>> pieces =
      {{0, 0, 1, 1}};

  const vector<unsigned int> &pieces_ids = solve(map_width, map_height, pieces);

  assert((pieces_ids.size() == 1));
  assert((pieces_ids[0] == 0));
}

void Test2x2Map() {
  cout << "Test2x2Map"s << endl;
  unsigned int map_width = 2;
  unsigned int map_height = 2;

  // one piece that cover all map
  vector<tuple<unsigned int, unsigned int, unsigned int, unsigned int>> pieces =
      {{0, 0, 2, 2}};
  vector<unsigned int> expected_pieces = {0};

  vector<unsigned int> pieces_ids = solve(map_width, map_height, pieces);

  assert((pieces_ids.size() == 1));
  assert((pieces_ids == expected_pieces));

  // two pieces that cover map
  pieces = {{0, 0, 2, 1}, {0, 1, 2, 2}};
  expected_pieces = {0, 1};

  pieces_ids = solve(map_width, map_height, pieces);

  assert((pieces_ids.size() == 2));
  assert((pieces_ids == expected_pieces));

  // two pieces that overlap but each of them covers the entire map
  pieces = {{0, 0, 2, 2}, {0, 0, 2, 2}};
  expected_pieces = {0};

  pieces_ids = solve(map_width, map_height, pieces);

  assert((pieces_ids.size() == 1));
  assert((pieces_ids == expected_pieces));

  // four pieces that cover map and two pieces that cover map
  pieces = {{0, 0, 1, 1}, {0, 0, 2, 1}, {1, 0, 2, 1},
            {0, 1, 2, 2}, {0, 1, 1, 2}, {1, 1, 2, 2}};
  expected_pieces = {1, 3}; // least number of pieces that solve

  pieces_ids = solve(map_width, map_height, pieces);

  assert((pieces_ids.size() == 2));
  assert((pieces_ids == expected_pieces));

  // two pieces that not overlap and not cover map
  pieces = {{0, 0, 1, 1}, {1, 1, 2, 2}};

  pieces_ids = solve(map_width, map_height, pieces);

  assert((pieces_ids.size() == 0));

  // two pieces that overlap and don't cover map
  pieces = {{0, 0, 2, 1}, {0, 0, 1, 2}};

  pieces_ids = solve(map_width, map_height, pieces);

  assert((pieces_ids.size() == 0));
}

void Test3x3MapForOverlapCase() {
  cout << "Test3x3MapForOverlapCase"s << endl;
  unsigned int map_width = 3;
  unsigned int map_height = 3;

  // two pieces that cover map together but overlap need
  vector<tuple<unsigned int, unsigned int, unsigned int, unsigned int>> pieces =
      {{0, 0, 2, 2}, {0, 1, 2, 3}};

  vector<unsigned int> pieces_ids = solve(map_width, map_height, pieces);

  assert((pieces_ids.size() == 0));
}

void TestMapDifferentSizes() {
  cout << "TestMapDifferentSizes"s << endl;
  unsigned int map_width = 5;
  unsigned int map_height = 5;

  // one piece covers entire map
  vector<tuple<unsigned int, unsigned int, unsigned int, unsigned int>> pieces =
      {{0, 0, 5, 5}};
  vector<unsigned int> expected_pieces = {0};

  vector<unsigned int> pieces_ids = solve(map_width, map_height, pieces);

  assert((pieces_ids.size() == 1));
  assert((pieces_ids == expected_pieces));

  // no solution
  pieces = {{0, 0, 3, 5}, {2, 0, 5, 5}};

  pieces_ids = solve(map_width, map_height, pieces);

  assert((pieces_ids.size() == 0));

  // best solution
  map_width = 30;
  map_height = 30;
  pieces = {{0, 0, 30, 10},
            {0, 10, 30, 20},
            {0, 20, 30, 30},
            {0, 0, 15, 30},
            {15, 0, 30, 30}};
  expected_pieces = {3, 4};

  pieces_ids = solve(map_width, map_height, pieces);

  assert((pieces_ids.size() == 2));
  assert((pieces_ids == expected_pieces));
}

void TestMapSolverRandom() {
  cout << "TestMapSolverRandom"s << endl;

  unsigned int map_max_side_len = 30;
  unsigned int max_pieces = 100;
  unsigned int number_of_runs = 100;

  std::random_device generator;
  std::uniform_int_distribution<int> distribution_map(1, map_max_side_len);

  for (unsigned int i = 0; i < number_of_runs; ++i) {
    unsigned int map_width = distribution_map(generator);
    unsigned int map_height = distribution_map(generator);
    vector<tuple<unsigned int, unsigned int, unsigned int, unsigned int>>
        pieces = generate_pieces(map_width, map_height, max_pieces - 1);
    // push back last piece that cover map to be able to assert
    pieces.push_back(std::make_tuple(0, 0, map_width, map_height));

    vector<unsigned int> pieces_ids = solve(map_width, map_height, pieces);

    assert((pieces_ids.size() == 1));
  }
}

void TestMapSolverTime() {
  cout << "TestMapSolverTime"s << endl;
  cout << "There are 100 pieces and map of 30x30" << endl;

  unsigned int map_max_side_len = 30;
  unsigned int max_pieces = 100;
  unsigned int map_width = map_max_side_len;
  unsigned int map_height = map_max_side_len;

  vector<tuple<unsigned int, unsigned int, unsigned int, unsigned int>> pieces =
      generate_pieces(map_width, map_height, max_pieces - 1);
  // push back last piece that cover map to be able to assert
  pieces.push_back(std::make_tuple(0, 0, map_width, map_height));

  std::clock_t start = std::clock();
  vector<unsigned int> pieces_ids = solve(map_width, map_height, pieces);
  assert((pieces_ids.size() == 1));
  std::clock_t end = std::clock();
  std::cout << "Elapsed time = " << 1000.0 * (end - start) / CLOCKS_PER_SEC
            << " ms"
            << " (CPU time)" << endl;
}
/****************************************************************************************************
 *                             END OF IMPLEMENTATION OF TESTS
 * **************************************************************************************************/

typedef void (*PROC)(void);
const PROC tests[NUM_TESTS] = {
    &TestMapWithMinWidthAndHeight,
    &Test2x2Map,
    &Test3x3MapForOverlapCase,
    &TestMapDifferentSizes,
    &TestMapSolverTime,
    &TestMapSolverRandom,
};

// run all tests
int main() {
  bool TESTS[NUM_TESTS];

  // Mark tests that will run
  for (int i = 0; i < NUM_TESTS; ++i) {
    TESTS[i] = false;
  }
  TESTS[NUM_TESTS - 1] = true;

  for (int i = 0; i < NUM_TESTS; ++i) {
    if (TESTS[i]) {
      tests[i]();
      std::cout << "Test " << i + 1 << " passed!" << std::endl;
    }
  }
}
