#include "bigint.h"

/**
 * Default constructor that builds 0.
 */
BigInt::BigInt() {}

/**
 * Constructor that builds BigInt from string representation.
 *
 * Time complexity: O(n) where n is a number of digits
 * Space complexity: O(n) where n is a number of digits
 */
BigInt::BigInt(const string &number) {
  for (int i = number.size() - 1; i >= 0; --i) {
    if (number[i] - '0' < 0 || number[i] - '0' > 9) {
      throw invalid_argument("Expected an integer, got "s + number + " (-->'"s +
                             number[i] + "')"s);
    }
    digits.push_back(number[i] - '0');
  }
}

/**
 * Converts BigInt into string.
 *
 * Time complexity: O(n) where n is a number of digits
 * Space complexity: O(n) where n is a number of digits (to accumulate string)
 */
string BigInt::to_string() const {

  if (this->digits.empty()) {
    return "0"s;
  }

  string number;
  for (int i = this->digits.size() - 1; i >= 0; --i) {
    number.push_back(this->digits[i] + '0');
  }
  return number;
}

/**
 * Reads BigInt from in stream.
 *
 * Time complexity: O(n) where n is a number of digits (constructing BigInt)
 * Space complexity: O(n) where n is a number of digits
 */
istream &operator>>(istream &in, BigInt &number) {
  string input;
  in >> input;
  number = BigInt(input);
  return in;
}

/**
 * Write BigInt to out stream.
 *
 * Time complexity: O(n) where n is a number of digits (converting BigInt into
 * string) Space complexity: O(n) where n is a number of digits
 */
std::ostream &operator<<(std::ostream &out, const BigInt &number) {
  out << number.to_string();
  return out;
}

/**
 * Adds two BigInt numbers
 *
 * Time complexity: O(n) where n is a number of digits of largest number
 * Space complexity: O(n) where n is a number of digits of largest number
 */
BigInt BigInt::operator+(const BigInt &number) const {
  BigInt result;

  uint8_t overflow = 0;
  size_t i = 0;
  while (i < this->digits.size() || i < number.digits.size()) {
    int sum = overflow;
    if (i < this->digits.size()) {
      sum += this->digits[i];
    }
    if (i < number.digits.size()) {
      sum += number.digits[i];
    }
    result.digits.push_back(sum % 10);
    overflow = sum / 10;
    ++i;
  }

  if (overflow) {
    result.digits.push_back(1);
  }

  return result;
}
