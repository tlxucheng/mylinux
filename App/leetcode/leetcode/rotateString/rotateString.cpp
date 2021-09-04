#include <iostream>
#include <string>

class Solution {
public:
    bool rotateString(std::string s, std::string goal) 
	{
		std::string::iterator it;
		char first_ch = s[0];
		int rotate = 0;
		
		if(s.size() != goal.size())
		{
			return false;
		}
		
		if(0 == s.size() && 0 == goal.size())
	    {
			return true;
		}			
	
        for(it = s.begin(); it != s.end(); it++)
        {			
	        if(s == goal)
			{
				return true;
			}
		    first_ch = s[0];
			s.erase(it);
			it--;
			s += first_ch;
			rotate++;
			if(rotate == s.size())
			{
				break;
			}
		}
		
        return false;
    }
};

int main()
{
	Solution test;
	
	std::string s1 = "abcde";
	std::string goal1 = "cdeab";
	std::cout << test.rotateString(s1, goal1) << std::endl; 

	std::string s2 = "abcde";
	std::string goal2 = "abced";
	std::cout << test.rotateString(s2, goal2) << std::endl; 
	
	std::string s3 = "";
	std::string goal3 = "";
	std::cout << test.rotateString(s3, goal3) << std::endl; 
	
	return 0;
}