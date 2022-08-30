#include <assert.h>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

#include "greatest_number.h"

#define NUM_TESTS 4

using namespace std::literals::string_literals;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace gn_huawei;

/****************************************************************************************************
 *                                   IMPLEMENTATION OF TESTS
 * **************************************************************************************************/
void TestEmptyListOfNumbers() {
  cout << "TestEmptyListOfNumbers"s << endl;
  vector<unsigned int> numbers;

  int gn = FindGreatestNumber(numbers, 0);
  assert((gn == 0));

  gn = FindGreatestNumber(numbers, 80);
  assert((gn == 0));
}

void TestNumbersAllGreaterThanLimit() {
  cout << "TestNumbersAllGreaterThanLimit"s << endl;
  vector<unsigned int> numbers = {11, 30, 20, 40, 90, 60};

  unsigned int gn = FindGreatestNumber(numbers, 10);
  assert((gn == 0));
}

void TestNumbersWithNonZeroLimit() {
  cout << "TestNumbersWithNonZeroLimit"s << endl;
  vector<unsigned int> numbers = {100, 2};

  unsigned int gn = FindGreatestNumber(numbers, 10);
  assert((gn == 8));

  numbers = {4, 4, 4, 4};
  gn = FindGreatestNumber(numbers, 16);
  assert((gn == 16));

  numbers = {10, 4, 4, 4, 4, 15};
  gn = FindGreatestNumber(numbers, 16);
  assert((gn == 16));

  numbers = {2, 8, 99, 98};
  gn = FindGreatestNumber(numbers, 100);
  assert((gn == 100));

  numbers = {3, 8, 99, 98};
  gn = FindGreatestNumber(numbers, 100);
  assert((gn == 99));
}

/**
 * Test generates random limit, random number of numbers
 * and random numbers itself.
 * To assert that solution was correct, randomly generated
 * count of selected numbers (1, 4). Then the limit is divided
 * to that count to get a number from which we could get either
 * max solution == limit or closest to it in case count is not
 * divided. A number is injected into the randomly generated array
 * to the middle.
 */
void TestRandomNumbersAndLimit() {
  cout << "TestRandomNumbersAndLimit"s << endl;

  int max_numbers_len = 1000;
  int max_limit_and_number = 1000000000;
  std::random_device generator;
  std::uniform_int_distribution<int> distribution_limit_and_number(
      0, max_limit_and_number);
  std::uniform_int_distribution<int> distribution_numbers_len(0,
                                                              max_numbers_len);
  std::uniform_int_distribution<int> distribution_selected_numbers_count(1, 4);

  for (int i = 0; i < 100; ++i) {
    unsigned int rand_limit = distribution_limit_and_number(generator);
    unsigned int numbers_len = distribution_numbers_len(generator);
    unsigned int count_to_reach_max =
        distribution_selected_numbers_count(generator);
    unsigned int number_to_get_expected_answer =
        rand_limit / count_to_reach_max;

    vector<unsigned int> numbers(numbers_len, 0);
    // generate random numbers
    for (size_t j = 0; j < numbers.size(); ++j) {
      numbers[i] = distribution_limit_and_number(generator);
    }
    numbers[numbers.size() / 2] = number_to_get_expected_answer;
    assert(FindGreatestNumber(numbers, rand_limit) ==
           number_to_get_expected_answer * count_to_reach_max);
  }
}

void TestGreatestNumberTime() {
  cout << "TestNumbersWithNonZeroLimit"s << endl;
  cout << "There are 1000 numbers of all ones and the limit is 1000000000"
       << endl;
  unsigned int max_numbers_len = 1000;
  unsigned int max_limit = 1000000000;
  vector<unsigned int> numbers(max_numbers_len, 1);
  std::clock_t start = std::clock();
  unsigned int gn = FindGreatestNumber(numbers, max_limit);
  assert((gn == 4));
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
    &TestEmptyListOfNumbers,
    &TestNumbersAllGreaterThanLimit,
    &TestNumbersWithNonZeroLimit,
    &TestGreatestNumberTime,
};

// run all tests
int main() {
  bool TESTS[NUM_TESTS];

  // Mark tests that will run
  for (int i = 0; i < NUM_TESTS; ++i) {
    TESTS[i] = true;
  }

  for (int i = 0; i < NUM_TESTS; ++i) {
    if (TESTS[i]) {
      tests[i]();
      std::cout << "Test " << i + 1 << " passed!" << std::endl;
    }
  }
}
