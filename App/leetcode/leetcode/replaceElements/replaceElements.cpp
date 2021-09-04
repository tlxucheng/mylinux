#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> replaceElements(std::vector<int>& arr) {
		std::vector<int>::iterator p;
		
		for(int i = 0; i < arr.size()-1; i++)
	    {
	        p = std::max_element(arr.begin()+i+1, arr.end());
			arr[i] = *p;
		}
		
		arr[arr.size()-1] = -1;
		
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