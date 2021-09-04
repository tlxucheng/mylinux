#include <iostream>
#include <string>
#include <stack>

class Solution {
public:
    std::string decodeString(std::string s)
	{
        std::stack<int> valueStack;
		std::stack<std::string> stringStack;
		
		for(int i = 0; i < s.length(); i++)
		{
			char ch = s[i];
			if(isdigit(ch))
			{
				int val = 0;
				while(i < s.length() && isdigit(s[i]))
				{
					val = val * 10 + (s[i] - '0');
					i++;
				}
				valueStack.push(val);
				i--;
				continue;
			}
			
			if(ch == '[' || isalpha(ch))
			{
				stringStack.push(std::string(1, ch));
				continue;
			}
			
			if(ch == ']')
			{
				std::string str;
				while(stringStack.top() != "[")
				{
					str = stringStack.top() + str;
					stringStack.pop();
				}
				stringStack.pop();
				int c = valueStack.top();
				valueStack.pop();
				
				std::string fullstr;
				while(c-- > 0)
				{
					fullstr += str;
				}
				stringStack.push(fullstr);
			}
		}
		
		std::string ret = "";
		while(!stringStack.empty())
		{
			ret = stringStack.top() + ret;
			stringStack.pop();
		}
		
		return ret;
    }
};

int main()
{
	Solution test;
	std::string ret;
	
	ret = test.decodeString("3[a]2[bc]");
	if("aaabcbc" == ret)
	{
		std::cout << "decodeString1 success" << std::endl;
	}
	else
	{
	    std::cout << "decodeString1 fail" << std::endl;
	}
	
    ret = test.decodeString("3[a2[c]]");
	if("accaccacc" == ret)
	{
		std::cout << "decodeString2 success" << std::endl;
	}
	else
	{
	    std::cout << "decodeString2 fail" << std::endl;
	}
	
	return 0;
}