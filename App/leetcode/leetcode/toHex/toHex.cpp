#include <iostream>
#include <string>
#include <math.h>

class Solution {
public:
    std::string toHex(int a) 
	{
        std::string hex_str;
		int remainder = 0;
		char c        = '0';
		
		unsigned int num = a;
		
		if(num > 0)
        {
			while(0 != num)
			{
				remainder = num %16;
				if(remainder < 10)
	            {
					c = remainder + '0';
				}
				else
			    {
					if(10 == remainder)
					{
						c = 'a';
					}
				    else if(11 == remainder)
					{
						c = 'b';
					}
					else if(12 == remainder)
					{
					    c = 'c';
					}
					else if(13 == remainder)
					{
					    c = 'd';
					}
					else if(14 == remainder)
					{
						c = 'e';
					}
					else if(15 == remainder)
					{
					    c = 'f';
					}
				}
				
				hex_str = c + hex_str;
				num = num/16;
			}
		}
		else if(0 == num)
		{
			hex_str = "0";
		}
		
		return hex_str;
    }
};

int main()
{
	Solution test;
	
	
	std::cout << test.toHex(26) << std::endl;
	std::cout << test.toHex(160) << std::endl;
	std::cout << test.toHex(0) << std::endl;	
	std::cout << test.toHex(32) << std::endl;	
	std::cout << test.toHex(1) << std::endl;	
	std::cout << test.toHex(-1) << std::endl;	
	
	return 0;
}