#include <iostream>
#include <vector>


/* 1,2,4,-1,-1,-1,3,5,-1,-1,6,-1,-1
           1
		 2   3
		4   5 6
   
   先序： 124356
   中序： 421536
   后序： 425631
*/

typedef struct treeNode
{
	int val;
	struct treeNode *left;
	struct treeNode *right;
}TreeNode;

class Solution {
public:
    std::vector<int> vc;
	int ans_sumOfLeftLeaves = 0;
	
	std::vector<int> vc_averageOfLevels;
	
	std::vector<int> vc_root_to_leaves;
public:
    std::vector<int> rootToLeavesTraversal(TreeNode* root)
    {
	    if(NULL != root && NULL == root->left
		   || NULL != root && NULL == root->right)
	    {
		    vc_root_to_leaves.push_back(root->val);
			rootToLeavesTraversal(root->left);
			rootToLeavesTraversal(root->right);
	    }
		
		return vc_root_to_leaves;
	}

    int sumNumbers(TreeNode* root)
    {
		return 0;
	}
	
    bool isBalanced()
	
    int sumOfLeftLeaves(TreeNode* root) 
	{
        if(root)
		{
			if(root->left && (NULL == root->left->left && NULL == root->left->right))
			{
				ans_sumOfLeftLeaves += root->left->val;
			}
			
			sumOfLeftLeaves(root->left);
			sumOfLeftLeaves(root->right);
		}
		
		return ans_sumOfLeftLeaves;
    }

    /*
	 *      1
	 *	   / \
	 *	  2   2
	 *	 / \ / \
	 *	3  4 4  3
	 *
	 */
    bool isSymmetric(TreeNode* root) 
	{
		if(NULL == root)
		{
			return true;
		}
        
		TreeNode* left_node = root->left;
		TreeNode* right_node = root->right;
		while(NULL != left_node && NULL != right_node)
		{
			if(left_node->val != right_node->val)
			{
				return false;
			}
			else
			{
				left_node = left_node->left;
				right_node = right_node->right;
			}
		}
		
		return true;
    }
	 
    bool hasPathSum(TreeNode *root, int targetSum)
	{
		if(!root)
		{
			return 0;
		}
		if(root->left == NULL && root->right == NULL)
		{
            if(targetSum == root->val)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}

		return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
	}
	
    std::vector<int> preorderTraversal(TreeNode* root)
	{
		if(root)
		{
		    vc.push_back(root->val);
			preorderTraversal(root->left);
			preorderTraversal(root->right);
		}
		
		
		return vc;
    }


    TreeNode* CreateBinaryTree(std::vector<int> &vc, int &index)
	{
	    TreeNode *T = NULL;

		if(-1 != vc[index])
		{
			T = new TreeNode;
			T->val = vc[index];
			T->left = CreateBinaryTree(vc, ++index);
			T->right = CreateBinaryTree(vc, ++index);
		}
		
		return T;
    }

    TreeNode* CreateBinaryTree2(std::vector<int> &vc)
    {
        int  index = 0;

	    return CreateBinaryTree(vc, index);
	}

	void PreOrderTraverse(TreeNode *T)
	{
		if(T)
		{
			std::cout << T->val;
			PreOrderTraverse(T->left);
			PreOrderTraverse(T->right);
		}
				
		return;
	}
	
    void InOrderTraverse(TreeNode *T)
	{
		if(T)
		{
			InOrderTraverse(T->left);
			std::cout << T->val;
			InOrderTraverse(T->right);
		}
			
		return;
	}
	
	void PostOrderTraverse(TreeNode *T)
	{
		if(T)
		{
			PostOrderTraverse(T->left);
			PostOrderTraverse(T->right);
		    std::cout << T->val;
		}
			
		return;
	}
};

int main()
{
    TreeNode *T = NULL;

	Solution test;
	std::vector<int> vc = {1,2,4,-1,-1,-1,3,5,-1,-1,6,-1,-1};
	T = test.CreateBinaryTree2(vc);
	test.PreOrderTraverse(T);
	std::cout << std::endl;
	test.InOrderTraverse(T);
	std::cout << std::endl;
	test.PostOrderTraverse(T);
	std::cout << std::endl;

	std::vector<int> ans;
	ans = test.preorderTraversal(T);
	for(int i = 0; i < ans.size(); i++)
	{
		std::cout << ans[i];
	}
    std::cout << std::endl;
	
    std::cout << test.hasPathSum(T, 10) << std::endl;

	std::cout << test.sumOfLeftLeaves(T) << std::endl;
	
	return 0;
}












