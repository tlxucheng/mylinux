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

    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) 
	{
        std::vector<int> ret;
		int row = matrix.size();
		int col = matrix[0].size();
		int elem_cout = row * col;;
		int find_elem_cout = 0;
		int direct = 1;   /* 1: 向右，2：向左，3：向上，4：向下*/
		
		print(matrix);
		
		std::cout << elem_cout << std::endl;
		
		int i = 0;
		int j = 0;
		while(find_elem_cout < elem_cout 
		     && 0 <= i && i < row
			 && 0 <= j && j < col)
		{
			ret.push_back(matrix[i][j]);
			if(i == 0 && j == col - 1)
			{
				direct = 4;
			}
			else if(i == row - 1 && j == col - 1)
            {
				direct = 2;
			}				
			else if(i == row - 1 && j == 0)
			{
				direct = 3;
			}
			else if(i == 0 && j == 0)
			{
				direct = 1;
			}
		
			if(i == row - 1)
			{
				col--;
			}
			else if(j == col - 1)
			{
				row--;
			}
		
			switch(direct)
			{
				case 1:
				    j++;
				    break;
				case 2:
				    j--;
					break;
				case 3:
				    i--;
				    break;
				case 4:
				    i++;
				    break;
				default:
				    break;
			}
			
		}
		
		
	    return ret;	
    }
};

int main()
{
    Solution test;
	
	std::vector<std::vector<int>> matrix(3);
	std::vector<int> ret;
	
	std::vector<int> row0 = {1,2,3};
	std::vector<int> row1 = {4,5,6};
	std::vector<int> row2 = {7,8,9};
	
	matrix[0] = row0;
	matrix[1] = row1;
	matrix[2] = row2;

	ret = test.spiralOrder(matrix);
	for(int i = 0; i < ret.size(); i++)
	{
		std::cout << ret[i] << " ";
	}
	std::cout << std::endl;
	
	return 0;
}