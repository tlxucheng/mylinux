#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int i = 0;
    
    priority_queue<int> a;
    priority_queue<int, vector<int>, greater<int> > c;

    for (int i = 0; i < 5; i++) 
    {
        a.push(i);
        c.push(i);
    }
    while (!a.empty()) 
    {
        cout << a.top() << ' ';
        a.pop();
    } 
    cout << endl;

    while (!c.empty()) 
    {
        cout << c.top() << ' ';
        c.pop();
    }
    cout << endl;
    
    return 0;
}

