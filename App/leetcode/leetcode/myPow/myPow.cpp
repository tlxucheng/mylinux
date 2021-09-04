#include <iostream>

class Solution {
public:
    double myPow(double x, int n)
	{
        double result   = 0.00000;
		int    negative = 0;
		
		if(n < 0)
		{
			negative = 1;
			n = 0 - n;
		}
		
		if(0 == n)
		{
			return 1.00000;
		}
		else
		{
			result = x*myPow(x, n-1);
		}
		
		if(1 == negative)
	    {
			result = 1.00000/result;
		}			
	
		return result;
    }
};

int main()
{
	Solution test;
	
	std::cout << test.myPow(2.00000, 3) << std::endl;
	std::cout << test.myPow(2.00000, 10) << std::endl;
	std::cout << test.myPow(2.10000, 3) << std::endl;	
	std::cout << test.myPow(2.00000, -2) << std::endl;	

	
	return 0;
}