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
    ListNode* middleNode(ListNode* head) {
        ListNode *p     = head;
        int      len    = 0;
		int      middle = 0;
		
        while(NULL != p)
		{
			len++;
			p = p->next;
		}			
	
        p = head;
		middle = len/2;
		while(middle > 0)
		{
			p = p->next;
			middle--;
		}
		
		return p;
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
	test.printLink(headA);
	test.printLink(test.middleNode(headA));
	
	ListNode *headB = new ListNode;
	headB->val = 1;
	headB->next = NULL;
	test.addLinkElem(headB, 2);
	test.addLinkElem(headB, 3);
	test.addLinkElem(headB, 4);
	test.addLinkElem(headB, 5);
	test.addLinkElem(headB, 6);
	test.printLink(headB);
	test.printLink(test.middleNode(headB));

	
	return 0;
}