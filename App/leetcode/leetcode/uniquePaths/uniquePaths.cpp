/* https://www.cnblogs.com/wzw0625/p/13531496.html */

#include <iostream>

class Solution {
public:
    int uniquePaths(int m, int n)
	{
        int dp[m][n];
		
		for(int i = 0; i < m; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(0 == i || 0 == j)
				{
					dp[i][j] = 1;
				}
				else
				{
					dp[i][j] = dp[i-1][j] + dp[i][j-1];
				}
			}
		}
		
		return dp[m-1][n-1];
    }
};

int main()
{
	Solution test;
	
	std::cout << test.uniquePaths(3, 7) << std::endl;
	std::cout << test.uniquePaths(3, 2) << std::endl;

	return 0;
}
