#include <iostream>

const int STACK_MAX_SIZE = 100000;

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        top_pos = -1;
    }
    
    void push(int val) {
        elem[++top_pos] = val;
    }
    
    void pop() {
        top_pos--;
    }
    
    int top() {
        return elem[top_pos];
    }
    
    int getMin() {
		int min = elem[0];
        for(int i = 1 ;i <= top_pos; i++)
		{
			if(elem[i] < min)
			{
				min = elem[i];
			}
		}
		
		return min;
    }
	
private:
    int elem[STACK_MAX_SIZE];
	int top_pos;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

int main()
{
	MinStack *obj = new MinStack();

	obj->push(-2);
	obj->push(0);
	obj->push(-3);
	std::cout << obj->getMin() << std::endl; // return -3
	obj->pop();
	std::cout << obj->top() << std::endl;    // return 0
	std::cout << obj->getMin() << std::endl; // return -2	
	
	delete obj;
	
	return 0;
}