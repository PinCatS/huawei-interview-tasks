#include <assert.h>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

#include "bigint.h"

#define NUM_TESTS 6

using namespace std::literals::string_literals;
using std::cout;
using std::endl;
using std::string;
using namespace bigint_huawei;

/****************************************************************************************************
 *                                   IMPLEMENTATION OF TESTS
 * **************************************************************************************************/
void TestDefaultConstructor() {
  cout << "TestDefaultConstructor"s << endl;

  BigInt number;

  assert((number.to_string() == "0"s));
}

void TestUnsignedLongLongConstructor() {
  cout << "TestUnsignedLongLongConstructor"s << endl;

  BigInt zero(0);
  assert((zero.to_string() == "0"s));

  BigInt one(1);
  assert((one.to_string() == "1"s));

  BigInt a(123456789);
  assert((a.to_string() == "123456789"s));

  BigInt b(100000000);
  assert((b.to_string() == "100000000"s));
}

void TestStringConstructor() {
  cout << "TestStringConstructor"s << endl;

  BigInt x(""s);
  assert((x.to_string() == "0"s));

  BigInt y("0"s);
  assert((y.to_string() == "0"s));

  BigInt z("555"s);
  assert((z.to_string() == "555"s));

  BigInt all_zeros("00000"s);
  assert((all_zeros.to_string() == "0"s));

  BigInt leading_zeros("0001000"s);
  assert((leading_zeros.to_string() == "1000"s));

  string big_number_str(1000, '1');
  BigInt big_number(big_number_str);
  assert((big_number.to_string() == big_number_str));

  // should throw exception when invalid arguments are passed:
  string bad_number_str = "123BigInt456";
  try {
    BigInt bad_number(bad_number_str); // without sign
  } catch (std::invalid_argument &e) {
    string expected_message =
        "Expected an integer, got "s + bad_number_str + " (-->'t')"s;
    assert(e.what() == expected_message);
  }
}

void TestAdditionOperation() {
  cout << "TestAdditionOperation"s << endl;

  BigInt zero_1;
  BigInt zero_2;
  assert(((zero_1 + zero_2).to_string() == "0"s));

  BigInt one("1"s);
  BigInt two("2"s);
  assert(((one + two).to_string() == "3"s));

  BigInt three("3"s);
  BigInt nine("9"s);
  assert(((three + nine).to_string() == "12"s));

  BigInt a("112233445566778899"s);
  BigInt b("998877665544332211"s);
  assert(((a + b).to_string() == "1111111111111111110"s));
}

void TestRandomNumbersAddition() {
  cout << "TestRandomNumbersAddition"s << endl;

  std::random_device generator;
  // uniform distribution of numbers from LLONG_MIN to LLONG_MAX:
  std::uniform_int_distribution<unsigned long long> distribution(0, ULLONG_MAX);
  for (int i = 0; i < 100; ++i) {
    unsigned long long rand_num = distribution(generator);
    assert(BigInt(rand_num).to_string() == std::to_string(rand_num));
  }
}

void TestAdditionOperationTime() {
  cout << "TestAdditionOperationTime"s << endl;
  cout
      << "Creation of two numbers with 1000 digits and its addition and assignment"s
      << endl;
  string str_number(1000, '9');
  std::clock_t start = std::clock();
  BigInt a(str_number);
  BigInt b(str_number);
  BigInt c = a + b;
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
    &TestDefaultConstructor,    &TestUnsignedLongLongConstructor,
    &TestStringConstructor,     &TestAdditionOperation,
    &TestRandomNumbersAddition, &TestAdditionOperationTime,
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
