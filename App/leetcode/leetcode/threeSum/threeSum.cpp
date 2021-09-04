#include <iostream>
#include <vector>
#include <algorithm>

class Solution 
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) 
	{
        std::vector<std::vector<int>> res;
		
		sort(nums.begin(), nums.end());
		
		for(int i = 0; i < nums.size(); i++)
		{
			if(i > 0 && nums[i] == nums[i-1])
			{
				continue;
			}
			
			int l = i + 1;
			int r = nums.size() - 1;
			int x = nums[i];
			
			while(l < r)
			{
				if(0 == x + nums[l] + nums[r])
				{
					res.push_back(std::vector<int>{x, nums[l], nums[r]});
					
					while(l < r && nums[l] == nums[l+1])
					{
						l++;
					}
					
					while(l < r && nums[r] == nums[r-1])
					{
						r--;
					}
					
					l++;
					r--;
				}
				else if(x + nums[l] + nums[r] < 0)
				{
					l++;
				}
				else
				{
					r--;
				}
			}
		}
		
		return res;

    }
};

int main()
{
	Solution test;
	
	std::vector<int> vc = {-1,0,1,2,-1,-4};
	
	std::vector<std::vector<int>> res = test.threeSum(vc);
				
	for(int i = 0; i < res.size(); i++)
	{
		std::vector<int> temp_res = res[i];
		for(int j = 0; j < temp_res.size(); j++)
		{
			std::cout << temp_res[j] << ",";
		}
		std::cout << std::endl;
	}
	
	return 0;
}