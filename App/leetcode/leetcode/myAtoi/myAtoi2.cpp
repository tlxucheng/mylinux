#include <iostream>
#include <string>

#define INT_MAX 2147483647
#define INT_MIN -2147483648

class Solution {
public:
    int myAtoi(std::string s) 
	{
        int res = 0, n = s.size(), i = 0;
		bool negative = false;
		bool overflow = false;
		while(  i<n && s[i] == ' '  ){
			i++;
		}
		
		if(i<n && s[i]=='-'){
			negative = true;
			i++;
		}
		else if(i<n && s[i] == '+')
			i++;
		int t;
		while(i<n && s[i]<='9'&& s[i]>='0'){
			t = s[i] - '0';
			// Checking overflow
			if(res>INT_MAX/10 || (res==INT_MAX/10 && t > 7) )
			{
				overflow = true;
				break;
			}
			res  = res*10 + t;
			i++;
		}
		
		if(overflow == true){
			if(negative)
				return INT_MIN;
			else
				return INT_MAX;
		}
		
		if(negative )
			return (-1)*res;
		return res;
        
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
