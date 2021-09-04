#include <iostream>
#include <string>

class Solution {
public:
    bool isPal(std::string &s, int i, int j) {
        while(i < j && s[i] == s[j]) {
            i++;
            j--;
        }
        
        return i>=j ? true : false;
    }
    bool validPalindrome(std::string s) {
        int i = 0, j = s.length()-1;
        
        while(i < j) {
            if(s[i] != s[j]) {
				//remove ith char and check OR remove jth char and check
                return isPal(s, i+1, j) || isPal(s, i, j-1);
            }
            
            i++;            
            j--;
        }
        
        return true;
    }
};

int main()
{
	Solution test;
	
	std::cout << test.validPalindrome("eedede") << std::endl;
	
	std::cout << test.validPalindrome("aba") << std::endl;
    std::cout << test.validPalindrome("abca") << std::endl;
    std::cout << test.validPalindrome("abc") << std::endl;
	
	return 0;
}