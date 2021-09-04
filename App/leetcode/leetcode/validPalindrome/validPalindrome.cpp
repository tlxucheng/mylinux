#include <iostream>
#include <string>

class Solution {
public:
    bool validPalindrome(std::string s) 
	{
        int count_diff = 0;
		int count_same = 0;
		std::string::iterator it_begin = s.begin();
		std::string::iterator it_end = s.end() - 1;
		
		while(it_begin < it_end)
		{
			if(*it_begin != *it_end)
			{
				count_diff++;
				if(count_diff > 1)
				{
					return false;
				}
			}
			else 
			{
				count_same++;
			}
			
			it_begin++;
		    it_end--;
		}
		
		if(0 == count_same)
	    {
		    return false;
		}			
	
		return true;
    }
};

int main()
{
	Solution test;
	
	std::cout << test.validPalindrome("eedede") << std::endl;
	
	std::cout << test.validPalindrome("aba") << std::endl;
    std::cout << test.validPalindrome("abca") << std::endl;
    std::cout << test.validPalindrome("abc") << std::endl;
	
	return 0;
}