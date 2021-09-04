#include <iostream>

class Solution {
public:
    int calc_sum_bit(int num)
	{
		int sum = 0;
		
		while(num > 0)
		{
		    sum += num % 10;
			num /= 10;
		}
		
		return sum;
	}

    int addDigits(int num) 
	{
        while(0 != num / 10)
		{
			num = calc_sum_bit(num);
		}
		
		return num;
    }
};

int main()
{
	Solution test;
	
	std::cout << test.addDigits(38) << std::endl;
	std::cout << test.addDigits(0) << std::endl;
	
	return 0;
}