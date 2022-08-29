#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * BigInt works with integers of any length.
 *
 * Design notes:
 *  BigInt integer is represented as vector of bytes in reverse order
 *  for performance reasons (adding new digit to the end of the vector).
 *
 * Supports:
 *  - Only natural (positive integers) without leading zeroes
 *  - Default default constructor that creates number 0
 *  - Reading BigInt from in stream
 *  - Writing BigInt to out stream
 *  - Add operation for two BigInt numbers
 *  - Conversion to string
 *
 * All other features will be implemented in the next releases.
 */
class BigInt {
  vector<uint8_t> digits;

public:
  BigInt();
  BigInt(const std::string &);

  friend std::istream &operator>>(std::istream &, BigInt &);
  friend std::ostream &operator<<(std::ostream &, const BigInt &);

  BigInt operator+(const BigInt &) const;

  string to_string() const;
};

#endif
