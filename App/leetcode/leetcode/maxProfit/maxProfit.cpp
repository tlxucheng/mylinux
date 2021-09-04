#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxProfit(std::vector<int>& prices) 
	{
		std::vector<int> result;
		std::vector<int>::iterator it;
		
		if(1 == prices.size())
		{
			return 0;
		}			
	
		for(it = prices.begin(); it != prices.end()-1; it++)
		{
			result.push_back(*std::max_element(it+1, prices.end()) - *it);
		}
		
		int result_num = *std::max_element(result.begin(), result.end());
		if(result_num < 0)
	    {
			result_num = 0;
		}			
	
        return result_num;   
    }
};

int main()
{
	Solution test;
	
	std::vector<int> prices1 = {7,1,5,3,6,4};
	std::cout << test.maxProfit(prices1) << std::endl;

	std::vector<int> prices2 = {7,6,4,3,1};
	std::cout << test.maxProfit(prices2) << std::endl;
	
	return 0;
}