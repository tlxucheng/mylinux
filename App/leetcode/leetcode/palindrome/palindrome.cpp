#include <iostream>
#include <sstream>

class Solution
{
public:
    bool isPalindrome(int x);
private:
	
};

bool Solution::isPalindrome(int x)
{
    std::stringstream ss;

	ss << x;

	std::string str = ss.str();

	std::cout << str << std::endl;

    int size = str.size();

    for(int i = 0; i < str.size(); i++)
	{
		if(str[i] != str[size-i-1])
	    {
			return false;
		}
	}

	return true;
}

int main()
{
    Solution test;

	std::cout << test.isPalindrome(-123) << std::endl;
	std::cout << test.isPalindrome(121) << std::endl;

	return 0;
}
