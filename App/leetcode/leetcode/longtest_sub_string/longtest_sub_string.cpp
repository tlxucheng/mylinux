#include <iostream>
#include <string>
#include <algorithm>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s)
	{		
        int           i    = 0;
		int           j    = 0;
	    int  max_length    = 0;
	 
	    if(s.empty())
        {
			return 0;
		}			
        else if(1 == s.size())
		{
			return 1;
		}
		
        for(int i = 0; i < s.size()-1; i++)
		{			
			for(int j = i+1; j < s.size(); j++)
			{
				if(s[j] == s[i])
				{			
                    max_length = std::max(max_length, j - i);
					break;
				}
			}
		}
			
		return std::max(max_length, j - i);
    }
};

int main()
{
	Solution test;
	
	std::string s1 = {"abcabcbb"};
	std::cout << test.lengthOfLongestSubstring(s1) << std::endl;
	
	std::string s2 = {"bbbbb"};
	std::cout << test.lengthOfLongestSubstring(s2) << std::endl;	
	
	std::string s3 = {"pwwkew"};
	std::cout << test.lengthOfLongestSubstring(s3) << std::endl;		
	
	std::string s4 = {""};
	std::cout << test.lengthOfLongestSubstring(s4) << std::endl;

	std::string s5 = {" "};
	std::cout << test.lengthOfLongestSubstring(s5) << std::endl;
	
	std::string s6 = {"au"};
	std::cout << test.lengthOfLongestSubstring(s6) << std::endl;
	
	std::string s7 = {"aab"};
	std::cout << test.lengthOfLongestSubstring(s7) << std::endl;
	
	return 0;
}
