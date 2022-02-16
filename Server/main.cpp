#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include "mysql_driver.h"
#include <mysql_driver.h>
#include <exception>
#include <iostream>
#include <string>
#include <utility>


using namespace::std;
using namespace::sql;

struct Account{
    string user_account;
    string user_pwd;
};

const string dbName("MatrixDB");
const string server("localhost");
const string user("neo");
const string pwd("123456");

int main()
{
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *set;

    driver = get_driver_instance();
    con = driver->connect("127.0.0.1", user, pwd);
    con->setSchema(dbName);
    stmt = con->createStatement();
    
    set = stmt->executeQuery("select * from account_table");

    while(set->next())
    {
        cout << set->getString("user_account") << " " << set->getString("user_pwd") << endl;
    }
    return 0;
}
