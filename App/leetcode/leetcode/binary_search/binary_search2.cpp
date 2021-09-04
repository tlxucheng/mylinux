#include <iostream>
#include <vector>

class Solution {
public:
    int search(std::vector<int>& nums, int target)
	{
		int i      = 0;
		int left   = 0;
		int right  = nums.size();
		int middle = 0;
		
		/*
	    if(target == nums[0])
		{
			return 0;
		}	
		*/

		while(left <= right)
	    {
            middle = ((right - left) >> 1) + left;
            
			if(target == nums[middle])
			{
				return middle;
			}			
			else if(target < nums[middle])
			{
				right = middle - 1;
			}	
			else
			{
				left = middle + 1;
			}
		}	

        return -1;		
    }
};

int main()
{
	Solution test;
	std::vector<int> vc1 = {-1,0,3,5,9,12};
	std::cout << test.search(vc1, -1) << std::endl;
	
	return 0;
}
