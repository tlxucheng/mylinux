#include <iostream>
#include <string>

class Solution {
public:
    int chartoInt(char c)
	{
		return c-'A'+1;
	}

    int titleToNumber(std::string columnTitle)
	{
        int size_number = columnTitle.size();
		int result      = 0;
				
	
		for(int i = 0; i < size_number; i++)
		{
			if(i != 0)
			{
				result *= 26;
			}	
			
			result += chartoInt(columnTitle[i]);
		}
		
		return result;
    }
};

int main()
{
	Solution test;
	
	std::cout << test.titleToNumber("A") << std::endl;
	std::cout << test.titleToNumber("AB") << std::endl;
	std::cout << test.titleToNumber("ZY") << std::endl;
	std::cout << test.titleToNumber("FXSHRXW") << std::endl;
	
	return 0;
}