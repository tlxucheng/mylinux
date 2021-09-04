#include <iostream>
#include <numeric>
#include <string>
#include <vector>

class Solution {
public:
    std::string shiftingLetters(std::string s, std::vector<int>& shifts)
	{
		unsigned long sum = 0;
		int i = 0;
		int diff = 0;
		
		for(i = 0; i < shifts.size(); i++)
		{
			shifts[i] = shifts[i]%26;
		}			
	
		for(i = 0; i < s.size(); i++)
	    {
            sum = std::accumulate(shifts.begin()+i , shifts.end(), 0);
			if(s[i] + sum > 'z')
			{
				diff = (s[i] - 96 + sum)%('z' - 96);
				if(diff == 0)
			    {
					s[i] = 'z';
				}
				else
				{
				    s[i] = diff + 'a' - 1;
				}
			}
			else 
		    {
				s[i] += sum;
			}
		}

		return s;
    }
};


int main()
{
	Solution test;
	
	std::string s = "abc";
	std::vector<int> shifts = {3, 5, 9};
	std::cout << test.shiftingLetters(s, shifts) << std::endl;

	std::string s3 = "xyz";
	std::vector<int> shifts3 = {1, 2, 3};
	std::cout << test.shiftingLetters(s3, shifts3) << std::endl;
	
	std::string s2 = "bad";
	std::vector<int> shifts2 = {10, 20, 30};
	std::cout << test.shiftingLetters(s2, shifts2) << std::endl;

	std::string s4 = "z";
	std::vector<int> shifts4 = {52};
	std::cout << test.shiftingLetters(s4, shifts4) << std::endl;
	
	return 0;
}