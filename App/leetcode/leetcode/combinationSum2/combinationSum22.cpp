#include <iostream>
#include <vector>

class Solution {
    void sum(int ind,std::vector<std::vector<int>> &ans,std::vector<int> &ds, std::vector<int> &arr,int target){
      
        if(target == 0){
                ans.push_back(ds);
                 return;
        }
        for(int i=ind;i<arr.size();i++){
         
        if(i>ind and arr[i]==arr[i-1]) continue;
           if(arr[i]>target) break;
            ds.push_back(arr[i]);
            sum(i+1,ans,ds,arr,target-arr[i]);
            ds.pop_back();
        
       }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());
        vector<vector<int>> ans;
        vector<int> ds;
        
        sum(0,ans,ds,candidates,target);
        return ans;
    }
};


int main()
{
	Solution test;
	
	std::vector<int>   vec1     = {2,5,2,1,2};
	int                target1  = 5;
 	int                i        = 0;
	int                j        = 0;
	
	std::vector<std::vector<int>> res1 = test.combinationSum2(vec1, target1);
	
	for(i = 0; i < res1.size(); i++)
	{
		for(j = 0; j < res1[i].size(); j++)
		{
			std::cout << res1[i][j] << ",";
		}
		std::cout << std::endl;
	}
	
	std::vector<int>   vec2     = {10,1,2,7,6,1,5};
	int                target2  = 8;
 	
	std::vector<std::vector<int>> res2 = test.combinationSum2(vec2, target2);
	
	for(i = 0; i < res2.size(); i++)
	{
		for(j = 0; j < res2[i].size(); j++)
		{
			std::cout << res2[i][j] << ",";
		}
		std::cout << std::endl;
	}
	
	return 0;
}