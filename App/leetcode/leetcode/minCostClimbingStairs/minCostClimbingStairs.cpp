#include <iostream>
#include <vector>

class Solution {
public:
    int minCostClimbingStairs(std::vector<int>& cost)
	{
		int n = cost.size();
        int dp[n+1];
		
		dp[0] = 0;
		dp[1] = 0;
		
		for(int i = 2; i <= n; i++)
		{
			dp[i] = std::min(dp[i-1]+cost[i-1], dp[i-2]+cost[i-2]);
		}
		
		return dp[n];
    }
};

int main()
{
	Solution test;
	
	std::vector<int> vec0 = {10,15};
	std::cout << test.minCostClimbingStairs(vec0) << std::endl;
	
	std::vector<int> vec1 = {10,15,20};
	std::cout << test.minCostClimbingStairs(vec1) << std::endl;
	
	std::vector<int> vec2 = {1,100,1,1,1,100,1,1,100,1};
	std::cout << test.minCostClimbingStairs(vec2) << std::endl;
	
	return 0;
}