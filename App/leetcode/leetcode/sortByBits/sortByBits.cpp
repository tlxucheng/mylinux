#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    static std::string inttoBits(int n)
	{
		std::string bits;
		
		while(n != 0)
		{
			bits.insert(bits.begin(), n % 2 + '0');
			n = n / 2;
		}
				
		return bits;
	}
	
    static int bitnums(int num)
    {
        int numOfOnes = 0;         
        while (num > 0) {
            if(num % 2 == 1) numOfOnes++;            
            num = num / 2;
        }
        
        return numOfOnes;
    }
    
	
	static bool cmp(const int &x, const int &y)
	{
		#if 0
		if(bitnums(x) > bitnums(y))
		{
			return x;
		}
		else if(bitnums(x) == bitnums(y))
		{
			if(x >= y)
			{
				return x;
			}
			else
			{
				return y;
			}
		}
		else 
		{
			return y;
		}
		#endif
		
		int xc = bitnums(x), yc = bitnums(y);
        return xc == yc ? x < y : xc < yc;
	}

    std::vector<int> sortByBits(std::vector<int>& arr) {
		
		std::sort(arr.begin(), arr.end(), cmp);
		
		return arr;
    }
};

#if 0
class Solution {
public:
    static bool cmp(const int& x, const int& y) {
        int xc = __builtin_popcount(x), yc = __builtin_popcount(y);
        return xc == yc ? x < y : xc < yc;
    }
    std::vector<int> sortByBits(std::vector<int>& v) {
        restd::sort(v.begin(), v.end(), cmp);
        return v;
    }
};
#endif

int main()
{
	Solution test;
	
	/*
	std::cout << test.inttoBits(1) << std::endl;
	std::cout << test.inttoBits(2) << std::endl;
	std::cout << test.inttoBits(7) << std::endl;
	std::cout << test.inttoBits(8) << std::endl;
    std::cout << test.inttoBits(16) << std::endl;

	std::cout << test.bitnums(1) << std::endl;
	std::cout << test.bitnums(2) << std::endl;
	std::cout << test.bitnums(7) << std::endl;
	std::cout << test.bitnums(8) << std::endl;
    std::cout << test.bitnums(16) << std::endl;
	*/
	
	std::vector<int> arr1 = {0,1,2,3,4,5,6,7,8};
	for(auto val : arr1)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	
	test.sortByBits(arr1);
	for(auto val : arr1)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	
	return 0;
}