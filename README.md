# Test task for Software Developer position in Huawei
It was asked to solve 3 interesting problems using C++ language.

All of them were solved within time, space requirements and were covered with tests.

Please see below problems solution notes, what was done and how to run them.

## Technologies
---------------
* C++17
* Make
* Docker
* Git

`valgrind` utility was used to check for memory leaks (see below)
`time` linux utility was used to check memory consumption (see below)

## How to run solved problems
-----------------------------

There are two options:

* Run the project in the docker container (recommended way since you don't need to worry about dependencies)
* Build the project on PC using make utility

### Run the project in the docker container
1. Clone the project to your PC.
2. Go to the root directory of the project.
3. Run the command `docker build --no-cache -t pincats/huawei:v1.0.0 .`. The command will build the image based on the Dockerfile instructions and tagged as `pincats/huawei:v1.0.0`.
4. Run the command `docker run -d --name huawei pincats/huawei:v1.0.0`. The command will create and start the `huawei` container based on `pincats/huawei:v1.0.0` image. `-d` key tells to detach your terminal from the container process.
5. Run the command `docker exec -it huawei bash`. The command will logon to huawei container and start bash terminal.
6. Now you should be in the Ubuntu OS bash terminal in the `huawei` directory at the root of the project. The project was already built there. See the details below which are similar to both approaches.

### Run the project on the PC
1. Clone the project to your PC.
2. Go to the root directory of the project.
3. Run make to get the executables.
4. See the details below which are similar to both approaches.

### Common instructions to the approaches above
1. At that stage you should be in the root directory of the projects and it was successfully built.
2. There should be `bin` folder with the problems executables:
* `text1` - text1 problem (addition of two big numbers)
* `text2` - text2 problem (Great Number)
* `text3` - text3 problem (Treasury Map / Map Solver)
3. `data` folder contains input data taken from the problems pdf.
4. To run all problems with the input data issue the command `make run`
5. To build and run tests, you can issue the command `make tests`. It will build tests and run them.
6. Test executables will be in the `bin/tests` folder after you run `make test` just in case you want to run them separately.

## Project folder structure
---------------------------
* `src` folder contains all source code.

* `src/text<X>.cpp` files correspond to `main`  source code for `text1`, `text2`, `text3` problems respectively.
* `src/bigint.cpp` file - implementation of the structure that is used by `text1` problem.
* `src/greatest_number.cpp` file - implementation of the algorithm to solve `text2` problem.
* `src/map_solver.cpp`, `src/dlx.cpp`, `src/linked_matrix.cpp` files - implementation of the algorithm and structures required to solve `text3` problem.
* `include` folder contains corresponding header files.
* `test` folder contains tests implementation for the solutions.
* `data` folder contains `.txt` files with input data taken from the pdf file for the problems.
* `bin` file will be created after the project was build via `make` (see instruction above) and will contain executables to corresponding problems.
* `bin/tests` file will be available after `make tests` is issued. It will contain executables for the tests.
* `Makefile` contains instructions how to build the project. Useful commands are: `make` to build the project,`make run` to run all problems against the input data, `make tests` to build and run tests, `make clean` to remove `bin`, `obj` folders.

## Problems design notes
------------------------
Please see the more detailed notes in the headers. The below are the key ideas.
### Addition of two big numbers (text1) problem

There was a choice between representing big number as `string` or `vector`. I made decision to `vector<uint_8>` because it more clearly reflects that there is array of bytes.

The digits of input number are stored in __reverse__ order due to efficiency to push back the overflowed `1`. Otherwise, I needed to add it to the front and shift all elements.

I implemented enough functionality to solve given problem. There are many functionality that can be added in the future.
The most big restriction is it only supports __positive__ numbers (natural). The input is validated against that restriction.

Most of the operations time complexity is O(n) where n is a number of digits. (see the comments in the `bigint.h`)

#### Smoke run on input data:

```
*******************************
Big inetger addition (text1)
-------------------------------
Case 1: 
1 + 2 = 3

Case 2: 
112233445566778899 + 998877665544332211 = 1111111111111111110

*******************************
```
#### Tests run:

```
*******************************
Testing BigInt
-------------------------------
TestDefaultConstructor
Test 1 passed!
TestUnsignedLongLongConstructor
Test 2 passed!
TestStringConstructor
Test 3 passed!
TestAdditionOperation
Test 4 passed!
TestRandomNumbersAddition
Test 5 passed!
TestAdditionOperationTime
Creation of two numbers with 1000 digits and its addition and assignment
Elapsed time = 0.029 ms (CPU time)
Test 6 passed!
```
#### Memory consumption

Using `env time -v ./bin/text1 < ./data/text1_input.txt` command: 
```
Maximum resident set size (kbytes): 3380
```
#### Valgrind run:

```
root@1c5b438af814:/huawei# valgrind --leak-check=yes ./bin/text1 < ./data/text1_input.txt
==75== Memcheck, a memory error detector
==75== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==75== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==75== Command: ./bin/text1
==75== 
Case 1: 
1 + 2 = 3

Case 2: 
112233445566778899 + 998877665544332211 = 1111111111111111110

==75== 
==75== HEAP SUMMARY:
==75==     in use at exit: 0 bytes in 0 blocks
==75==   total heap usage: 33 allocs, 33 frees, 78,209 bytes allocated
==75== 
==75== All heap blocks were freed -- no leaks are possible
==75== 
==75== For lists of detected and suppressed errors, rerun with: -s
==75== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### Greatest Number (text2) problem

The key idea is to calculate and store all `two sums` in array and then sum `two sums` but instead of running through all combination, we can optimize it by `binary searching` the closest sum to the limit reducing time complexity down from O(n<sup>4</sup>) to O(n<sup>2</sup>logn) where n is a count of numbers.

In the corner case when the elements contain max allowed values `1000000000`, the sum value can reach `4000000000`. It was taken into consideration and `unsigned int` was used for sum variables. The test also was written for that case.

**Important note**: `the players choose no more than four integers from them` I understand as `players can pick 1/2/3/4 numbers` and solution takes it into account.
At the real case, I would clarify it from the customer. It might be treated as `players should alway pick any 4`.

Time complexity is: O(n<sup>2</sup>logn) (see details in the greatest_number.h)
Space complexity: O(n<sup>2</sup>) where n is a number of numbers because we store all `two sums`

#### Smoke run on input data:

```
*******************************
Greatest Number (text2)
-------------------------------
Case 1: 8
```

#### Tests run:

```
*******************************
Testing Greatest Number
-------------------------------
TestEmptyListOfNumbers
Test 1 passed!
TestNumbersAllGreaterThanLimit
Test 2 passed!
TestNumbersWithNonZeroLimit
Test 3 passed!
TestNumbersWithMaxValues
Test 4 passed!
TestGreatestNumberTime
There are 1000 numbers of all ones and the limit is 1000000000
Elapsed time = 33.231 ms (CPU time)
Test 5 passed!
```
#### Memory consumption

Using `env time -v ./bin/text2 < ./data/text2_input.txt` command: 

```
Maximum resident set size (kbytes): 3464
```
#### Valgrind run:

```
root@1c5b438af814:/huawei# valgrind --leak-check=yes ./bin/text2 < ./data/text2_input.txt
==76== Memcheck, a memory error detector
==76== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==76== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==76== Command: ./bin/text2
==76== 
Case 1: 8

Case 2: 80

==76== 
==76== HEAP SUMMARY:
==76==     in use at exit: 0 bytes in 0 blocks
==76==   total heap usage: 15 allocs, 15 frees, 78,396 bytes allocated
==76== 
==76== All heap blocks were freed -- no leaks are possible
==76== 
==76== For lists of detected and suppressed errors, rerun with: -s
==76== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### Treasury Map (text3) problem
The problem can be reduce to the NP-problem called `Exact Cover` and is solved using Knuth's AlgorithmX recursive nondeterministic algorithm. The implementation of the algorithm is called `DLX (DancingLinkX)` because it uses `Dancing Link` technique.

Algorithm uses `Linked Matrix` - data structure uses `Double Linked Lists` to represent the matrix. All nodes are connected in double linked list cycle. Each node pointers to the left/right (row) and to the up/down (column) neighbors. Nodes represent '1's in a matrix. Thus, `Linked Matrix` data structure is very efficient way to represent boolean matrix since we don't need to store '0's and for the `Exact Cover Problems` the matrix is usually very sparse.

How reduction to `Exact Cover` problem accomplished? Each point (1x1 square) of 2-d map is translated to 1-d map and each point represents a column. For example, if there is a 1x1 square with coordinates `(0, 1), (1, 2)` within `2x2 map`, the square point is translated into `2` using formula `y1 * map_width + x1`. Each `map piece` represents a row. Piece points are marked as '1's in a matrix.

`linked_matrix.h` describes `Linked Matrix` data structure.
`dlx.h` describes `DLX` algorithm. Important note - it doesn't stop as soon as finds first solution but continues to get the best one. (least number of pieces)
`map_solver.h` builds boolean matrix (reduces problem to the `Exact Cover`) and solves it.

#### Smoke run on input data:

```
*******************************
Find Map pieces (text3)
-------------------------------
1
-1
2
*******************************
```

#### Tests run:

```
*******************************
Map Solver
-------------------------------
TestMapWithMinWidthAndHeight
Test 1 passed!
Test2x2Map
Test 2 passed!
Test3x3MapForOverlapCase
Test 3 passed!
TestMapDifferentSizes
Test 4 passed!
TestMapSolverRandom
Test 5 passed!
TestMapSolverTime
There are 100 pieces and map of 30x30
Elapsed time = 4.388 ms (CPU time)
Test 6 passed!
*******************************
```
#### Memory consumption

Using `env time -v ./bin/text3 < ./data/text3_input.txt` command: 

```
Maximum resident set size (kbytes): 3712
```
#### Valgrind run:

```
root@1c5b438af814:/huawei# valgrind --leak-check=yes ./bin/text3 < ./data/text3_input.txt
==77== Memcheck, a memory error detector
==77== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==77== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==77== Command: ./bin/text3
==77== 
1
-1
2
==77== 
==77== HEAP SUMMARY:
==77==     in use at exit: 0 bytes in 0 blocks
==77==   total heap usage: 3,070 allocs, 3,070 frees, 365,988 bytes allocated
==77== 
==77== All heap blocks were freed -- no leaks are possible
==77== 
==77== For lists of detected and suppressed errors, rerun with: -s
==77== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Author
Sergey Li - pincats@gmail.com; telegram: @pincats
