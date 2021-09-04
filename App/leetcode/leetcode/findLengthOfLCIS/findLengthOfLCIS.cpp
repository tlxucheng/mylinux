#include <iostream>
#include <vector>

class Solution {
public:
    int findLengthOfLCIS(std::vector<int>& nums) 
	{
        int left = 0;
		int right = 0;
		int length = 0;
		
		for(int i = 0; i < nums.size() - 1; i++)
		{
			if(nums[i+1] > nums[i])
			{
				right++;
			}
			else
			{
				left = right;
			}
			
			if(right - left > length)
			{
				length = right - left;
			}
		}
		
		return length+1;
    }
};

int main()
{
	Solution test;
	
	std::vector<int> v1 = {1,3,5,4,7};
	std::cout << test.findLengthOfLCIS(v1) << std::endl;
	
	std::vector<int> v2 = {2,2,2,2,2};
	std::cout << test.findLengthOfLCIS(v2) << std::endl;
	
	return 0;
}