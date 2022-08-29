#include <iostream>
#include <string>
#include <vector>

#include "greatest_number.h"

using namespace std;

int ReadNumber() {
  int number;
  cin >> number;
  return number;
}

pair<int, int> ReadCountAndLimit() {
  int numbers_count, limit;
  cin >> numbers_count >> limit;
  return {numbers_count, limit};
}

bool IsEndOfTestCases(const pair<int, int> &values) {
  return (values.first == 0 and values.second == 0);
}

int main() {
  int test_case_id = 1;
  vector<int> numbers;
  pair<int, int> count_and_limit;
  do {
    count_and_limit = ReadCountAndLimit();
    if (IsEndOfTestCases(count_and_limit)) {
      break;
    }

    auto [count, limit] = count_and_limit;
    for (int i = 0; i < count; ++i) {
      numbers.push_back(ReadNumber());
    }

    int greatest_number = gn_huawei::FindGreatestNumber(numbers, limit);

    cout << "Case "s << test_case_id << ": "s << greatest_number << endl
         << endl;

    numbers.clear();
    ++test_case_id;
  } while (true);
}
