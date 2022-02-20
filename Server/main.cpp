#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>
#include <memory>
#include "src/mysqlPool.h"

using namespace std;
using namespace sql;

int main()
{
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    if(pConn != nullptr)
    {
        cout << "Succesful! Current size is " << ConnectionPool::getConnectionPool().getCurrentSize() << endl;
        unique_ptr<Statement> pStmt(pConn->createStatement());
        pStmt->execute("use MatrixDB");
        unique_ptr<ResultSet> pRes(pStmt->executeQuery("call getUserTable()"));
        cout << "find " << pRes->rowsCount() << " data";
        while(pRes->next())
        {
            cout << "accout: " << pRes->getString("user_account");
            cout << "password: " << pRes->getString("user_pwd");
        }

    }
    return 0;
}
