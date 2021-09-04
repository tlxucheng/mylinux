#include <iostream>

class Solution {
public:
    int trailingZeroes(int n)
	{
		if(n < 5)
        {
			return 0;
		}
		
		int ans = 0;
		while(n > 0)
		{
			n = n/5;
		    ans += n;
		}
		
		return ans;
    }
};

int main()
{
	Solution test;
	
	std::cout << test.trailingZeroes(10) << std::endl;
	std::cout << test.trailingZeroes(3) << std::endl;
    std::cout << test.trailingZeroes(5) << std::endl;
    std::cout << test.trailingZeroes(0) << std::endl;
    std::cout << test.trailingZeroes(12) << std::endl;

	return 0;
}