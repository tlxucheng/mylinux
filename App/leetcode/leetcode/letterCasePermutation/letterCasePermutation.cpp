#include <iostream>
#include <vector>
#include <string>

#if 0
class Solution {
public:
    std::vector<std::string> sans;
    void Util(std::string s, std::string s1, int index)
    {
        sans.push_back(s1);
        for(int i = index; i < s.length(); i++)
        {
            if(s[i]>= 97 && s[i]<=122)
            {
                s1[i]=s[i]-32;
                Util(s,s1,i+1);
                s1[i]=s[i];
            }
            else if(s[i]>=65 && s[i]<=90)
            {
                s1[i]=s[i]+32;
                Util(s,s1,i+1);
                s1[i]=s[i];
            }
        }
    }
	
    std::vector<std::string> letterCasePermutation(std::string s)
	{
        Util(s,s,0);
        return sans;
    }
};
#endif

class Solution {
public:
    std::vector<std::string> sans;

    std::vector<std::string> letterCasePermutation(std::string s) 
	{
	    Util(s, s, 0);
		return sans;
    }

	void Util(std::string &s, std::string s1, int index)
	{		
        sans.push_back(s1);
        for(int i = index; i < s.length(); i++)
		{
	        if(s[i]>= 97 && s[i]<=122)
            {
                s1[i]=s[i]-32;
                Util(s,s1,i+1);
                s1[i]=s[i];
            }	
            else if(s[i]>=65 && s[i]<=90)
            {
                s1[i]=s[i]+32;
                Util(s,s1,i+1);
                s1[i]=s[i];
            }			
		}
	}
};

#if 0
class Solution {
public:
    std::vector<std::string> letterCasePermutation(std::string s) 
	{
        std::vector<std::string> res;

	    backtrack(s, res, s, 0);

		return res;
    }

	void backtrack(std::string &s, std::vector<std::string> &res, std::string &path, int start_index)
	{		
		res.push_back(path);

		for(int i = start_index; i < s.length(); i++)
		{
			if(s[i]>=97 && s[i]<=122)
			{
				path[i] = s[i] - 32;
			    backtrack(s, res, path, i+1);
				path[i] = s[i];
			}		
            else if(s[i]>=65 && s[i]<=90)	
            {
				path[i] = s[i] + 32;
				backtrack(s, res, path, i+1);
				path[i] = s[i];
			}				
		}
	}
};
#endif

int main()
{
	Solution test;
	
    std::vector<std::string> res1;
	std::string              s1 = "a1b2";
	
	res1 = test.letterCasePermutation(s1);
	std::cout << "res1.size: " << res1.size() << std::endl;
	for(int i = 0; i < res1.size(); i++)
	{
		std::cout << res1[i] << std::endl;
	}
	std::cout << std::endl;
	
	return 0;
}
