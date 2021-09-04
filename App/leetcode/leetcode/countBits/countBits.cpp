/* 上面的代码中，i&(i-1)的含义为，将i的从右往左的第一个1变为0，这样可以使得i变小，以便可以从已经找到的结果中寻找结果。然后再加1给加回来即可。 */

#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> countBits(int num)
	{
        std::vector<int> ret(num+1, 0);
		
        for (int i = 1; i <= num; ++i)
		{
            ret[i] = ret[i&(i-1)] + 1;
		}
		
        return ret;
    }
};

int main()
{
	Solution          test;
	int               num = 5;
	std::vector<int>  vec;
	
	vec = test.countBits(num);
	
	for(int i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
	
	return 0;
}
