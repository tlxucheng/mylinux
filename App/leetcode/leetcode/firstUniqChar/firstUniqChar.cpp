#include <iostream>
#include <string>
#include <algorithm>

class Solution {
public:
    int firstUniqChar(std::string s) {
        for(int i = 0; i < s.size(); i++)
		{
			if(1 == std::count(s.begin(), s.end(), s[i]))
			{
				return i;
			}
		}
		
		return -1;
    }
};

int main()
{
	Solution test;
	
	std::string s1 = {"leetcode"};
	std::cout << test.firstUniqChar(s1) << std::endl;

	std::string s2 = {"loveleetcode"};
	std::cout << test.firstUniqChar(s2) << std::endl;	
	
	std::string s3 = {"aabb"};
	std::cout << test.firstUniqChar(s3) << std::endl;	
	
	return 0;
}