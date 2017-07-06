#include <iostream>
#include <unordered_map>
#include <vector>

template <typename T>
using vector = std::vector<T>;

class Solution {
public:
	// time complexity O(n), space complexity O(n)
	vector<int> twoSum(vector<int>& nums, int target) {
		std::unordered_map<int, int> map;
		for (int i = 0; i < nums.size(); i++) {
			if (map.find(target - nums[i]) != map.end())
				return {map.at(target - nums[i]), i};
			map.insert({nums[i], i});
		}
	}
};


int main()
{
	vector<int> nums = {2, 5, 5, 1};
	Solution sol;
	vector<int> indices = sol.twoSum(nums, 10);
	
	for (int element : indices)
		std::cout << element << ", ";
	std::cout << std::endl;
}
