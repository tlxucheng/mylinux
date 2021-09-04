#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    int findleft(int index, std::string s, char c)
	{
		int dis = -1;
		
	    for(int i = index; i >= 0; i--)
		{
			if(s[i] == c)
			{
				dis = index - i;
				break;
			}
		}
		
		return dis;
	}
	
	int findright(int index, std::string s, char c)
	{
	    int dis = -1;

		for(int i = index; i < s.size(); i++)
		{
			if(s[i] == c)
			{
				dis = i - index;
				break;
			}
		}
		
		return dis;
	}

    std::vector<int> shortestToChar(std::string s, char c) 
	{
		std::vector<int> v(s.size(), 0);
		int left_dis  = 0;
		int right_dis = 0;
		
        for(int i = 0; i < s.size(); i++)
		{
			left_dis = findleft(i, s, c);
			right_dis = findright(i, s, c);
			if(-1 == left_dis)
			{
				v[i] = right_dis;
			}
			else if(-1 == right_dis)
			{
				v[i] = left_dis;
			}
			else
			{
			    v[i] = std::min(left_dis, right_dis);
			}
		}
		
		return v;
    }
};

int main()
{
	Solution test;
	int i = 0;
	
    std::string s1 = "loveleetcode";
	char c1 = 'e';
	std::vector<int> v1;
	v1 = test.shortestToChar(s1, c1);
	for(i = 0; i < v1.size(); i++)
	{
		std::cout << v1[i] << " ";
	}
	std::cout << std::endl;
	
	std::string s2 = "aaab";
	char c2 = 'b';
	std::vector<int> v2;
	v2 = test.shortestToChar(s2, c2);
	for(i = 0; i < v2.size(); i++)
	{
		std::cout << v2[i] << " ";
	}
	std::cout << std::endl;
	
	return 0;
}