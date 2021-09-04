#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> combine(int n, int k) 
	{
		std::vector<std::vector<int>> res;
		std::vector<int>              path;
		
	    backtrack(res, path, 0, n, k);
		
        return res;
    }
	
	void backtrack(std::vector<std::vector<int>> &res, std::vector<int> &path, int start_index, int n, int k)
	{
		if(k == path.size())
		{
			res.push_back(path);
			return;
		}
		
		for(int i = start_index; i < n; i++)
		{
			path.push_back(i+1);
			backtrack(res, path, i+1, n, k);
			path.pop_back();
		}
	}
};

int main()
{
	Solution test;
	
	std::vector<std::vector<int>> res1;
	
	res1 = test.combine(4, 2);
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