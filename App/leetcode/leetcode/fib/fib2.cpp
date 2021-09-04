#include <iostream>
#include <vector>

class Solution {
public:
    int fib(int n) 
	{
        if(0 == n)
		{
			return 0;
		}
		else if(1 == n)
		{
			return 1;
		}
		else
		{
			std::vector<int> vc(n+1);
            int              i    =  0;
			
			vc[0] = 0;
			vc[1] = 1;
			
			for(int i = 2; i <= n; i++)
			{
		        vc[i] = vc[i-1] + vc[i-2];
			}
			
			return vc[n];
		}
			
    }
};

int main()
{
	Solution test;
	
    std::cout << test.fib(0) << std::endl;
	std::cout << test.fib(1) << std::endl;
	std::cout << test.fib(2) << std::endl;
	std::cout << test.fib(40) << std::endl;
	
	return 0;
}