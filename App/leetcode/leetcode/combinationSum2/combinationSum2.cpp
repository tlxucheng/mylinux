#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    void combinationSum2DFS(std::vector<int>& candidates, int target, int start, std::vector<int> &out, std::vector<std::vector<int>> &res)
	{
		if(0 == target)
		{
			res.push_back(out);
			return;
		}
		
	    for(int i = start; i < candidates.size(); i++)
		{
			if(i > start && candidates[i]==candidates[i-1])
		    {
				continue;
			}
			
			if(candidates[i] > target)
			{
				break;
			}

			out.push_back(candidates[i]);
			combinationSum2DFS(candidates, target - candidates[i], i+1, out, res);
			out.pop_back();
		}
		
	}

    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) 
	{
        std::vector<std::vector<int>> res;
		std::vector<int> out;
		
		sort(candidates.begin(),candidates.end());
		combinationSum2DFS(candidates, target, 0, out, res);
		
		return res;
    }
};

int main()
{
	Solution test;
	
	std::vector<int>   vec1     = {2,5,2,1,2};
	int                target1  = 5;
 	int                i        = 0;
	int                j        = 0;
	
	std::vector<std::vector<int>> res1 = test.combinationSum2(vec1, target1);
	
	for(i = 0; i < res1.size(); i++)
	{
		for(j = 0; j < res1[i].size(); j++)
		{
			std::cout << res1[i][j] << ",";
		}
		std::cout << std::endl;
	}
	
	std::vector<int>   vec2     = {10,1,2,7,6,1,5};
	int                target2  = 8;
 	
	std::vector<std::vector<int>> res2 = test.combinationSum2(vec2, target2);
	
	for(i = 0; i < res2.size(); i++)
	{
		for(j = 0; j < res2[i].size(); j++)
		{
			std::cout << res2[i][j] << ",";
		}
		std::cout << std::endl;
	}
	
	return 0;
}
