#include <iostream>
#include <string>

class Solution {
public:
    std::string defangIPaddr(std::string address) 
	{
        std::string res;
		
		for(int i = 0; i < address.size(); i++)
		{
			if(address[i] == '.')
			{
				res += "[.]";
			}
			else
			{
				res += address[i];
			}
		}
		
		return res;
    }
};

int main()
{
	Solution test;
	
	std::cout << test.defangIPaddr("1.1.1.1") << std::endl;
	
	return 0;
}