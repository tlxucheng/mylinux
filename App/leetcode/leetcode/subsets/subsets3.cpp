#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) 
	{
		std::vector<std::vector<int>> res;
		std::vector<int>              path;
		
		res.push_back({}); 
	    backtrack(nums, res, path, 0, nums.size());
		
        return res;
    }
	
	void backtrack(std::vector<int>& nums, std::vector<std::vector<int>> &res, std::vector<int> &path, int start_index, int n)
	{		
		for(int i = start_index; i < n; i++)
		{
			path.push_back(nums[i]);
			res.push_back(path);
			backtrack(nums, res, path, i+1, n);
			path.pop_back();
		}
	}
};

int main()
{
	Solution test;
	
	std::vector<std::vector<int>> res1;
	std::vector<int>              nums = {1,2,3};
	
	res1 = test.subsets(nums);
	std::cout << "res1.size: " << res1.size() << std::endl;
	for(int i = 0; i < res1.size(); i++)
	{
		for(int j = 0; j < res1[i].size(); j++)
		{
			std::cout << res1[i][j] << " ";
		} 
		std::cout << std::endl;
	}
	std::cout << std::endl;
	
	return 0;
}
