#include "mysqlPool.h"
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <exception>
#include <memory>
#include <pthread.h>
#include <iostream>

const string g_sdefaultHost = "localhost";
const string g_sdefaultUser = "neo";
const string g_sdefaultPass = "123456";
const int g_imaxSize = 20;
//pthread_mutex_t poolLock;

unique_ptr<ConnectionPool> ConnectionPool::onlyInstance;
ConnectionPool::ConnectionPool(const std::string& host, 
        const std::string& userName, 
        const std::string& pwd, int maxSize):
    m_host(host), m_userName(userName), m_pwd(pwd), _MAXSIZE_(maxSize)
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
    if(onlyInstance.get() == 0)
    {
  //      pthread_mutex_lock(&poolLock);
        onlyInstance.reset(new ConnectionPool(g_sdefaultHost, g_sdefaultUser, g_sdefaultPass, g_imaxSize));
    //    pthread_mutex_unlock(&poolLock);
    }
    return *(onlyInstance.get());
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
            ++(_CURRENTSIZE_);
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
    if(m_connList.size() > 0)
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
            --_CURRENTSIZE_;
        }
        pthread_mutex_unlock(&lock);
        return pConn;
    }
    else
    {
        if(_CURRENTSIZE_ < _MAXSIZE_)
        {
            pConn = this->CreateOneConnection();
            if(pConn)
            {
                ++_CURRENTSIZE_;
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
        this->TerminateConnectionFromPool(*it);
    }
    _CURRENTSIZE_ = 0;
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
    return _CURRENTSIZE_;
}

ConnectionPool::~ConnectionPool()
{
    TerminateConnectionPool();
}
