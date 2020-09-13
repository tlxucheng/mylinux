#include <iostream>

using namespace std;

class Databases
{
public:
    virtual void connect() = 0;
};

class MysqlDb:public Databases
{
public:
    void connect() override
    {
        cout << "MysqlDb Class connect" << endl;
    }
};

class OracleDb:public Databases
{
public:
    void connect() override
    {
        cout << "OracleDb Class connect" << endl;
    }
};

template<typename T>
class callmodel
{
public:
    void getdata()
    {
        m_db.connect();
    }

private:
    T m_db;
};

int main()
{
    callmodel<MysqlDb> *test_mysqldb = new callmodel<MysqlDb>;

    test_mysqldb->getdata();
    delete test_mysqldb;
    test_mysqldb = nullptr;

    callmodel<OracleDb> *test_oracle_db = new callmodel<OracleDb>;

    test_oracle_db->getdata();
    delete test_oracle_db;
    test_oracle_db = nullptr; 
    
    return 0;
}


