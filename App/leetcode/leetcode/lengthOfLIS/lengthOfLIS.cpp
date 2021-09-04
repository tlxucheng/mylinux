/* https://my.oschina.net/u/4279434/blog/4173865 */

#include <iostream>
#include <vector>

class Solution
{
public:
    int lengthOfLIS(std::vector<int>& nums)
	{
		int n      = nums.size();
	    int maxres = 1;

		std::vector<int> res(n, 1);
		for(int i = 1; i < n; i++)
		{
			for(int j = 0; j < i; j++)
			{
				if(nums[i] > nums[j])
				{
					res[i] = std::max(res[i], res[j]+1);
				}
			}
			maxres = std::max(maxres, res[i]);
		}
		
		return maxres;
	}
};

int main()
{
	Solution test;
	
	std::vector<int> nums1 = {10,9,2,5,3,7,101,18};
	std::cout << test.lengthOfLIS(nums1) << std::endl; /* [2,3,7,101] */
	
	std::vector<int> nums2 = {10,9,2,5,3,1,101,18};   /* [2,5,101]*/
	std::cout << test.lengthOfLIS(nums2) << std::endl;

	return 0;
}
