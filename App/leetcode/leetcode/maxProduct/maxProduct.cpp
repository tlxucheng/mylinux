#include <iostream>
#include <vector>

class Solution {
public:
    int maxProduct(std::vector<int>& nums)
	{
        int max = 0;
		int max_second = 0;
		
		if(nums[0] > nums[1])
		{
			max = nums[0];
			max_second = nums[1];
		}
		else
		{
			max = nums[1];
			max_second = nums[0];
		}
		
		for(int i = 2; i < nums.size(); i++)
		{
			if(nums[i] > max_second && nums[i] <= max)
			{
			    max_second = nums[i];
			}
			else if(nums[i] > max)
			{
				max_second = max;
				max = nums[i];
			}
		}
		
		
	    return (max-1)*(max_second-1);
    }
};

int main()
{
	Solution test;
	
	std::vector<int> vc1 = {3,4,5,2};
	std::cout << test.maxProduct(vc1) << std::endl;

	std::vector<int> vc2 = {1,5,4,5};
	std::cout << test.maxProduct(vc2) << std::endl;	

	std::vector<int> vc3 = {3,7};
	std::cout << test.maxProduct(vc3) << std::endl;
	
	return 0;
}