#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int missingNumber(std::vector<int>& nums) 
	{
		int i = 0;
		
        sort(nums.begin(), nums.end());
	
	    for(i = 0; i < nums.size(); i++)
		{
			if(i != nums[i])
			{
				break;
			}
		}
		
		return i;
    }
};

int main()
{
	Solution test;
		
	std::vector<int> nums = {9,6,4,2,3,5,7,0,1};
	std::cout << test.missingNumber(nums) << std::endl;
	
	std::vector<int> nums1 = {3,0,1};
	std::cout << test.missingNumber(nums1) << std::endl;
	
	std::vector<int> nums2 = {0,1};
	std::cout << test.missingNumber(nums2) << std::endl;
	
	return 0;
}