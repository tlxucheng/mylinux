#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxSubArray(std::vector<int>& nums)
	{
        int max_sub_array = nums[0];
		
		for(int i = 1; i < nums.size(); i++)
	    {
			nums[i] = std::max(nums[i], nums[i] + nums[i-1]);
			max_sub_array = std::max(max_sub_array, nums[i]);
		}			
	
		return max_sub_array;
    }
	
	int maxSubArray2(std::vector<int>& nums)
	{
        int n = nums.size(); // size array
        int sum = 0; // sum curent of array
        int max_sum = nums[0]; // MAX subarray in array
        for(int i =0;i<n;i++)
        {
            if(sum < 0)
            {
                sum = 0;
            }
            sum +=nums[i];
            //sum = max(sum,0);
            max_sum = std::max(sum,max_sum);            
        }
        return max_sum;
    }
};

int main()
{
	Solution test;
		
#if 0
	std::vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
	std::cout << test.maxSubArray(nums) << std::endl;

	std::vector<int> nums1 = {1};
	std::cout << test.maxSubArray(nums1) << std::endl;

	std::vector<int> nums2 = {5,4,-1,7,8};
	std::cout << test.maxSubArray(nums2) << std::endl;
#endif

	std::vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
	std::cout << test.maxSubArray2(nums) << std::endl;
	
	return 0;
}