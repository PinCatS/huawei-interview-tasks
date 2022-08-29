#include <iostream>

#include "bigint.h"

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
pair<BigInt, BigInt> ReadQuery() {
  BigInt first, second;
  cin >> first >> second;
  return {first, second};
}

/**
 * Reads test cases, adds BigInts and displays results.
 */
int main() {
  int count = ReadTestCasesCount();

  pair<BigInt, BigInt> numbers;
  for (int i = 0; i < count; ++i) {
    const auto &[first, second] = ReadQuery();
    cout << "Case "s << i + 1 << ": "s << endl
         << first << " + "s << second << " = "s << first + second << endl
         << endl;
  }
}
