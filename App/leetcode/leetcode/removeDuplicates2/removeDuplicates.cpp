#include <iostream>
#include <vector>

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) 
	{
		std::vector<int>::iterator it;
		
		if(0 == nums.size())
	    {
			return 0;
		}			
	
		it = nums.begin();
		while(it != nums.end()  - 1)
		{
			if(*it == *(it+1))
			{
		        nums.erase(it);
			}
			else
			{
				it++;
			}
		}
		
        return nums.size();
    }
};

int main()
{
	Solution test;
	
	std::vector<int> nums = {1,1,2};
	std::cout << test.removeDuplicates(nums) << std::endl;
	
	std::vector<int> nums2 = {0,0,1,1,1,2,2,3,3,4};
	std::cout << test.removeDuplicates(nums2) << std::endl;
	
	return 0;
}