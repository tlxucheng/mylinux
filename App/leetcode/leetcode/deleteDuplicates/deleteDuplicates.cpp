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
	ListNode* deleteDuplicates(ListNode* head)
	{
		ListNode *p = head;
		
		while(NULL != p && NULL != p->next)
		{
			if(p->next->val == p->val)
			{
				p->next = p->next->next;
			}
			else
			{
			    p=p->next;
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

	ListNode *headD = new ListNode;
	headD->val = 1;
	headD->next = NULL;
	test.addLinkElem(headD, 1);
	test.addLinkElem(headD, 1);
	test.printLink(headD);
	headD = test.deleteDuplicates(headD);
	test.printLink(headD);
	std::cout << std::endl;
	
	ListNode *headA = new ListNode;
	headA->val = 1;
	headA->next = NULL;
	test.addLinkElem(headA, 1);
	test.addLinkElem(headA, 2);
	test.printLink(headA);
	headA = test.deleteDuplicates(headA);
	test.printLink(headA);
	std::cout << std::endl;
	
	ListNode *headB = new ListNode;
	headB->val = 1;
	headB->next = NULL;
	test.addLinkElem(headB, 1);
	test.addLinkElem(headB, 2);
	test.addLinkElem(headB, 3);
	test.addLinkElem(headB, 3);
	test.printLink(headB);
	headB = test.deleteDuplicates(headB);
	test.printLink(headB);
	std::cout << std::endl;
	
	ListNode *headC = new ListNode;
	headC->val = 1;
	headC->next = NULL;
	test.addLinkElem(headC, 2);
	test.addLinkElem(headC, 2);
	test.printLink(headC);
	headC = test.deleteDuplicates(headC);
	test.printLink(headC);	
	std::cout << std::endl;
	
	return 0;
}
