#include <iostream>
#include <queue>

class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {
        
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        q.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        while(q.size() > 1)
		{
			q1.push(q.front());
			q.pop();
		}
		
		int elem = q.front();
		q.pop();
		while(!q1.empty())
		{
		    q.push(q1.front());   
            q1.pop();			
		}
		
		return elem;
    }
    
    /** Get the top element. */
    int top() {
        while(q.size() > 1)
		{
			q1.push(q.front());
			q.pop();
		}
		
		int elem = q.front();
		q.pop();
		
		while(!q1.empty())
		{
		    q.push(q1.front());    	
			q1.pop();
		}
		q.push(elem);
		
		return elem;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return q.empty();
    }
	
private:
    std::queue<int> q;
	std::queue<int> q1;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

int main()
{	
	MyStack* obj = new MyStack();
    obj->push(1);
	obj->push(2);
	obj->push(3);
	obj->push(4);
	std::cout << obj->top() << std::endl;
	std::cout << obj->pop() << std::endl;
	std::cout << obj->empty() << std::endl;
	delete obj;
	
    obj = new MyStack();
	obj->push(1);
	obj->push(2);
	std::cout << obj->top() << std::endl;
	std::cout << obj->pop() << std::endl;
	std::cout << obj->empty() << std::endl;
	delete obj;

	return 0;
}




