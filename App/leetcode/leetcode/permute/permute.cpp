/* https://blog.csdn.net/long_long_int/article/details/79930888 */

#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
	{
        std::vector<std::vector<int>> result;
		permutationrecusive(nums, 0, result);
		return result;
    }
	
	void permutationrecusive(std::vector<int> &num, int k, std::vector<std::vector<int>> &result)
	{
		if(k == num.size())
		{
			result.push_back(num);
			return;
		}
		
		for(int i = k; i < num.size(); i++)
		{
			std::swap(num[k], num[i]);
			permutationrecusive(num, k+1, result);
			std::swap(num[k], num[i]);
		}
	}
};

int main()
{
	Solution                         test;
	std::vector<std::vector<int>>    result;
	std::vector<int>                 nums = {1, 2, 3};
	
	result = test.permute(nums);
	
	for(int i = 0; i < result.size(); i++)
	{
		for(int j = 0; j < result[i].size(); j++)
		{
			std::cout << result[i][j] << ",";
		}
		std::cout << std::endl;
	}
	
	
	return 0;
}