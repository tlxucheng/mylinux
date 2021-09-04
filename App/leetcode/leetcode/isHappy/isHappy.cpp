#include <iostream>

class Solution {
public:
    int calc_sum(int n)
	{
		int sum = 0;
		
		while(n > 0)
		{
			int temp = n % 10;
			sum += temp * temp;
			n = n / 10;
		}
		
		return sum;
		
	}

    bool isHappy(int n) 
	{
        int a = n;
		int b = n;
		
		if(0 == n)
		{
			return false;
		}
		
		do
		{
			//std::cout << "a: " << a << ",b: " << b << std::endl;
			a = calc_sum(a);
			b = calc_sum(b);
			b = calc_sum(b);
		}while(a != b);
		
        if(a == 1)
        {
			return true;
		}			
		
		return false;
    }
};

int main()
{
	Solution test;
	
	std::cout << test.isHappy(19) << std::endl;
	std::cout << test.isHappy(2) << std::endl;
	std::cout << test.isHappy(12) << std::endl;

	return 0;
}