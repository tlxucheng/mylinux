#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    std::string toHex(int num) {
        std::string res = "";
        if(num == 0){
            return "0";
        }
        std::vector<char> vec = {
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
            'a', 'b', 'c', 'd', 'e', 'f'
        };
        unsigned int n = num;
        while(n != 0){
            std::string tmp(1, vec[n%16]);
            res = tmp + res;
            n /= 16;
        }
        return res;
    }
};


int main()
{
	Solution test;
	
	std::cout << test.toHex(160) << std::endl;
	
	std::cout << test.toHex(26) << std::endl;
	std::cout << test.toHex(0) << std::endl;	
	std::cout << test.toHex(32) << std::endl;	
	std::cout << test.toHex(1) << std::endl;	
	std::cout << test.toHex(-1) << std::endl;	
	std::cout << test.toHex(-2) << std::endl;	
	std::cout << test.toHex(-2147483648) << std::endl;	
	
	return 0;
}