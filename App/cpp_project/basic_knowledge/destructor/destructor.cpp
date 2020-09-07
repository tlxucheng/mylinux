#include <iostream>

using namespace std;

class databases
{
public:
    databases() {cout << "create databases" << endl;}
    virtual ~databases() {cout << "delete databases" << endl;}    
};

class mysql:public databases
{
public:
    mysql() {cout << "create mysql" << endl;}
    ~mysql() {cout << "delete mysql" << endl;}    
};

int main()
{
    databases *p = new mysql();

    delete p;
   
    // mysql q;

    return 0;
}
