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
     ListNode* reverse(ListNode *slow)
	 {// reversing the half liked list ie [3 , 4]
        ListNode* prev=NULL,*next;
        if(slow==NULL || slow->next==NULL){
            return slow;
        }
        while(slow!=NULL){ 
            next=slow->next;
            slow->next=prev;
            prev=slow;
            slow=next;
        }
        return prev;
    }
	
    bool isPalindrome(ListNode* head) 
	{
      if(head->next==NULL){
          return true;
      }   
        ListNode* slow=head,*fast=head;
		// helps to reach mid of the linked list slow at last of loop denote the node which is mid of the liked list
        while(fast!=NULL && fast->next!=NULL){
            slow=slow->next;
            fast=fast->next->next;
        }
        ListNode* rev=reverse(slow); //here slow denote 3 from 3 we reverse the liked list and make it [4,3]
        ListNode* curr=head;
        while(rev!=NULL){// than compare half reverse liked list with full until we reach null of liked list
            if(rev->val!=curr->val){
                return false;
            }
            curr=curr->next;
            rev=rev->next;
        }
        return true;
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
	test.addLinkElem(headA, 2);
	test.addLinkElem(headA, 1);
	test.printLink(headA);
	std::cout << test.isPalindrome(headA) << std::endl;
	
	ListNode *headB = new ListNode;
	headB->val = 1;
	headB->next = NULL;
	test.addLinkElem(headB, 2);	
	test.printLink(headB);
	std::cout << test.isPalindrome(headB) << std::endl;

	ListNode *headC = new ListNode;
	headC->val = 1;
	headC->next = NULL;
	test.addLinkElem(headC, 1);
	test.addLinkElem(headC, 2);
	test.addLinkElem(headC, 1);
	test.printLink(headC);
	std::cout << test.isPalindrome(headC) << std::endl;
	
	return 0;
}