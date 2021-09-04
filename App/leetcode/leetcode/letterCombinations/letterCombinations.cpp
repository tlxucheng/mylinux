#include <iostream>
#include <vector>
#include <string>
#include <map>

class Solution {
public:
    void createCombinations(int start, std::string digits, std::string current)
	{
		if(start == digits.length())
		{
			ans.push_back(current);
		}
		
		for(int i = 0; i < m[digits[start]].length(); i++)
		{
			char s = m[digits[start]][i];
			current += s;
			createCombinations(start+1, digits, current);
			current.pop_back();
		}
	}

    std::vector<std::string> letterCombinations(std::string digits)
	{
        if(digits.length()<=0) return ans;
        
        m.insert({'2',"abc"});
        m.insert({'3',"def"});
        m.insert({'4',"ghi"});
        m.insert({'5',"jkl"});
        m.insert({'6',"mno"});
        m.insert({'7',"pqrs"});
        m.insert({'8',"tuv"});
        m.insert({'9',"wxyz"});
		
		createCombinations(0, digits, "");
		
		return ans;
    }

private:
    std::vector<std::string> ans;
	std::map<char, std::string> m;
};

int main()
{
	Solution test;
	std::string digits = {"23"};
	std::vector<std::string> ans1;
	
	ans1 = test.letterCombinations(digits);
	for(int i = 0; i < ans1.size(); i++)
	{
		std::cout << ans1[i] << " ";
	}
	std::cout << std::endl;
	
	return 0;
}