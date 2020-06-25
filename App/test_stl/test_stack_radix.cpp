#include <iostream>
#include <stack>

using namespace std;

int main()
{
    stack<int>         result_stack;
    int                input_num      = 0;
    int                radix          = 0;
    
    cout << "input number and radix(number >= 0, radix 2~16)";
    cin >> input_num >> radix;

    if(input_num < 0 || radix < 2 || radix > 16)
    {
        cout << "input error!" << endl;
    }

    do
    {
        result_stack.push(input_num%radix);
        input_num = input_num/radix;
    }while(input_num > 0);

    while(!result_stack.empty())
    {   
        if(result_stack.top() > 9)
        {
            cout << (char)(result_stack.top() - 10 + 'A');
        }
        else
        {
            cout << result_stack.top();
        }
        
        result_stack.pop();
    };
 
    cout << endl;
    
    return 0;
}


