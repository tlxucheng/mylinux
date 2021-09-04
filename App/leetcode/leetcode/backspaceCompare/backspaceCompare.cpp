#include <iostream>
#include <string>

class Solution {
public:
    void backspaceString(std::string &s)
	{
		std::string::iterator it;
		
	#if 0
		it = s.begin()+2;
		std::cout << *it << std::endl;
		
		s.erase(s.begin()+2-1, s.begin()+2+1);
		std::cout << s << std::endl;
	#endif
		
		for(it = s.begin(); it != s.end(); it++)
		{			
			if(*it == '#')
			{
				if(it == s.begin())
			    {
					s.erase(it, it+1);
					it--;
				}
				else if(it == s.end() - 1)
				{
					s.erase(it-1, it);
					it--;
				}
				else
				{
			        s.erase(it-1, it+1);
					it = it - 2;
				}
			}
		}
	}


    bool backspaceCompare(std::string s, std::string t) 
	{
        backspaceString(s);
		backspaceString(t);
   
        if(s == t)
		{
			return true;
		}
		
		return false;
    }
};

int main()
{
	Solution test;
	
	std::string s1 = "ab#c";
	std::string t1 = "ad#c";
	std::cout << test.backspaceCompare(s1, t1) << std::endl;
	
	std::string s2 = "ab##";
	std::string t2 = "c#d#";
	std::cout << test.backspaceCompare(s2, t2) << std::endl;
	
	std::string s3 = "a##c";
	std::string t3 = "#a#c";
	std::cout << test.backspaceCompare(s3, t3) << std::endl;

	std::string s4 = "a#c";
	std::string t4 = "b";
	std::cout << test.backspaceCompare(s4, t4) << std::endl;

	std::string s5 = "ab#cc#";
	std::string t5 = "ad#c";
	std::cout << test.backspaceCompare(s5, t5) << std::endl;
	
	return 0;
}