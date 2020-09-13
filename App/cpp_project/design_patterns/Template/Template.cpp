#include <iostream>

using namespace std;

class Databases
{
public:
    void GetData()
    {
        Connect();
        Select();
    }

protected:
    virtual void Connect() = 0;    
    virtual void Select() = 0;
};

class MysqlDb:public Databases
{
protected:
    void Connect() override
    {
        cout << "MysqlDb Class Connect" << endl;
    }

    void Select() override
    {
        cout << "MysqlDb Class Select" << endl;
    }   
};

class OracleDb:public Databases
{
protected:
    void Connect() override
    {
        cout << "OracleDb Class Connect" << endl;
    }

    void Select() override
    {
        cout << "OracleDb Class Select" << endl;
    }   
};

int main()
{
    MysqlDb *test_mysql_db = new MysqlDb();

    test_mysql_db->GetData();
    delete test_mysql_db;
    test_mysql_db = nullptr;
    
    OracleDb *test_oracle_db = new OracleDb();

    test_oracle_db->GetData();
    delete test_oracle_db;
    test_oracle_db = nullptr;

    return 0;
}

