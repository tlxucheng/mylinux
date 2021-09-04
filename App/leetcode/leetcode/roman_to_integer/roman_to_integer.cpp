#include <iostream>
#include <string>
#include <stack>

class Solution {
public:
    int romanToInt(std::string s);  
};

int Solution::romanToInt(std::string s)
{
    int sum = 0;
    int num = 0;
    std::stack<int> reverse_num;
    int latest_num = 0;

    for(int i = 0; i < s.size(); i++)
    {
	    if(s[i] == 'I')
	    {
			num = 1;
		}
		else if(s[i] == 'V')
	    {
			num = 5;
		}
		else if(s[i] == 'X')
		{
			num = 10;
		}
		else if(s[i] == 'L')
		{
			num = 50;
		}
		else if(s[i] == 'C')
		{
			num = 100;
		}
		else if(s[i] == 'D')
		{
			num = 500;
		}
		else if(s[i] == 'M')
		{
			num = 1000;
		}
        sum += num;

		if(!reverse_num.empty())
		{
			latest_num = reverse_num.top();
			if(latest_num < num)
			{
				sum -= 2*latest_num;
			}
			reverse_num.pop();
        }

		reverse_num.push(num);
	}

	return sum;
}

int main()
{
    Solution test;

	std::cout << test.romanToInt("III") << std::endl;
	std::cout << test.romanToInt("IV") << std::endl;
	std::cout << test.romanToInt("MCMXCIV") << std::endl;

	return 0;
}
