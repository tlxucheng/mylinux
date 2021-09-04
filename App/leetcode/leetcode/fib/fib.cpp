#include <iostream>

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
			return fib(n - 1) + fib(n - 2);
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