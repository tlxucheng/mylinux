#include <iostream>
#include <string>
#include <stack>

class Solution {
public:
    std::string reverseWords(std::string s) 
	{
		std::string result;
		std::string word;
		std::stack<std::string> st;
		int index = 0;
		
		while(index < s.size())
		{
		    if(s[index] == ' ')
			{
				index++;
				continue;
			}
			
			while(index < s.size() && s[index] != ' ')
			{
				word.push_back(s[index]);
				index++;
			}
		    st.push(word);
			word = "";
		}
		
		result = st.top();
		st.pop();
		while(!st.empty())
		{
			result += " " + st.top();
			st.pop();
		}			
	
		return result;
    }
};

int main()
{
	Solution test;
	
	std::string str1 = {"the sky is blue"};
	std::cout << test.reverseWords(str1) << std::endl;
	
	std::string str2 = {"  hello world  "};
	std::cout << test.reverseWords(str2) << std::endl;
	
    std::string str3 = {"a good   example"};
	std::cout << test.reverseWords(str3) << std::endl;
	
    std::string str4 = {"  Bob    Loves  Alice   "};
	std::cout << test.reverseWords(str4) << std::endl;

    std::string str5 = {"Alice does not even like bob"};
	std::cout << test.reverseWords(str5) << std::endl;
	
	return 0;
}