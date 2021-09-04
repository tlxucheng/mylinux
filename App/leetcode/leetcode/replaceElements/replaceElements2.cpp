#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> replaceElements(std::vector<int>& arr) {
	    int n=arr.size(); int mx=-1;

		for(int i=n-1;i>=0;i--)
		{
			int temp=arr[i];
			arr[i]=mx;
			mx=std::max(temp,mx);
		}
		return arr;
	}
};

int main()
{
	Solution test;
	
    std::vector<int> vc = {17,18,5,4,6,1};
	for(auto val : vc)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	
	test.replaceElements(vc);
	
	for(auto val : vc)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;

	
    std::vector<int> vc2 = {400};
	for(auto val : vc2)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	
	test.replaceElements(vc2);
	
	for(auto val : vc2)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	
    return 0;	
}