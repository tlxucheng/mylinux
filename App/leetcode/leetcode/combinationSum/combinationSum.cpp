/* https://www.cnblogs.com/wwj99/p/12376629.html */

#include <iostream>
#include <vector>
 
class Solution {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) 
	{
        std::vector<std::vector<int>> res;
        std::vector<int> out;
        		
	    combinationSumDFS(candidates, target, 0, out, res);
        return res;
    }
	
    void combinationSumDFS(std::vector<int>& candidates, int target, int start, std::vector<int>& out, std::vector<std::vector<int>>& res)
	{
		if(target < 0)
		{
			return;
		}
		
		if(0 == target)
		{
			res.push_back(out);
			return;
		}
		
		for(int i = start; i < candidates.size(); i++)
		{
			out.push_back(candidates[i]);
			combinationSumDFS(candidates, target - candidates[i], i, out, res);
			out.pop_back();
		}
	}
};

int main()
{
	Solution test;
	
	std::vector<int> candidates1 = {2,3,6,7};
	int              target1     = 7;
	
	std::vector<std::vector<int>> res1;
    res1 = test.combinationSum(candidates1, target1);
	for(int i = 0; i < res1.size(); i++)
	{
		for(int j = 0; j < res1[i].size(); j++)
		{
			std::cout << res1[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	
	std::vector<int> candidates2 = {1};
	int              target2     = 1;
	
	std::vector<std::vector<int>> res2;
    res2 = test.combinationSum(candidates2, target2);
	for(int i = 0; i < res2.size(); i++)
	{
		for(int j = 0; j < res2[i].size(); j++)
		{
			std::cout << res2[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	
	return 0;
}