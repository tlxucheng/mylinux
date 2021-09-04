#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) 
	{
		std::vector<std::vector<int>> res;
		std::vector<int>              path;

	    backtracking(nums, res, path, 0);
		
        return res;
    }
	
	void backtracking(std::vector<int>& nums, std::vector<std::vector<int>> &res, std::vector<int> &path, int start_index)
	{
		if(start_index == nums.size())
		{
		    res.push_back(path);
		}
        else		
		{
			path.push_back(nums[start_index]);
			backtracking(nums, res, path, start_index+1);
			path.pop_back();
			backtracking(nums, res, path, start_index+1);
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