#include <iostream>
#include <list>

typedef struct ListNode {
    int val;
    ListNode *next;
}ListNode;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
	    std::list<int>order;
        ListNode*temp=head;
        while(temp!=nullptr){
            order.push_back(temp->val);
            temp=temp->next;
        }
		
		std::list<int>::iterator it;		
		for(it = order.begin(); it != order.end(); it++)
		{
			std::cout << *it << " ";
		}		
		std::cout << std::endl;
		
        temp=head;
        int i=0;
        while(temp!=nullptr)
        {
            if(i%2==0)
            {
                temp->val=order.front();
                order.pop_front();
            }
            else
            {
                temp->val=order.back();
                order.pop_back();
            }
            temp=temp->next;
            i++;
        }
		
		return;
    }
	
	void addLinkElem(ListNode *head, int val)
	{
		ListNode *p = head;
		while(NULL != p->next)
		{
		   p = p->next;
		}

		ListNode *node = new ListNode;
		node->val = val;
		node->next = NULL;
		p->next = node;
	}

	void printLink(ListNode *head)
	{
		ListNode *p = head;
		while(NULL != p->next)
		{
		   std::cout << p->val << " ";
		   p = p->next;
		}
		std::cout << p->val << " " << std::endl;
	   
	}
};

int main()
{	
	Solution test;

	ListNode *headA = new ListNode;
	headA->val = 1;
	headA->next = NULL;
	test.addLinkElem(headA, 2);
	test.addLinkElem(headA, 3);
	test.addLinkElem(headA, 4);
	test.addLinkElem(headA, 5);
	test.addLinkElem(headA, 6);
	test.printLink(headA);

	test.reorderList(headA);
	test.printLink(headA);
	
	return 0;
}
