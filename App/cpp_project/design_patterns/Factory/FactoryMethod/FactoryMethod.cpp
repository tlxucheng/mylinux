#include <iostream>

using namespace std;

class databases
{
public:
    virtual void show() = 0;
};

class mysql:public databases
{
public:
    void show()
	{
	    cout << "this is mysql class" << endl;
	}
};

class oracle:public databases
{
public:
    void show()
	{
	    cout << "this is oracle class" << endl;
	}
};

class factoy
{
public:
    virtual databases* create() = 0;
};

class factory_mysql:public factoy
{
public:
    databases* create()
    {
	return new mysql;
    }
};

class factory_oracle:public factoy
{
public:
    databases* create()
    {
	return new oracle;
    }
};

int main()
{
    factory_mysql  *test_mysql_fac = new factory_mysql;
    factory_oracle *test_oracle_fac = new factory_oracle;
	
    databases *test_mysql = test_mysql_fac->create();
    databases *test_oracle = test_oracle_fac->create();
	
    test_mysql->show();
    test_oracle->show();

    delete(test_mysql_fac);	
    delete(test_oracle_fac);
    delete(test_mysql);
    delete(test_oracle);
	
    return 0;
}