/* https://blog.csdn.net/qq_24452475/article/details/107070496 有图参考 */

#include <iostream>
#include <vector>

class Solution {
public:
    int findLength(std::vector<int>& nums1, std::vector<int>& nums2)
	{
		int size_A = nums1.size();
		int size_B = nums2.size();
        int ans = 0;
		int dp[6][6] = {0};
		
		for(int i = 1; i <= size_A; i++)
		{
			for(int j = 1; j <= size_B; j++)
			{
				if(nums1[i-1] == nums2[j-1])
				{
					dp[i][j] = dp[i-1][j-1] + 1;
					ans = std::max(ans, dp[i][j]);
				}
			}
		}

		return ans;
    }
};

int main()
{
	Solution test;
	
	std::vector<int> A1 = {1,2,3,2,1};
	std::vector<int> A2 = {3,2,1,4,7};
    std::cout << test.findLength(A1, A2) << std::endl;
	
	std::vector<int> A3 = {1,2,3,1};
	std::vector<int> A4 = {3,2,1,4,7};
    std::cout << test.findLength(A3, A4) << std::endl;
	
	return 0;
}