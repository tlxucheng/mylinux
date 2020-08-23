#include <iostream>
#include <stack>

using namespace std;

typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;    
}BiTNode;

typedef struct BiSortTNode
{
    int data;
    struct BiSortTNode *lchild;
    struct BiSortTNode *rchild;    
}BiSortTNode;

/* input: 
 * ABDG###E##C#F## 
 * ABD#G###C#F##
 * ABDG##E##H##C#F##
 * ABCD#E###G##C#F##
 * ABCD#E###G##CF##M##
 * ABCD#E###G##CF##M#N##
 * ABCD#E###G##CF##MN###
 * ABCD#####
 * ABCD#E#####
 * ABCD###EM##N##C#F##
 * 4123#####
 */

void CreatBiTree_NoRecursion(BiTNode* &T)
{
    char              ch;
    stack<BiTNode *>  tree_elem;
    char              top_elem;
    BiTNode*          new_node    = NULL;           
    BiTNode*          temp_node   = NULL;  
    BiTNode*          top_node    = NULL;      
    bool              IsDirection = true; // true:�� false:��

    /* �������ڵ� */
    cin >> ch;
    T = new BiTNode;
    T->data = ch;
    T->lchild = NULL;
    T->rchild = NULL;
    tree_elem.push(T);

    do
    {
        cin >> ch;

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

                while(!tree_elem.empty())
                {
                    top_node = tree_elem.top();
                    if(top_node->rchild == temp_node)
                    {
                        tree_elem.pop();
                        temp_node = top_node;
                    }
                    else 
                    {
                        break;
                    }
               };
            }
        }
   
    }while(!tree_elem.empty());

    return;
}

void CreatBiSortTreeInsert(BiSortTNode* &T, int data)
{
    BiSortTNode *temp_node  = NULL;  
    BiSortTNode *find_node  = NULL;  

    /* ���ڵ� */
    if(NULL == T)
    {
        T = new BiSortTNode;
        T->data = data;
        T->lchild = NULL;
        T->rchild = NULL;
    }
    else
    {
        find_node = T;
        if(data < find_node->data)
        {
            if(NULL == find_node->lchild)
            {
                temp_node = new BiSortTNode;
                temp_node->data = data;
                find_node->lchild = temp_node;
                
            }
        }
    }

    return;
}


void CreatBiTree_NoRecursion_ByCinString(BiTNode* &T)
{
    string str;

    cin >> str;
    cout << str << endl;

    return;
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

    return;
}

/* ABDG###E##C#F## */
void preorder_NoRecursion(BiTNode *T)
{
    BiTNode           *node = NULL;
    stack<BiTNode *>  tree_elem;

    node = T;

    while(!tree_elem.empty() || NULL != node)
    {
        if(NULL != node)
        {
            cout << node->data;
            if(NULL != node->rchild)
            {
                tree_elem.push(node->rchild);
            }
            node = node->lchild;
        }
        else
        {
            if(!tree_elem.empty())
            {
                node = tree_elem.top();
                tree_elem.pop();
            }
        }
    };
    
    cout << endl;    
    
    return;
}

int main()
{
    BiTNode *root = NULL;

    //CreatBiTree(root);
    CreatBiTree_NoRecursion(root);
        
    cout << "pre order: "; 
    preorder(root);
    cout << endl;

    preorder_NoRecursion(root);

    //CreatBiTree_NoRecursion_ByCinString(root);

    delete(root);

    return 0;
}

