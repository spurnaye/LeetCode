// 410. Split Array Largest Sum
// https://leetcode.com/problems/split-array-largest-sum/
#include <iostream>
#include <cassert>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
using namespace std;

// BEGIN: http://www.cnblogs.com/grandyang/p/5933787.html
// BEGIN: https://discuss.leetcode.com/topic/61324/clear-explanation-8ms-binary-search-java
class Solution {
public:
	int splitArray(vector<int>& nums, int m) {
		vector<size_t> numsCopy(begin(nums), end(nums));
		size_t left = *max_element(begin(numsCopy), end(numsCopy));
		size_t right = accumulate(begin(numsCopy), end(numsCopy), 0);
		while (left + 1 < right) {
			size_t mid = left + (right - left) / 2;
			if (isValid(mid, m, numsCopy)) {
				right = mid;
			}
			else {
				left = mid;
			}
		}
		if (isValid(left, m, numsCopy)) {
			return left;
		}
		return right;
	}
private:
	bool isValid(const size_t target, int m, const vector<size_t>& nums) {
		for (size_t i = 0, sum = 0; i < nums.size(); i++) {
			if ((sum += nums[i]) > target) {
				if (--m <= 0) {
					return false;
				}
				sum = nums[i];
			}
		}
		return true;
	}
};
// END: https://discuss.leetcode.com/topic/61324/clear-explanation-8ms-binary-search-java
// END: http://www.cnblogs.com/grandyang/p/5933787.html

// BEGIN: Time Limit Exceeded
// class Solution {
// public:
// 	int splitArray(vector<int>& nums, int m) {
// 		vector<vector<size_t>> OPT(nums.size(), vector<size_t>(nums.size(), 0)), cumsum(nums.size(), vector<size_t>(nums.size(), 0));
// 		for (size_t i = 0; i < nums.size(); i++) {
// 			for (size_t j = i; j < nums.size(); j++) {
// 				if (j == i) {
// 					cumsum[i][j] = nums[j];
// 					OPT[i][j] = nums[j];
// 				}
// 				else {
// 					cumsum[i][j] = cumsum[i][j - 1] + nums[j];
// 					OPT[i][j] = OPT[i][j - 1] + nums[j];
// 				}
// 			}
// 		}
// 		for (int k = 1; k < m; k++) {
// 			for (size_t len = nums.size(); len >= 1; len--) {
// 				for (size_t i = 0; i + len <= nums.size(); i++) {
// 					const size_t j = i + len - 1;
// 					for (size_t l = i; l + k <= j; l++) {
// 						OPT[i][j] = min(OPT[i][j], max(cumsum[i][l], OPT[l + 1][j]));
// 					}
// 				}
// 			}
// 		}
// 		return OPT[0][nums.size() - 1];
// 	}
// };
// END: Time Limit Exceeded

// BEGIN: Memory Limit Exceeded
// class Solution {
// public:
// 	int splitArray(vector<int>& nums, int m) {
// 		vector<vector<vector<size_t>>> OPT(nums.size(), vector<vector<size_t>>(nums.size(), vector<size_t>(nums.size(), size_t(-1))));
// 		for (size_t len = 1; len <= nums.size(); len++) {
// 			for (size_t i = 0; i + len <= nums.size(); i++) {
// 				const size_t j = i + len - 1;
// 				OPT[0][i][j] = accumulate(next(begin(nums), i), next(begin(nums), i + len), 0);
// 				OPT[len - 1][i][j] = *max_element(next(begin(nums), i), next(begin(nums), i + len));
// 			}
// 		}
// 		for (size_t len = 1; len <= nums.size(); len++) {
// 			for (size_t i = 0; i + len <= nums.size(); i++) {
// 				const size_t j = i + len - 1;
// 				for (size_t k = 1; k + 1 < len; k++) {
// 					for (size_t l = i; l + k <= j; l++) {
// 						OPT[k][i][j] = min(OPT[k][i][j], max(OPT[0][i][l], OPT[k - 1][l + 1][j]));
// 					}
// 				}
// 			}
// 		}
// 		return OPT[m - 1][0][nums.size() - 1];
// 	}
// };
// END: Memory Limit Exceeded

