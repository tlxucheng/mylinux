/* https://zhuanlan.zhihu.com/p/111806624 */

#include <iostream>
#include <vector>

class Solution {
public:
    int coinChange(std::vector<int>& coins, int amount) {
        std::vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for(int i = 1; i <= amount; ++i) {
            for(int j = 0; j < coins.size(); ++j) {
                if(i >= coins[j]) {
                    dp[i] = std::min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] > amount? -1: dp[amount];
    }
};
 
int main()
{
    Solution test;
	
	std::vector<int> coins = {1,2,5};
	int amount             = 11;

    std::cout << test.coinChange(coins, amount) << std::endl;
	
    return 0;	
}