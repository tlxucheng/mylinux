#include <iostream>
#include <algorithm>
#include <vector>

class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) 
	{
        double ret = 0.00000;
		std::vector<int> nums3(nums1.size()+nums2.size());
		int middle = 0;
		
		merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), nums3.begin());
		
		middle = nums3.size()/2;
        if(0 == nums3.size() % 2)
		{
			ret = (nums3[middle] + nums3[middle-1])/2.00000;
		}
		else 
		{	
			ret = nums3[middle]/1.00000;
		}
		
		return ret;
    }
};

int main()
{
	Solution test;
	
	std::vector<int> nums21 = {1,3};
    std::vector<int> nums22 = {2};
	std::cout << test.findMedianSortedArrays(nums21, nums22) << std::endl;
	
	std::vector<int> nums1 = {1,2};
    std::vector<int> nums2 = {3,4};
	std::cout << test.findMedianSortedArrays(nums1, nums2) << std::endl;
 
	std::vector<int> nums31 = {0,0};
    std::vector<int> nums32 = {0,0};
	std::cout << test.findMedianSortedArrays(nums31, nums32) << std::endl;
	
	std::vector<int> nums41;
    std::vector<int> nums42 = {1};
	std::cout << test.findMedianSortedArrays(nums41, nums42) << std::endl;

	std::vector<int> nums51 = {2};
    std::vector<int> nums52;
	std::cout << test.findMedianSortedArrays(nums51, nums52) << std::endl;	
	
	return 0;
}