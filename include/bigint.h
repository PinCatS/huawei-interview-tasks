#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>
#include <vector>

namespace bigint_huawei {

/**
 * BigInt works with integers of any length.
 *
 * Design notes:
 *  BigInt integer is represented as vector of bytes in reverse order
 *  for performance reasons (adding new digit to the end of the vector).
 *
 * Supports:
 *  - Only natural (positive integers)
 *  - Default default constructor that creates number 0
 *  - Reading BigInt from in stream
 *  - Writing BigInt to out stream
 *  - Add operation for two BigInt numbers
 *  - Conversion to string
 *
 * All other features will be implemented in the next releases.
 */
class BigInt {
  std::vector<uint8_t> digits;

public:
  BigInt();
  BigInt(const std::string &number);
  BigInt(unsigned long long number);

  friend std::istream &operator>>(std::istream &in, BigInt &number);
  friend std::ostream &operator<<(std::ostream &out, const BigInt &number);

  BigInt operator+(const BigInt &number) const;

  std::string to_string() const;
};

} // namespace bigint_huawei
#endif
