#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Solution {
    public:
			std::vector<int> plusOne(std::vector<int>& digits) {
		    std::string   str;
            int      i = 0;
            std::vector<int> b;
			std::stringstream ss;

			for(i = 0; i < digits.size(); i++)
			{
                ss << digits[i];

                str.insert(str.size(), ss.str());

				ss.clear();
				ss.str("");
			}

			std::istringstream is(str);
			int num = 0;
			is >> num;
			num += 1;

            ss << num;
            str = ss.str();

			for(i = 0; i < str.size(); i++)
	        {
                b.push_back(str[i]-'0');
			}

			return b;
		}
};

int main()
{
    Solution test;
    int      i  =  0;

	std::vector<int> digits = {1,2,3};
	std::vector<int> digits2 = {4,3,2,1};
    std::vector<int> digits3 = {0};
    std::vector<int> digits4 = {9,9,9};

	std::vector<int> b1 = test.plusOne(digits);
    for(i = 0; i < b1.size(); i++)
	{
		std::cout << b1[i]  ;
	}
	std::cout << std::endl;

	std::vector<int> b2 = test.plusOne(digits2);
    for(i = 0; i < b2.size(); i++)
    {
        std::cout << b2[i]  ;
	}
	std::cout << std::endl;

	std::vector<int> b3 = test.plusOne(digits3);
    for(i = 0; i < b3.size(); i++)
    {
		std::cout << b3[i]  ;
	}
	std::cout << std::endl;

	std::vector<int> b4 = test.plusOne(digits4);
    for(i = 0; i < b4.size(); i++)
    {
		std::cout << b4[i]  ;
	}
	std::cout << std::endl;

	return 0;
}
