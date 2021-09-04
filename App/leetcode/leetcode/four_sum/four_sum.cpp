#include <iostream>
#include <algorithm>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target)
	{
        std::vector<std::vector<int>>  foursum_vec;

		for(int i = 0; i < nums.size())
		
        return foursum_vec;		
    }
};

void my_print(int i)
{
	std::cout << i << " ";
}

int main()
{
	std::vector<int> vc = {-1,2,1,-2};
    std::for_each(vc.begin(), vc.end(), my_print);
	std::cout << std::endl;
	
	std::sort(vc.begin(), vc.end());
    std::for_each(vc.begin(), vc.end(), my_print);
	std::cout << std::endl;
	
	return 0;
}