#include <iostream>
#include <string>

class Solution {
public:
    int longestCommonSubsequence(std::string text1, std::string text2) {
        int dp[1001][1001] = {0};
		int ans            = 0;
		
		for(int i = 1; i <= text1.size(); i++)
		{
			for(int j = 1; j <= text2.size(); j++)
			if(text1[i-1] == text2[j-1])
			{
				dp[i][j] = dp[i-1][j-1] + 1;
			}
			else
			{
				dp[i][j] = std::max(dp[i][j-1], dp[i-1][j]);
			}
		}
		
		return dp[text1.size()][text2.size()];
    }
};

int main()
{
	Solution test;
	
	std::string text1 = "abc";
	std::string text2 = "abc";
	std::cout << test.longestCommonSubsequence(text1, text2) << std::endl;
	
	std::string text3 = "abc";
	std::string text4 = "def";
	std::cout << test.longestCommonSubsequence(text3, text4) << std::endl;
	
	std::string text5 = "abcde";
	std::string text6 = "ace";
	std::cout << test.longestCommonSubsequence(text5, text6) << std::endl;
	
	return 0;
}