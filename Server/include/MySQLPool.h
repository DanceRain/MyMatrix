#ifndef _MYSQLPOOL_H_
#define _MYSQLPOOL_H_

#include <memory>
#include <string>
#include <list>
#include <pthread.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;
using namespace sql;

class ConnectionPool
{
public:
    ConnectionPool(ConnectionPool&&) = delete;
    ConnectionPool(const ConnectionPool&) = delete;
    ConnectionPool& operator=(const ConnectionPool&) = delete;
    ConnectionPool& operator=(const ConnectionPool&&) = delete;
    ~ConnectionPool();
private:
    ConnectionPool(string  host, string  userName, string  pwd, unsigned maxSize);
    void InitConnectionPool(unsigned connectionSize);
    void TerminateConnectionPool();
    static void TerminateConnectionFromPool(Connection* p);
    Connection* CreateOneConnection();
    
public:
    static ConnectionPool& getConnectionPool();
    Connection* getConnectionFromPool();
    void releaseConnection(Connection* pConn);
    unsigned getCurrentSize();

private:
    const unsigned MAXSIZE = 0;
    unsigned CURRENTSIZE = 0;

private:
    string m_userName;
    string m_pwd;
    string m_host;
    list<Connection*> m_connList;
    Driver *m_pDriver;
private:
    friend class unique_ptr<ConnectionPool>;
    static unique_ptr<ConnectionPool> onlyInstance;
private:
    pthread_mutex_t lock{};
};


#endif
