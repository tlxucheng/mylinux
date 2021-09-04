#include <iostream>
#include <vector>
#include <algorithm>

class Solution 
{
public:
    int maxProfit(std::vector<int>& prices) 
    {
        int buy=prices[0],ans=0;
        for(int i=1;i<prices.size();i++)
        {
            ans=std::max(ans,prices[i]-buy);
            buy=std::min(buy,prices[i]);
        }
        return ans;
    }
};

int main()
{
	Solution test;
	
	std::vector<int> prices1 = {7,1,5,3,6,4};
	std::cout << test.maxProfit(prices1) << std::endl;

	std::vector<int> prices2 = {7,6,4,3,1};
	std::cout << test.maxProfit(prices2) << std::endl;
	
	
	std::vector<int> prices3 = {7,1,6,2,10};
	std::cout << test.maxProfit(prices3) << std::endl;
	
	return 0;
}