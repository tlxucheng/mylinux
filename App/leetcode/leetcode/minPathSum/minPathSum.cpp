#include <iostream>
#include <vector>

class Solution 
{
public:
    int minPathSum(std::vector<std::vector<int>>& grid)
	{
        int m = grid.size();
		int n = grid[0].size();
		
		int dp[m][n];
		
		dp[0][0] = grid[0][0];
		
		for(int i = 0; i < m; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(0 == i && 0 == j)
				{
					continue;
				}
				if(0 == i)
				{
					dp[i][j] = grid[i][j] + dp[i][j-1];
				}
				else if(0 == j)
				{
					dp[i][j] = grid[i][j] + dp[i - 1][j];
				}
				else 
				{
					dp[i][j] = grid[i][j] + std::min(dp[i-1][j], dp[i][j-1]);
				}
			}
		}
		
		return dp[m-1][n-1];
    }
};

int main()
{
	Solution test;

	std::vector<std::vector<int>> mat1 = {{1,3,1},{1,5,1},{4,2,1}};
	for(int i = 0; i < mat1.size(); i++)
	{
		for(int j = 0; j < mat1[i].size(); j++)
		{
			std::cout << mat1[i][j] << " ";
		}
		
		std::cout << std::endl;
	}
	std::cout << test.minPathSum(mat1) << std::endl;
	
	std::vector<std::vector<int>> mat2 = {{1,3,1},{1,1,1},{4,2,1}};
	for(int i = 0; i < mat2.size(); i++)
	{
		for(int j = 0; j < mat2[i].size(); j++)
		{
			std::cout << mat2[i][j] << " ";
		}
		
		std::cout << std::endl;
	}
	std::cout << test.minPathSum(mat2) << std::endl;

	return 0;
}