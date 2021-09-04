/* https://leetcode.com/problems/climbing-stairs/discuss/1315296/C%2B%2B-6-line-code-dynamic-100-fast-Solution */

#include <iostream>
#include <vector>

class Solution {
public:
    int climbStairs(int n) {
        std::vector<int> dp(46);
		
		dp[0] = 1;
		dp[1] = 2;
		for(int i = 2; i < n; i++)
		{
			dp[i] = dp[i-1] + dp[i-2];
		}
		
		return dp[n-1];
    }
};

int main()
{
	Solution test;
	
	std::cout << test.climbStairs(1) << std::endl;
    std::cout << test.climbStairs(2) << std::endl;
	std::cout << test.climbStairs(3) << std::endl;
	std::cout << test.climbStairs(4) << std::endl;

	return 0;
}
