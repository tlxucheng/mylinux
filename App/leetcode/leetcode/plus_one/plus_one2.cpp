#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
    public:
			std::vector<int> plusOne(std::vector<int>& digits) {
            std::vector<int> b(digits.size());
            int              i = 0;
			int              j = 0;

			for(i = digits.size() - 1, j = 0; i >= 0; i--, j++)
	        {
			    if(i == 0 && digits[i] == 9 && b[digits.size() - 1] == 1)
                {
					b.resize(digits.size()+1);
				}
				    
				if(digits[i] == 9)
                {
			        b[j] = 0;
					b[j+1] = 1;
				}
				else
				{
				    if(i == digits.size() - 1)
				    {
				        b[j] = digits[i] + 1;
					}
					else 
					{
				        b[j] += digits[i];
					}
				}
			}

			//reverse(b.begin(), b.end());		
			std::vector<int> c(b.size());

			for (i = 0; i < b.size(); i++)
		    {
			    c[i] = b[b.size()-1-i];
			}

			return c;
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
