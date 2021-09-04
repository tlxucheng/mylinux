#include <iostream>

class Solution {
public:
    bool isPowerOfTwo(int n)
	{
		int ret = 0;
		
        if(n <= 0)
        {
			return false;
		}			
					
        while(n > 1)
        {
			ret = n%2;
			if(0 != ret)
			{
				break;
			}
			else
			{
				n = n/2;
			}
		}			
		
		if(0 == ret)
	    {
		    return true;
		}
		else
		{
			return false;
		}
    }
};

int main()
{
	Solution test;
	
	std::cout << test.isPowerOfTwo(1) << std::endl;	
	std::cout << test.isPowerOfTwo(16) << std::endl;
	std::cout << test.isPowerOfTwo(3) << std::endl;
	std::cout << test.isPowerOfTwo(4) << std::endl;

	return 0;
}