int main(void) {
	Solution solution;
	vector<int> nums;
	int result = 0;

	nums = {7, 2, 5, 10, 8};
	result = solution.splitArray(nums, 2);
	assert(18 == result);
	
	nums = {1, 2147483647};
	result = solution.splitArray(nums, 2);
	assert(2147483647 == result);

	nums = {5334, 6299, 4199, 9663, 8945, 3566, 9509, 3124, 6026, 6250, 7475, 5420, 9201, 9501, 38, 5897, 4411, 6638, 9845, 161, 9563, 8854, 3731, 5564, 5331, 4294, 3275, 1972, 1521, 2377, 3701, 6462, 6778, 187, 9778, 758, 550, 7510, 6225, 8691, 3666, 4622, 9722, 8011, 7247, 575, 5431, 4777, 4032, 8682, 5888, 8047, 3562, 9462, 6501, 7855, 505, 4675, 6973, 493, 1374, 3227, 1244, 7364, 2298, 3244, 8627, 5102, 6375, 8653, 1820, 3857, 7195, 7830, 4461, 7821, 5037, 2918, 4279, 2791, 1500, 9858, 6915, 5156, 970, 1471, 5296, 1688, 578, 7266, 4182, 1430, 4985, 5730, 7941, 3880, 607, 8776, 1348, 2974, 1094, 6733, 5177, 4975, 5421, 8190, 8255, 9112, 8651, 2797, 335, 8677, 3754, 893, 1818, 8479, 5875, 1695, 8295, 7993, 7037, 8546, 7906, 4102, 7279, 1407, 2462, 4425, 2148, 2925, 3903, 5447, 5893, 3534, 3663, 8307, 8679, 8474, 1202, 3474, 2961, 1149, 7451, 4279, 7875, 5692, 6186, 8109, 7763, 7798, 2250, 2969, 7974, 9781, 7741, 4914, 5446, 1861, 8914, 2544, 5683, 8952, 6745, 4870, 1848, 7887, 6448, 7873, 128, 3281, 794, 1965, 7036, 8094, 1211, 9450, 6981, 4244, 2418, 8610, 8681, 2402, 2904, 7712, 3252, 5029, 3004, 5526, 6965, 8866, 2764, 600, 631, 9075, 2631, 3411, 2737, 2328, 652, 494, 6556, 9391, 4517, 8934, 8892, 4561, 9331, 1386, 4636, 9627, 5435, 9272, 110, 413, 9706, 5470, 5008, 1706, 7045, 9648, 7505, 6968, 7509, 3120, 7869, 6776, 6434, 7994, 5441, 288, 492, 1617, 3274, 7019, 5575, 6664, 6056, 7069, 1996, 9581, 3103, 9266, 2554, 7471, 4251, 4320, 4749, 649, 2617, 3018, 4332, 415, 2243, 1924, 69, 5902, 3602, 2925, 6542, 345, 4657, 9034, 8977, 6799, 8397, 1187, 3678, 4921, 6518, 851, 6941, 6920, 259, 4503, 2637, 7438, 3893, 5042, 8552, 6661, 5043, 9555, 9095, 4123, 142, 1446, 8047, 6234, 1199, 8848, 5656, 1910, 3430, 2843, 8043, 9156, 7838, 2332, 9634, 2410, 2958, 3431, 4270, 1420, 4227, 7712, 6648, 1607, 1575, 3741, 1493, 7770, 3018, 5398, 6215, 8601, 6244, 7551, 2587, 2254, 3607, 1147, 5184, 9173, 8680, 8610, 1597, 1763, 7914, 3441, 7006, 1318, 7044, 7267, 8206, 9684, 4814, 9748, 4497, 2239};
	result = solution.splitArray(nums, 9);
	assert(194890 == result);

	nums = {499, 498, 497, 496, 495, 494, 493, 492, 491, 490, 489, 488, 487, 486, 485, 484, 483, 482, 481, 480, 479, 478, 477, 476, 475, 474, 473, 472, 471, 470, 469, 468, 467, 466, 465, 464, 463, 462, 461, 460, 459, 458, 457, 456, 455, 454, 453, 452, 451, 450, 449, 448, 447, 446, 445, 444, 443, 442, 441, 440, 439, 438, 437, 436, 435, 434, 433, 432, 431, 430, 429, 428, 427, 426, 425, 424, 423, 422, 421, 420, 419, 418, 417, 416, 415, 414, 413, 412, 411, 410, 409, 408, 407, 406, 405, 404, 403, 402, 401, 400, 399, 398, 397, 396, 395, 394, 393, 392, 391, 390, 389, 388, 387, 386, 385, 384, 383, 382, 381, 380, 379, 378, 377, 376, 375, 374, 373, 372, 371, 370, 369, 368, 367, 366, 365, 364, 363, 362, 361, 360, 359, 358, 357, 356, 355, 354, 353, 352, 351, 350, 349, 348, 347, 346, 345, 344, 343, 342, 341, 340, 339, 338, 337, 336, 335, 334, 333, 332, 331, 330, 329, 328, 327, 326, 325, 324, 323, 322, 321, 320, 319, 318, 317, 316, 315, 314, 313, 312, 311, 310, 309, 308, 307, 306, 305, 304, 303, 302, 301, 300, 299, 298, 297, 296, 295, 294, 293, 292, 291, 290, 289, 288, 287, 286, 285, 284, 283, 282, 281, 280, 279, 278, 277, 276, 275, 274, 273, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 257, 256, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 236, 235, 234, 233, 232, 231, 230, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	result = solution.splitArray(nums, 50);
	assert(2667 == result);	

	cout << "\nPassed All\n";
	return 0;
}