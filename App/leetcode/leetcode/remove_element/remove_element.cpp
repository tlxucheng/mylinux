#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int removeElement(std::vector<int>& nums, int val)
	{   
		std::vector<int>::iterator it;
		
	    for(it = nums.begin(); it != nums.end();)
		{
			if(val == *it)
			{
				it = nums.erase(it);
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
	std::vector<int> vc1 = {3,2,2,3};
	Solution test;
	
	std::cout << test.removeElement(vc1, 3) << std::endl;
	
	std::vector<int> vc2 = {0,1,2,2,3,0,4,2};
	std::cout << test.removeElement(vc2, 2) << std::endl;
	
	return 0;
}