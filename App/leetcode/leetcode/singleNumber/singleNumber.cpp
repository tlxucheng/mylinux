#include <iostream>
#include <vector>

class Solution {
public:
    int singleNumber(std::vector<int>& nums)
	{
        int i   = 0;
		int ret = 0;
		
		for(i = 0; i < nums.size(); i++)
		{			
            ret ^= nums[i];
		}
		
		return ret;
    }
};

int main()
{
    Solution test;

    std::vector<int> vc1 = {2,2,1};
	std::cout << test.singleNumber(vc1) << std::endl;
	
	std::vector<int> vc2 = {4,1,2,1,2};
	std::cout << test.singleNumber(vc2) << std::endl;

    std::vector<int> vc3 = {1};
	std::cout << test.singleNumber(vc3) << std::endl;
	
	return 0;
}