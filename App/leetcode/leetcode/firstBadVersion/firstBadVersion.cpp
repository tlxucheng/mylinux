#include <iostream>

const int g_bad = 1;

class Solution {
public:
    bool isBadVersion(int version)
	{
         if(version >= g_bad)
		 {
			 return true;
		 }
		 else
		 {
			 return false;
		 }
	}

    int firstBadVersion(int n) 
	{
		int left   = 0;
		int right  = n;
		int middle = right/2;
		int i      = 0;
		
		while(false == isBadVersion(middle))
		{
			left = middle;
			middle = left + (right - left)/2;
		}
		
		for(i = middle; i > 0; i--)
		{
			if(false == isBadVersion(i-1))
			{
				break;
			}
		}
		
		return i;
    }
};

int main()
{
	Solution test;
	
	std::cout << test.firstBadVersion(5) << std::endl;
	
	return 0;
}