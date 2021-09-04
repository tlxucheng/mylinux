#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    std::string restoreString(std::string s, std::vector<int>& indices) 
	{
		std::string res(s.size(), 'a');
		
        for(int i = 0;i < s.size(); i++)
		{
			res[indices[i]] = s[i];
		}
		
        return res;		
    }
};

int main()
{
    Solution test;
	
	std::vector<int> vc1 = {4,5,6,7,0,2,1,3};
	
	std::cout << test.restoreString("codeleet", vc1) << std::endl;
	
	return 0;
}