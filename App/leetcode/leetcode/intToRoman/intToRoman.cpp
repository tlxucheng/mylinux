#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    std::string intToRoman(int num) 
	{
        std::vector<int>          value = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
		std::vector<std::string>  sym   = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
		std::string               res; 
		
		for(int i = 0; i < value.size(); i++)
		{
			while(num >= value[i])
			{
				num -= value[i];
				res += sym[i];
			}
		}
			
		return res;
    }
};

int main()
{
	Solution test;
	
	std::cout << test.intToRoman(1994) << std::endl;
	
	std::cout << test.intToRoman(58) << std::endl;

	std::cout << test.intToRoman(9) << std::endl;

	std::cout << test.intToRoman(3) << std::endl;

	return 0;
}