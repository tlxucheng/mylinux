#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>

class Solution {
public:
    void addToHexa (std::string &res, int n) 
    {
        if ( n >= 0 && n <= 9)    res += std::to_string(n);
        if (n == 10)    res += "a";
        if (n == 11)    res += "b";
        if (n == 12)    res += "c";
        if (n == 13)    res += "d";
        if (n == 14)    res += "e";
        if (n == 15)    res += "f";
    }
    
    std::string toHex (int a)
    {
        unsigned int num = a;
        
        if (num == 0)
            return "0";
        if (num < 0)
            num = pow(2,32) - (-1 * num);
            
        std::string res; 
        while (num != 0) {
            addToHexa(res, num % 16); 
            num /= 16;
        }
            
        std::reverse(res.begin(), res.end());
        return res;
    }
};


int main()
{
	Solution test;
	
	std::cout << test.toHex(26) << std::endl;
	std::cout << test.toHex(0) << std::endl;	
	std::cout << test.toHex(32) << std::endl;	
	std::cout << test.toHex(1) << std::endl;	
	std::cout << test.toHex(-1) << std::endl;	
	std::cout << test.toHex(-2) << std::endl;	
	std::cout << test.toHex(-2147483648) << std::endl;	
	
	return 0;
}