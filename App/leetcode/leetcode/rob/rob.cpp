#include <iostream>
#include <vector>

class Solution {
public:
    int rob(std::vector<int>& nums) 
	{
		int n = nums.size();
		
		if(0 == n)
		{
			return 0;
		}
		if(1 == n)
		{
			return nums[0];
		}
		if(2 == n)
		{
			return std::max(nums[0], nums[1]);
		}
		
		int dp[n];
		dp[0] = nums[0];
		dp[1] = std::max(nums[0], nums[1]);
		for(int i = 2; i < n; i++)
		{
			dp[i] = std::max(nums[i]+dp[i-2], dp[i-1]);
		}
		
		return dp[n-1];
	}
};

int main()
{
	Solution test;
	
	std::vector<int> nums1 = {1,2,3,1};
	std::cout << test.rob(nums1) << std::endl;
	
	std::vector<int> nums2 = {2,7,9,3,1};
	std::cout << test.rob(nums2) << std::endl;
	
	return 0;
}