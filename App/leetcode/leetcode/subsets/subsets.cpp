/* https://blog.csdn.net/yuanliang861/article/details/89087875 */

#include <iostream>
#include <vector>

class Solution
{
public:
    void fun(const std::vector<int> &nums, int index, std::vector<int> &temp, std::vector<std::vector<int>> &res)
	{
		res.push_back(temp);
		while(index < nums.size())
		{
			temp.push_back(nums[index]);
			fun(nums, index+1, temp, res);
			temp.pop_back();
			++index;
		}
		
		return;
	}

	std::vector<std::vector<int>> subsets(std::vector<int>& nums)
	{
		std::vector<std::vector<int>> res;
		std::vector<int> temp;
		fun(nums, 0, temp, res);

		return res;
	}
};

int main()
{
    Solution test;

    std::vector<int> vc = {1, 2, 3};
    //std::vector<int> vc = {1, 2};

	std::vector<std::vector<int>> res;

	res = test.subsets(vc);

	std::vector<std::vector<int>>::iterator it;
	std::vector<int> array;
	std::vector<int>::iterator it_array;

    for(it = res.begin(); it!= res.end(); it++)
	{
		array = *it;
		for(it_array = array.begin(); it_array != array.end(); it_array++)
		{
			std::cout << *it_array << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
