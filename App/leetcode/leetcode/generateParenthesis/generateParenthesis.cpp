/* https://leetcode.com/problems/generate-parentheses/discuss/1415961/C%2B%2B-Solution-using-Backtracking */

#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) 
	{
        std::vector<std::string> res;
		std::string              path;

		backtracing(res, path, 0, 0, n);
		
		return res;
    }
	
	void backtracing(std::vector<std::string> &res, std::string path, int open, int close, int n)
	{
		if((2*n) == path.size())
	    {
			res.push_back(path);
			return;
		}			
	
	    if(open < n)
		{
			//path.push_back('(');  /* path必须传值 https://segmentfault.com/q/1010000014413358 */
			backtracing(res, path+'(', open+1, close, n);
		}
		if(close < open)
		{
			//path.push_back(')');
			backtracing(res, path+')', open, close+1, n);
		}
	
		return;
	}
};

int main()
{
	Solution test;
	
	std::vector<std::string> res;
	
	res = test.generateParenthesis(3);
	for(int i = 0; i < res.size(); i++)
	{
		std::cout << res[i] << std::endl;
	}
	std::cout << std::endl;
	
	return 0;
}