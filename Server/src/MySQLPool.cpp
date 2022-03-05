#include "MySQLPool.h"
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <exception>
#include <memory>
#include <pthread.h>
#include <iostream>
#include <utility>

const string defaultHost = "localhost";
const string defaultUser = "neo";
const string defaultPass = "123456";
const unsigned maxsize = 20;
pthread_mutex_t poolLock;


unique_ptr<ConnectionPool> ConnectionPool::onlyInstance;

ConnectionPool::ConnectionPool(std::string  host,
        std::string  userName,
        std::string  pwd, unsigned maxSize):
    m_host(std::move(host)), m_userName(std::move(userName)), m_pwd(std::move(pwd)), MAXSIZE(maxSize)
{
    try
    {
        m_pDriver = get_driver_instance();
    }
    catch(SQLException& e)
    {
        cerr << e.what() << endl;
    }
    this->InitConnectionPool(maxSize / 2);
}

ConnectionPool& ConnectionPool::getConnectionPool()
{
    if(onlyInstance == nullptr)
    {
        pthread_mutex_lock(&poolLock);
        onlyInstance.reset(new ConnectionPool(defaultHost, defaultUser, defaultPass, maxsize));
        pthread_mutex_unlock(&poolLock);
    }
    return *(onlyInstance);
}

void ConnectionPool::InitConnectionPool(unsigned ConnectionSize)
{
    Connection* pConn;
    pthread_mutex_lock(&lock);
    for(int i = 0; i < ConnectionSize; ++i)
    {
        pConn = this->CreateOneConnection();
        if(pConn)
        {
            m_connList.push_back(pConn);
            ++CURRENTSIZE;
        }
        else
        {
            cerr << "can't create database connection" << endl;
        }
    }
    pthread_mutex_unlock(&lock);
}

Connection* ConnectionPool::CreateOneConnection()
{
    Connection* pConn;
    try{
        pConn = m_pDriver->connect(m_host, m_userName, m_pwd);
        return pConn;
    }catch(SQLException& e)
    {
        cerr << e.what() << endl;
        return nullptr;
    }
}

Connection* ConnectionPool::getConnectionFromPool()
{
    Connection* pConn;
    pthread_mutex_lock(&lock);
    if(!m_connList.empty())
    {
        pConn = m_connList.front();
        m_connList.pop_front();
        if(pConn->isClosed())
        {
            delete pConn;
            pConn = this->CreateOneConnection();
        }
        if(nullptr == pConn)
        {
            //新连接创建错误，当前连接池剩余连接 -1
            --CURRENTSIZE;
        }
        pthread_mutex_unlock(&lock);
        return pConn;
    }
    else
    {
        if(CURRENTSIZE < MAXSIZE)
        {
            pConn = this->CreateOneConnection();
            if(pConn)
            {
                ++CURRENTSIZE;
                pthread_mutex_unlock(&lock);
                return pConn;
            }
            else
            {
                pthread_mutex_unlock(&lock);
                return nullptr;
            }
        }
        else
        {
            pthread_mutex_unlock(&lock);
            return nullptr;
        }
    }
}

void ConnectionPool::releaseConnection(Connection* pConn)
{
    if(pConn)
    {
        pthread_mutex_lock(&lock);
        m_connList.push_back(pConn);
        pthread_mutex_unlock(&lock);
    }    
}

void ConnectionPool::TerminateConnectionPool()
{
    list<Connection*>::iterator it;
    pthread_mutex_lock(&lock);
    for(it = m_connList.begin(); it != m_connList.end(); ++it)
    {
        TerminateConnectionFromPool(*it);
    }
    CURRENTSIZE = 0;
    m_connList.clear();
    pthread_mutex_unlock(&lock);
}

void ConnectionPool::TerminateConnectionFromPool(Connection* pConn)
{
    if(pConn)
    {
        try{
            pConn->close();
        }catch(SQLException& e)
        {
            cerr << e.what() << endl;
        }
    }
    delete pConn;
}

unsigned ConnectionPool::getCurrentSize()
{
    return CURRENTSIZE;
}

ConnectionPool::~ConnectionPool()
{
    TerminateConnectionPool();
}
