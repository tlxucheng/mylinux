#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2)
	{
		std::vector<int> nums3;
		int num = 0;
		std::vector<int>::iterator it;
		
		for(int i = 0; i < nums1.size(); i++)
		{
			num = nums1[i];
			for(it = nums2.begin(); it != nums2.end(); it++)
			{
				if(num == *it)
				{
					nums2.erase(it);
					nums3.push_back(num);
					break;
				}
			}
		}

		
		return nums3;
    }
};

int main()
{
	Solution test;
	int i = 0;
	
    std::vector<int> nums11 = {1,2,2,1};
	std::vector<int> nums12 = {2,2};
	std::vector<int> nums13 = test.intersect(nums11, nums12);
	for(i = 0; i < nums13.size(); i++)
	{
		std::cout << nums13[i] << " ";
	}
	std::cout << std::endl;
	
	std::vector<int> nums21 = {4,9,5};
	std::vector<int> nums22 = {9,4,9,8,4};
	std::vector<int> nums23 = test.intersect(nums21, nums22);
	for(i = 0; i < nums23.size(); i++)
	{
		std::cout << nums23[i] << " ";
	}
	std::cout << std::endl;
	
	std::vector<int> nums31 = {1,2,2,1};
	std::vector<int> nums32 = {2};
	std::vector<int> nums33 = test.intersect(nums31, nums32);
	for(i = 0; i < nums33.size(); i++)
	{
		std::cout << nums33[i] << " ";
	}
	std::cout << std::endl;
	
	std::vector<int> nums41 = {3,1,2};
	std::vector<int> nums42 = {1,1};
	std::vector<int> nums43 = test.intersect(nums41, nums42);
	for(i = 0; i < nums43.size(); i++)
	{
		std::cout << nums43[i] << " ";
	}
	std::cout << std::endl;
	
	return 0;
}