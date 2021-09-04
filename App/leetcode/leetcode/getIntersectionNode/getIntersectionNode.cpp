#include <iostream>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
typedef struct ListNode {
    int val;
    ListNode *next;
}ListNode;
 
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
	{
	    if(NULL == headA || NULL == headB)
		{
			return NULL;
		}		

        ListNode *p      = headA;
		ListNode *q      = headB;	
		int      lenA    = 0;
		int      lenB    = 0;
		int      lendiff = 0;
		
        while(NULL != p)
		{
			lenA++;
			p = p->next;
		}
		
		while(NULL != q)
		{
			lenB++;
			q = q->next;
		}
		
		p = headA;
		q = headB;	
		
		if(lenA > lenB)
		{
			lendiff = lenA - lenB; 
			while(lendiff > 0)
			{
				p = p->next;
				lendiff--;
			}
		}
		else 
		{
			lendiff = lenB - lenA; 
			while(lendiff > 0)
			{
			    q = q->next;
				lendiff--;
			}
		}
		
		
		while(p && q)
		{
		   if(p == q)	
		   {
			   return p;
		   }
		   else 
		   {
			   p = p->next;
			   q = q->next;
		   }
		}
		
		return NULL;
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
	headA->val = 4;
	headA->next = NULL;
	test.addLinkElem(headA, 1);
	test.addLinkElem(headA, 8);
	test.addLinkElem(headA, 4);
	test.addLinkElem(headA, 5);
	test.printLink(headA);
	
	ListNode *headB = new ListNode;
	headB->val = 5;
	headB->next = NULL;
	test.addLinkElem(headB, 6);	
	test.addLinkElem(headB, 1);
	test.addLinkElem(headB, 8);
	test.addLinkElem(headB, 4);
	test.addLinkElem(headB, 5);
	test.printLink(headB);
	
	ListNode *result = NULL;
	result = test.getIntersectionNode(headA, headB);
	if(NULL != result)
	{
		std::cout << result->val << std::endl;
	}
	else 
	{
		std::cout << "no getIntersectionNode" << std::endl;
	}
	
	return 0;
}