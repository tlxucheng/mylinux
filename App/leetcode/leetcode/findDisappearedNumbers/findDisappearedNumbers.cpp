#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
        std::vector<int> ret;
		std::vector<int>::iterator finded;
 		
		for(int i = 0; i < nums.size(); i++)
		{
			finded = std::find(nums.begin(), nums.end(), i+1);
			if(finded == nums.end())
			{
				ret.push_back(i+1);
			}
		}
		
		return ret;
    }
};

int main()
{
	Solution test;
	
	std::vector<int> nums1 = {4,3,2,7,8,2,3,1};
	for(auto val : nums1)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	std::vector<int> ret1 = test.findDisappearedNumbers(nums1);
	for(auto val : ret1)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	
	std::vector<int> nums2 = {1,1};
	for(auto val : nums2)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	std::vector<int> ret2 = test.findDisappearedNumbers(nums2);
	for(auto val : ret2)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	
	return 0;
}