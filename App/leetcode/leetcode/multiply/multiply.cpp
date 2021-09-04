#include <iostream>
#include <string>
#include <vector>

class Solution
{
public:
    std::string multiply(std::string num1, std::string num2) 
	{
		if("0" == num1 || "0" == num2)
		{
			return "0";
		}
		
        std::vector<int> res(num1.size() + num2.size(), 0);
		for(int i = num1.size() - 1; i >= 0; i--)
		{
			for(int j = num2.size() - 1; j >= 0; j--)
			{
				res[i+j+1] += (num1[i] - '0') * (num2[j] - '0');
				res[i+j] += res[i+j+1] / 10;
				res[i+j+1] %= 10;
			}
		}
		
		int k = 0;
		std::string ans;
		
		while(0 == res[k])
		{
			k++;
		}
		
		while(k < res.size())
		{
			ans += std::to_string(res[k++]);
		}
		
		return ans;
    }
};

int main()
{
	Solution test;
	
	std::cout << test.multiply("123", "456") << std::endl;
	
	
	return 0;
}