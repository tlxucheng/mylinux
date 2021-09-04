#include <iostream>
#include <vector>

class Solution {
public:
    void print(std::vector<std::vector<int>>& matrix)
    {
		int row = matrix.size();
		int col = matrix[0].size();
		
		for(int i = 0; i < row; i++)
		{
			for(int j = 0; j < col; j++)
			{
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}	
		
		return;
	}
	
    void rotate(std::vector<std::vector<int>>& matrix)
	{
        print(matrix);
		
	    int n = matrix[0].size();
		
		for(int i = 0; i < n / 2; i++)
		{
            for(int j = 0; j < n; j++)
			{
                std::swap(matrix[i][j], matrix[n - i - 1][j]);
            }
        }
	
	    print(matrix);
	
		return;
    }
};

int main()
{
	Solution test;
	
	std::vector<std::vector<int>> matrix(3);
	
	std::vector<int> row0 = {1,2,3};
	std::vector<int> row1 = {4,5,6};
	std::vector<int> row2 = {7,8,9};
	
	matrix[0] = row0;
	matrix[1] = row1;
	matrix[2] = row2;

	test.rotate(matrix);
	
	return 0;
}