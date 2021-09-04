#include <iostream>

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
	ListNode* removeNthFromEnd(ListNode* head, int n)
	{
		ListNode *p     = head;
	    int      length = 0;
		
	 	if(NULL == head)
		{
			return NULL;
		}			
	
		while(NULL != p)
        {
            length++;			
			p = p->next;
		}			
	
	    p = head;
		if(length - n == 0)
		{
		    return head->next;
		}
		else
		{
	        for(int i = 0; i < length - n - 1; i++)
			{
				p = p->next;
			}
			
			if(p->next->next != NULL)
			{
			    p->next = p->next->next;
			}
			else
			{
				p->next = NULL;
			}
		}
		
        return head;
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
		while(NULL != p && NULL != p->next)
		{
		   std::cout << p->val << " ";
		   p = p->next;
		}
		
		if(NULL != p)
		{
		    std::cout << p->val << " " << std::endl;
		}
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
	test.printLink(headA);
	headA = test.removeNthFromEnd(headA, 2);
	test.printLink(headA);
	std::cout << std::endl;
	
	ListNode *headB = new ListNode;
	headB->val = 1;
	headB->next = NULL;
	test.printLink(headB);
	headB = test.removeNthFromEnd(headB,1);
	test.printLink(headB);
	std::cout << std::endl;
	 
	ListNode *headC = new ListNode;
	headC->val = 1;
	headC->next = NULL;
	test.addLinkElem(headC, 2);
	test.printLink(headC);
	headC = test.removeNthFromEnd(headC,1);
	test.printLink(headC);	

	ListNode *headD = new ListNode;
	headD->val = 1;
	headD->next = NULL;
	test.addLinkElem(headD, 2);
	test.printLink(headD);
	headD = test.removeNthFromEnd(headD,2);
	test.printLink(headD);	
	
	return 0;
}
