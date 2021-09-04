#include <iostream>
#include <string>
#include <algorithm>

class Solution {
public:
    int firstUniqChar(std::string s) {
        std::vector<int> hash(256, 0);

		for(int i = 0; i < s.size(); i++)
		{
			hash[s[i]]++;
		}
		
		for(int i = 0; i < s.size(); i++)
		{
			if(hash[s[i]] == 1)
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
