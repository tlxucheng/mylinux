#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) 
	{
		std::vector<std::vector<int>> res;
		std::vector<int>              path;
		
		sort(nums.begin(), nums.end()); /* 必须有 */
	    backtrack(nums, res, path, 0, nums.size());
		
        return res;
    }
	
	void backtrack(std::vector<int>& nums, std::vector<std::vector<int>> &res, std::vector<int> &path, int start_index, int n)
	{		
	    if(visited.find(path) == visited.end())
		{
			visited[path] = true;
		    res.push_back(path);
		}
	
		for(int i = start_index; i < n; i++)
		{
			path.push_back(nums[i]);
			backtrack(nums, res, path, i+1, n);
			path.pop_back();
		}
	}
	
private:
    std::map<std::vector<int>, bool> visited;
};

int main()
{
	Solution test;
	
	std::vector<std::vector<int>> res1;
	std::vector<int>              nums = {4,4,4,1,4};
	
	res1 = test.subsetsWithDup(nums);
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
