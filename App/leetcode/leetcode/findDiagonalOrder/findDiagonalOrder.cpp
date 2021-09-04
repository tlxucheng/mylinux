#include <iostream>
#include <vector>

class Solution 
{
public:
    std::vector<int> findDiagonalOrder(std::vector<std::vector<int>>& mat) {
        int i = 0;
		int j = mt.size() - 1;
		
	    return false;
    }
};

int main()
{
	std::vector<std::vector<int>> mat = {{1,2,3},{4,5,6},{7,8,9}};
		
	for(int i = 0; i < mat.size(); i++)
	{
		for(int j = 0; j < mat[i].size(); j++)
		{
			std::cout << mat[i][j] << " ";
		}
		
		std::cout << std::endl;
	}
	
	return 0;
}