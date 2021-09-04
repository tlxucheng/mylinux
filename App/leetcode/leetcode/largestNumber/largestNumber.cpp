/* https://leetcode.com/problems/largest-number/discuss/1366378/C%2B%2B-Easy-Code */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    bool static compareFun(int a, int b)
	{
		std::string str_a = std::to_string(a);
	    std::string str_b = std::to_string(b);
		
		return (str_a + str_b) > (str_b + str_a);
	}

    std::string largestNumber(std::vector<int>& nums)
	{
		std::string res;
		
		std::sort(nums.begin(), nums.end(), compareFun);
		
        for(int i = 0; i < nums.size(); i++)
		{
			res += std::to_string(nums[i]);
		}
		
	    if('0' == res[0] && res.length() > 1)
		{
			res = res.substr(0,1);
		}
		
		return res;
    }
};

int main()
{
	Solution test;
	
	std::vector<int> nums = {3,30,34,5,9};
	
	std::cout << test.largestNumber(nums) << std::endl;
	
	return 0;
}