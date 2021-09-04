#include <iostream>

const int g_bad = 4; /* false false false true true */

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
	    unsigned int  lo = 1, hi = n, mid;
		
		while(hi >= lo) {
			mid = (hi +lo)/2;
			if (isBadVersion(mid)) hi = mid - 1;
			else lo = mid + 1;
		}
		mid = (hi + lo + 1)/2;
		
		return(mid);
    }
};

int main()
{
	Solution test;
	
	std::cout << test.firstBadVersion(5) << std::endl;
	
	return 0;
}