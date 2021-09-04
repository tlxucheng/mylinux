#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target)
	{
        int left = 0;
		int right = nums.size() - 1;
		int middle = (right - left)/2 + left;
		int start = -1;
		int end = -1;
		std::vector<int> rec;
 
        if(0 != nums.size())
        {
			while(left <= right)
			{
				if(nums[middle] == target)
				{
					start = end = middle;
					if(middle + 1 <= nums.size() - 1)
					{
						while(nums[middle+1] == target)
						{
							end = middle+1;
							middle++;
						}
					}
					
		            if(middle - 1 >= 0)
					{
						while(nums[middle-1] == target)
						{
							start = middle - 1;
							middle--;
						}
					}
					
					break;
				}
				else if(nums[middle] < target)
				{
					left = middle + 1;
					middle = (right - left)/2 + left; 
				}
				else 
				{
					right = middle - 1;
					middle = (right - left)/2 + left; 
				}				
			}
		}
		
		rec.push_back(start);
		rec.push_back(end);
		
		return rec;
    }
};

int main()
{
	Solution test;	
	
	std::vector<int> nums1 = {5,7,7,8,8,10};
	std::vector<int> rec1;
	rec1 = test.searchRange(nums1, 8);
	std::cout << rec1[0] << " " << rec1[1] << std::endl;
	
	std::vector<int> nums3;
	std::vector<int> rec3;
	rec3 = test.searchRange(nums3, 6);
	std::cout << rec3[0] << " " << rec3[1] << std::endl;
	
	std::vector<int> nums4 = {1};
	std::vector<int> rec4;
	rec4 = test.searchRange(nums4, 6);
	std::cout << rec4[0] << " " << rec4[1] << std::endl;
	
	std::vector<int> nums2 = {5,7,7,8,8,10};
	std::vector<int> rec2;
	rec2 = test.searchRange(nums2, 6);
	std::cout << rec2[0] << " " << rec2[1] << std::endl;
	
	std::vector<int> nums5 = {1};
	std::vector<int> rec5;
	rec5 = test.searchRange(nums5, 1);
	std::cout << rec5[0] << " " << rec5[1] << std::endl;
	
	
	return 0;
}