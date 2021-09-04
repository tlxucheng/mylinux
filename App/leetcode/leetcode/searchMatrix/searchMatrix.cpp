#include <iostream>
#include <vector>

class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) 
	{
        int i = 0;
		int j = matrix[0].size() - 1;
		
		while(i < matrix.size() && j >= 0)
		{
			if(target == matrix[i][j])
			{
				return true;
			}
			else if(target < matrix[i][j])
			{
				j--;
			}
			else 
			{
				i++;
			}
		}
		
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
	
	Solution test;
	
	std::cout << test.searchMatrix(mat, 5) << std::endl;
	std::cout << test.searchMatrix(mat, 10) << std::endl;

	return 0;
}
