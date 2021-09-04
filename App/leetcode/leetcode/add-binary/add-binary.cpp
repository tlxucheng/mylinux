#include <iostream>
#include <string>

class Solution {
    public:
	    std::string addBinary(std::string a, std::string b) 
		{
		    int i = 0;
		    int j = 0;
			int k = 0;
			std::string c;

		    for(i = a.length() - 1, j < b.length() - 1; i = 0, j = 0, k = 0; i--, j--, k++)
		    {
		         if(a[i] == '1' && b[j] == '1')
				 {
				     c.insert(c.begin(), '0');
				     c.insert(c.begin(), '1');
				 }
				 else if(a[i] == '1' && b[j] == '0'
						|| a[i] == '0' && b[j] == '1')
				 {
                     if(c[k] == '1')
					 {
					     c.insert(c.begin(), '0');
						 c.insert(c.begin(), '1');
					 }
					 else 
					 {
				         c.insert(c.begin(), '1');
					 }
				 }
				 else if(a[i] == '0' && b[j] == '0')
				 {
		             c.insert(c.begin(), '0');
				 }

		    }

		}
};

int main()
{
    Solution test;

    std::string a = "11";
	std::string b = "1";

    std::cout << test.addBinary(a, b) << std::endl; 

    a = "1010";
	b = "1011";
    std::cout << test.addBinary(a, b) << std::endl;


	return 0;
}
