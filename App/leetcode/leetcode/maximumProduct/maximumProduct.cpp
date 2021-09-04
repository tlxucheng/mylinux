#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maximumProduct(std::vector<int>& nums) 
	{
        int n = nums.size();
		sort(nums.begin(), nums.end());
		int a1 = nums[n-1]*nums[n-2]*nums[n-3];
		int a2 = nums[0]*nums[1]*nums[n-1];
		
		return std::max(a1,a2);
    }
};

int main()
{
	Solution test;
	
	std::vector<int> v1 = {1,2,3};
	std::cout << test.maximumProduct(v1) << std::endl;

	std::vector<int> v2 = {1,2,3,4};
	std::cout << test.maximumProduct(v2) << std::endl;
	
    std::vector<int> v3 = {-1,-2,-3};
	std::cout << test.maximumProduct(v3) << std::endl;
	
	return 0;
}