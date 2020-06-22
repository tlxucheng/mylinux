#include <iostream>
#include <map>
using namespace std;
int main()
{
    map<int,string> data={
        {1,"a"},
        {2,"b"}
    };
    data[3]='c';
    map<int,string>::iterator it;
    data.insert(pair<int,string>(4,"d"));
    data.insert(pair<int,string>(1,"z"));
    it=data.find(1);//查找关键字1，结果为find,==a
    if(it!=data.end())
    {
        cout << "find,=="<<it->second<<endl;
    }
    else
    {
        cout << "don't find"<<endl;
    }
    cout<<data.count(2) << endl;//查找关键字2，结果为1
}


