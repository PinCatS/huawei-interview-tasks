#include <iostream>

#include "bigint.h"

using namespace std::literals::string_literals;
using std::cin;
using std::cout;
using std::endl;

using namespace bigint_huawei;

/**
 * Reading int from the in stream.
 */
int ReadTestCasesCount() {
  int count;
  cin >> count;
  return count;
}

/**
 * Reading two BigInt numbers in the line.
 */
std::pair<BigInt, BigInt> ReadQuery() {
  BigInt first, second;
  cin >> first >> second;
  return {first, second};
}

/**
 * Reads test cases, adds BigInts and displays results.
 */
int main() {
  int count = ReadTestCasesCount();

  std::pair<BigInt, BigInt> numbers;
  for (int i = 0; i < count; ++i) {
    const auto &[first, second] = ReadQuery();
    cout << "Case "s << i + 1 << ": "s << endl
         << first << " + "s << second << " = "s << first + second << endl
         << endl;
  }
}
