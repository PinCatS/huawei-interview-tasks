#include "greatest_number.h"

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
int FindGreatestNumber(std::vector<int> &numbers, int limit) {
  int max_sum = 0;

  // Sort to break loops earlier in case we get number/sum > limit
  sort(numbers.begin(), numbers.end());

  // Find all sums of two elements
  std::vector<int> two_sums;
  for (size_t i = 0; i < numbers.size(); ++i) {
    // Found best max
    if (numbers[i] == limit) {
      return numbers[i];
    }

    // All next will be above the limit
    if (numbers[i] > limit) {
      break;
    }

    // Update max_sum in case we can get the largest with only one number
    if (max_sum < numbers[i]) {
      max_sum = numbers[i];
    }

    for (size_t j = i; j < numbers.size(); ++j) {
      int sum = numbers[i] + numbers[j];
      // Found best max
      if (sum == limit) {
        return sum;
      }

      // All next sums will be above the limit
      if (sum > limit) {
        break;
      }

      // Update max_sum in case we can get the largest with only one number
      if (max_sum < sum) {
        max_sum = sum;
      }

      two_sums.push_back(sum);
    }
  }

  // Sort sums to use binary search
  sort(two_sums.begin(), two_sums.end());

  // Sum two sums. Instead of summing all combinations,
  // do binary search to improve performance.
  for (size_t i = 0; i < two_sums.size(); ++i) {
    int left = 0;
    int right = two_sums.size() - 1;
    while (left < right) {
      int mid = left + (right - left) / 2;
      int sum = two_sums[i] + two_sums[mid];

      if (sum == limit) {
        return sum;
      }

      if (sum < limit) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    int sum = two_sums[i] + two_sums[left];
    if (max_sum < sum) {
      max_sum = sum;
    }

    if (sum > limit) {
      break;
    }
  }

  return max_sum;
}

} // namespace gn_huawei
