#include <iostream>
#include <vector>


class Solution {
public:
    int majorityElement(std::vector<int>& nums) {
        int major, counts = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            if (!counts) {
                major = nums[i];
                counts = 1;
            }
            else counts += (nums[i] == major) ? 1 : -1;
        }
        return major;
    }
};

int main()
{
	Solution test;
	
	std::vector<int> nums1 = {3,2,3};
	std::cout << test.majorityElement(nums1) << std::endl;;
	
	std::vector<int> nums2 = {2,2,1,1,1,2,2};
	std::cout << test.majorityElement(nums2) << std::endl;;

	std::vector<int> nums3 = {8,8,7,7,7};
	std::cout << test.majorityElement(nums3) << std::endl;;
	
	return 0;
}