#include <iostream>
#include <string>
#include <vector>

#include "greatest_number.h"

#define MAX_NUMBERS_COUNT 1000
#define MAX_LIMIT 1000000000
#define MAX_NUMBER_VALUE 1000000000

using namespace std;

unsigned int ReadNumber() {
  unsigned int number;
  cin >> number;
  return number;
}

pair<unsigned int, unsigned int> ReadCountAndLimit() {
  unsigned int numbers_count, limit;
  cin >> numbers_count >> limit;
  return {numbers_count, limit};
}

bool IsEndOfTestCases(const pair<unsigned int, unsigned int> &values) {
  return (values.first == 0 and values.second == 0);
}

int main() {
  unsigned int test_case_id = 1;
  vector<unsigned int> numbers;
  pair<unsigned int, unsigned int> count_and_limit;
  do {
    count_and_limit = ReadCountAndLimit();
    if (IsEndOfTestCases(count_and_limit)) {
      break;
    }

    auto [count, limit] = count_and_limit;
    if (count < 0 || count > MAX_NUMBERS_COUNT) {
      cerr << "Invalid numbers of numbers: "s << count
           << ". Should be in the range [0, "s << MAX_NUMBERS_COUNT << "]."
           << endl;
      return -1;
    }

    if (limit < 0 || limit > MAX_LIMIT) {
      cerr << "Invalid limit: "s << limit << ". Should be in the range [0, "s
           << MAX_LIMIT << "]." << endl;
      return -1;
    }

    for (unsigned int i = 0; i < count; ++i) {
      unsigned int number = ReadNumber();
      if (number < 0 || number > MAX_NUMBER_VALUE) {
        cerr << "Invalid number value: "s << number
             << ". Should be in the range [0, "s << MAX_NUMBER_VALUE << "]."
             << endl;
        return -1;
      }
      numbers.push_back(number);
    }

    unsigned int greatest_number =
        gn_huawei::FindGreatestNumber(numbers, limit);

    cout << "Case "s << test_case_id << ": "s << greatest_number << endl
         << endl;

    numbers.clear();
    ++test_case_id;
  } while (true);
}
