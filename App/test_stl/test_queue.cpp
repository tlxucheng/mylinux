#include <iostream>
#include <queue>
#include <deque>

using namespace std;

int main()
{
    queue<int> my_queue;
    int        i        = 0;
    int        elem     = 0;

    cout << "test queue front" << endl;
    for(i = 0; i < 5; i++)
    {
        my_queue.push(i+1);
    }

    while(!my_queue.empty())
    {
        elem = my_queue.front();
        cout << elem << "\t";
        my_queue.pop();
    }
    cout << endl;

    cout << "test queue back" << endl;
    for(i = 0; i < 5; i++)
    {
        my_queue.push(i+1);
    }
  
    elem = my_queue.back();
    cout << elem << "\t";
    my_queue.pop();

    elem = my_queue.back();
    cout << elem << endl;

    deque<int> my_deque;

    cout << "test deque front" << endl;
    for(i = 0; i < 5; i++)
    {
        my_deque.push_front(i+1);
    }

    for(int i = 0;i < my_deque.size();i++)
    {
        cout<<my_deque.at(i)<<"\t";
    }
    cout << endl;

    while(!my_deque.empty())
    {
        elem = my_deque.front();
        cout << elem << "\t";
        my_deque.pop_front();
    }
    cout << endl;
   
    cout << "test deque back" << endl;
    for(i = 0; i < 5; i++)
    {
        my_deque.push_back(i+1);
    }
   
    for(int i = 0;i < my_deque.size();i++)
    {
        cout<<my_deque.at(i)<<"\t";
    }
    cout << endl;
       
    while(!my_deque.empty())
    {
        elem = my_deque.front();
        cout << elem << "\t";
        my_deque.pop_front();
    }
    cout << endl;
  
    return 0;
}

