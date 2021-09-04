#include <iostream>
#include <string>

class Solution {
public:
    std::string removeDuplicates(std::string s) 
	{
		std::string::iterator it;
		int remove_flag = 0;
		
		do
		{	
			remove_flag = 0;

			if(s.size() <= 1)
			{
				return s;
			}
				
			for(it = s.begin(); it != s.end() - 1;)
			{
				if(*it == *(it+1))
				{
					remove_flag = 1;
					s.erase(it);
					s.erase(it);
				}
				else
				{
					++it;
				}
			}	
					
		}while(remove_flag);		
		
		return s;
    }
};

int main()
{
    Solution test;

	std::string str4 = "aababaab";
	std::cout << test.removeDuplicates(str4) << std::endl;
	
	std::string str3 = "aaaaaaaa";
	std::cout << test.removeDuplicates(str3) << std::endl;
	
	std::string str = "abbaca";
	std::cout << test.removeDuplicates(str) << std::endl;
	
	std::string str2 = "azxxzy";
	std::cout << test.removeDuplicates(str2) << std::endl;
	
	return 0;
}