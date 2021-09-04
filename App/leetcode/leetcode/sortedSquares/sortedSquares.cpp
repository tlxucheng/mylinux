#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> sortedSquares(std::vector<int>& nums)
	{
        std::vector<int> sortedSquares_vec(nums.size(), 0);
		
		for(int i = 0; i < nums.size(); i++)
		{
			sortedSquares_vec[i] = nums[i] * nums[i];
		}
			
		sort(sortedSquares_vec.begin(), sortedSquares_vec.end());
			
		return sortedSquares_vec;
    }
};

int main()
{
	Solution test;
	
	std::vector<int> vec1;
	std::vector<int> nums1 = {-4,-1,0,3,10};
	int i = 0;
	
	vec1 = test.sortedSquares(nums1);
    for(i = 0; i < nums1.size(); i++)
    {
		std::cout << nums1[i] << " ";
	}		
    std::cout << std::endl;
	
	for(i = 0; i < vec1.size(); i++)
    {
		std::cout << vec1[i] << " ";
	}		
    std::cout << std::endl;
	
	return 0;
}