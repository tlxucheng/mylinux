#include <iostream>
#include <string>

class Solution {
public:
    int myAtoi(std::string s) 
	{
        long result = 0;
		int negative = 1;
		int get_flag = 0;
		int nums = 0;
		
	    if(' ' != s[0] && '+' != s[0] && '-' != s[0] && (s[0] < '0' || s[0] > '9'))
		{
			return 0;
		}				
		
		for(int i = 0; i < s.size(); i++)
		{
			if(' ' == s[i])
			{
				if(i == 0)
				{
				    continue;
				}
				else if(result != 0)
				{
					break;
				}
			}
			else if('-' == s[i])
			{
				if(i > 0)
			    {
					if('0' <= s[i-1] <= '9')
					{
					    return 0;
					}
				}
				
				if(get_flag)
				{
					return 0;
				}
				else
				{
				    negative = -1;
					get_flag = 1;
				}
			}		
			else if('+' == s[i])
			{
				if(i > 0)
			    {
					if('0' <= s[i-1] <= '9')
					{
					    return 0;
					}
				}
				
				if(get_flag || result > 0)
                {
					return 0;
				}
				else
				{
				    negative = 1;
					get_flag = 1;
				}
			}
			else if(s[i] < '0' || s[i] > '9')
			{
				if(s[i] == '-' || s[i] == '+')
			    {
			        result = 0;
				}
				else 
				{
					break;
				}
			}
			else 
			{
				result = 10*result + (s[i] - '0');
				if(negative == 1 && result >= 2147483647)
				{
					return 2147483647;
				}
				else if(negative == -1 && result >= 2147483648)
				{
					return -2147483648;
				}
			}
		}
		
		return negative*result;
    }
};

int main()
{
	Solution test;
	
	std::string s1 = "42";
	std::cout << test.myAtoi(s1) << std::endl;
	
	std::string s2 = "   -42";
	std::cout << test.myAtoi(s2) << std::endl;

	std::string s3 = "4193 with words";
	std::cout << test.myAtoi(s3) << std::endl;
	
	std::string s4 = "words and 987";
	std::cout << test.myAtoi(s4) << std::endl;

	std::string s5 = "-91283472332";
	std::cout << test.myAtoi(s5) << std::endl;

	std::string s6 = "+1";
	std::cout << test.myAtoi(s6) << std::endl;

	std::string s7 = "+-12";
	std::cout << test.myAtoi(s7) << std::endl;

	std::string s8 = "   -42";
	std::cout << test.myAtoi(s8) << std::endl;

	std::string s9 = "3.14159";
	std::cout << test.myAtoi(s9) << std::endl;

	std::string s10 = "00000-42a1234";
	std::cout << test.myAtoi(s10) << std::endl;
	
	return 0;
}