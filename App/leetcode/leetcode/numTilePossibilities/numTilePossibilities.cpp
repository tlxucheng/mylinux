#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    int numTilePossibilities(std::string tiles)
	{
        std::vector<int> count(26, 0);
		
		for(int i = 0; i < tiles.size(); i++)
		{
			count[tiles[i]-'A']++;
		}
		
		int res = 0;
		backtrack(count, res);
		return res;
    }
	
	void backtrack(std::vector<int>& count, int& res)
	{
		for(int i = 0; i < 26; i++)
		{
			if(0 == count[i])
			{
				continue;
			}
			
			res++;
			count[i]--;
			backtrack(count, res);
			count[i]++;
		}
		
		return;
	}
};

int main()
{
	Solution test;
	std::string tiles = "AAB";
	
	std::cout << test.numTilePossibilities(tiles) << std::endl;
	
	return 0;
}