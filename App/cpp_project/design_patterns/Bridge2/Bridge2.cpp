#include <iostream>

using namespace std;

class statement
{
public:
    virtual ~statement() {}
    virtual void execute() = 0;
    
};

class select:public statement
{
public:
    void execute()
    {
        cout << "exec select sql" << endl;
    }
};

class insert:public statement
{
public:
    void execute()
    {
        cout << "exec insert sql" << endl;
    }
};

class update:public statement
{
public:
    void execute()
    {
        cout << "exec update sql" << endl;
    }
};

class mysql
{
public:
    mysql(statement *pStatement)
    {
        this->pStatement = pStatement;
    }
    
    ~mysql()
    {
        delete pStatement;
        pStatement = NULL;
    }

    void execute()
    {
        pStatement->execute();
    }
    
private:
    statement *pStatement = NULL;
};

class oracle
{
public:
    oracle(statement *pStatement)
    {
        this->pStatement = pStatement;
    }
    
    ~oracle()
    {
        delete pStatement;
        pStatement = NULL;
    }

    void execute()
    {
        pStatement->execute();
    }
    
private:
    statement *pStatement = NULL;
};

class sqlserver
{
public:
    sqlserver(statement *pStatement)
    {
        this->pStatement = pStatement;
    }
    
    ~sqlserver()
    {
        delete pStatement;
        pStatement = NULL;
    }

    void execute()
    {
        pStatement->execute();
    }
    
private:
    statement *pStatement = NULL;
};


int main()
{
     mysql *test = NULL;

     test = new mysql(new select());
     test->execute();
     delete test;
     
     test = new mysql(new insert());
     test->execute();
     delete test;

     test = new mysql(new update());
     test->execute();
     delete test;

     oracle *test_oracle = NULL;
     
     test_oracle = new oracle(new select());
     test_oracle->execute();
     delete test_oracle;
     
     test_oracle = new oracle(new insert());
     test_oracle->execute();
     delete test_oracle;

     test_oracle = new oracle(new update());
     test_oracle->execute();
     delete test_oracle;

     sqlserver *test_sqlserver = NULL;

     test_sqlserver = new sqlserver(new select());
     test_sqlserver->execute();
     delete test_sqlserver;
     
     test_sqlserver = new sqlserver(new insert());
     test_sqlserver->execute();
     delete test_sqlserver;

     test_sqlserver = new sqlserver(new update());
     test_sqlserver->execute();
     delete test_sqlserver;

     return 0;
}


