#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    std::string addStrings(std::string num1, std::string num2)
	{
        std::string sum;

		int length    = std::max(num1.size(), num2.size());
		char add_bit  = '0';
		int i         = 0;
		int diff_size = 0;
				
		if(num1.size() > num2.size())
		{
			diff_size = num1.size() - num2.size();
			for(i = 0; i < diff_size; i++)
			{
				num2.insert(num2.begin(), '0');
			}
		}
		else if(num1.size() < num2.size())
		{
			diff_size = num2.size() - num1.size();
		    for(i = 0; i < diff_size; i++)
			{
				num1.insert(num1.begin(), '0');
			}
		}
		
		for(i = length - 1; i >= 0; i--)
		{
			if(num1[i] - '0' + num2[i] - '0' + add_bit - '0' >= 10)
			{
				sum.insert(sum.begin(), (num1[i] - '0' + num2[i] - '0' + add_bit - '0')%10 + '0');
				add_bit = '1';
			}
			else 
			{
				sum.insert(sum.begin(), num1[i] - '0' + num2[i] - '0' + add_bit - '0' + '0');
				add_bit = '0';
			}
		}
		
		if('1' == add_bit)
	    {
			sum.insert(sum.begin(), '1');
		}		
  
        return sum;		
    }
};

int main()
{
	Solution test;
	
	std::string num9 = "9133";
	std::string num10 = "0";
    std::cout << test.addStrings(num9, num10) << std::endl;
	
	std::string num1 = "11";
	std::string num2 = "123";
	
	std::cout << test.addStrings(num1, num2) << std::endl;
	
	std::string num3 = "19";
	std::string num4 = "123";
    std::cout << test.addStrings(num3, num4) << std::endl;

	std::string num5 = "1001";
	std::string num6 = "129";
    std::cout << test.addStrings(num5, num6) << std::endl;

	std::string num7 = "1";
	std::string num8 = "9";
    std::cout << test.addStrings(num7, num8) << std::endl;
	
	return 0;
}