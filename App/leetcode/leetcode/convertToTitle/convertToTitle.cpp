#include <iostream>
#include <string>
#include <map>

class Solution {
public:
    std::string convertToTitle(int columnNumber)
	{
        std::string ans;
									   
		while(columnNumber > 0)
        {
			char temp = 'A' + (columnNumber-1) % 26;
			ans = temp + ans;
			columnNumber = (columnNumber-1) / 26;
		}			
		
		return ans;
    }
};

int main()
{
	Solution test;
	
	std::cout << test.convertToTitle(1) << std::endl;
	std::cout << test.convertToTitle(26) << std::endl;
	std::cout << test.convertToTitle(28) << std::endl;
	std::cout << test.convertToTitle(701) << std::endl;
	std::cout << test.convertToTitle(2147483647) << std::endl;
	
	return 0;
}
