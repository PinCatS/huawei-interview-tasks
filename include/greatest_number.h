#ifndef GREATEST_NUMBER_H
#define GREATEST_NUMBER_H

#include <algorithm>
#include <vector>

namespace gn_huawei {

/**
 * Finds the closest to the limit sum.
 * Can be picked at most 4 numbers (numbers can be repeated).
 *
 * Note: input array of numbers is modified (sorted)
 *
 * The below algorithm finds all two sums first and saves them.
 * Then it sums two sums and updates better maximum.
 *
 * Two optimize performance, sorting is used for:
 *  - To detect earlier if we can get out of loop
 *  - To use binary search to reduce two sums operations
 *
 * Time complexity: O((N^2)logN) where N is a number of numbers.
 * Details:
 *  - Sorting takes O(NlogN) where N is a number of numbers
 *  - Finding all two sums takes N(N+1)/2 => O(N^2) where N is a number of
 * numbers
 *  - Sorting all two sums takes O(N^2logN) because there are N(N+1)/2 two sums
 * in array
 *  - Finding sums of two sums takes (N^2)log(N^2) => O((N^2)logN) where N is a
 * number of numbers
 *
 * Space complexity: O(N^2) where N is a number of numbers because we store all
 * two sums
 */
int FindGreatestNumber(std::vector<int> &numbers, int limit);

} // namespace gn_huawei
#endif
