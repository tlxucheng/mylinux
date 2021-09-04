#include <iostream>
#include <vector>

class Solution {
public:
    int search(std::vector<int>& nums, int target)
	{
		int i      = 0;
		int left   = 0;
		int right  = nums.size();
		int middle = (right - left)/2;
		
	    if(target == nums[0])
		{
			return 0;
		}	
		
		if(target == nums[middle])
		{
			return middle;
		}	
		
		while(middle != left && middle != right)
	    {
			if(target == nums[middle])
			{
				return middle;
			}			
			else if(target < nums[middle])
			{
				right = middle;
				middle = (right - left)/2 + left;
			}	
			else
			{
				left = middle;
			    middle = (right - left)/2 + left;
			}
		}	

        return -1;		
    }
};

int main()
{
	Solution test;
	std::vector<int> vc1 = {-1,0,3,5,9,12};
	std::cout << test.search(vc1, 9) << std::endl;
	std::cout << test.search(vc1, 2) << std::endl;
	
    std::vector<int> vc2 = {5};
	std::cout << test.search(vc2, 5) << std::endl;

    std::vector<int> vc3 = {2,5};
	std::cout << test.search(vc3, 2) << std::endl;

	std::cout << test.search(vc1, 12) << std::endl;
	
	return 0;
}