#include <iostream>
#include <stack>

using namespace std;

typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;    
}BiTNode;

/* input: ABDG###E##C#F## */

void CreatBiTree_NoRecursion(BiTNode* &T)
{
    char              ch;
    stack<BiTNode *>  tree_elem;
    char              top_elem;
    BiTNode*          new_node    = NULL;           
    BiTNode*          temp_node   = NULL;  
    bool              IsDirection = true; // true:左 false:右
    bool              Isroot      = true;

    do
    {
        cin >> ch;

        if('!' == ch)
        {
            break;
        }

        if(Isroot)
        {
            /* 创建根节点 */
            T = new BiTNode;
            T->data = ch;
            T->lchild = NULL;
            T->rchild = NULL;
            tree_elem.push(T);
            Isroot = false;
        }
        else
        {
            if('#' != ch)
            {
                new_node = new BiTNode;
                new_node->data = ch;
                temp_node = tree_elem.top();
                if(true == IsDirection)
                {
                    temp_node->lchild = new_node;
                }
                else 
                {
                    temp_node->rchild = new_node;
                    IsDirection = true;
                }
                tree_elem.push(new_node);
            }
            else if('#' == ch)
            {
                temp_node = tree_elem.top();
                if(true == IsDirection)
                {
                    temp_node->lchild = NULL;
                    IsDirection = false;
                }
                else 
                {
                    temp_node->rchild = NULL;
                    tree_elem.pop();
                    
                    temp_node = tree_elem.top();
                    while(NULL != temp_node->lchild && NULL != temp_node->rchild)
                    {
                        if(!tree_elem.empty())
                        {
                            tree_elem.pop();
                            temp_node = tree_elem.top();
                        }
                    }
                }
            }
        }
   
    }while(!tree_elem.empty());

    return;
}

void CreatBiTree_NoRecursion_ByCinString(BiTNode* &T)
{
}

void CreatBiTree(BiTNode* &T)
{
    char ch;

    cin >> ch;
    if('#' == ch)
    {
        T = NULL;
        return;
    }
    T = new BiTNode;
    if(!T)
    {
        cout << "no space" << endl;
    }
    else
    {
        T->data = ch;
        T->lchild = NULL;
        T->rchild = NULL;
        CreatBiTree(T->lchild);
        CreatBiTree(T->rchild);
    }

    return;
}

void preorder(BiTNode *T)
{
    if(!T)
    {   
        return ;
    }
    cout << T->data;
    preorder(T->lchild);
    preorder(T->rchild);
}

int main()
{
    BiTNode *root = NULL;

    //CreatBiTree(root);
    CreatBiTree_NoRecursion(root);
        
    cout << "pre order: "; 
    preorder(root);
    cout << endl;

    return 0;
}

