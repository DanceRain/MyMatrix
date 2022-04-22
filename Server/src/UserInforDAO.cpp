//
// Created by 14773 on 2022/4/17.
//

#include "UserInforDAO.h"
#include "DatabaseUtility.h"
#include "MySQLPool.h"

void UserInforDAO::insertIntoTable(const UserInforData &userData)
{
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr<PreparedStatement> pStmt(pConn->prepareStatement("CALL insertUserInforTable(?, ?, ?, ?)"));
            unique_ptr<ResultSet> pRes;
            pStmt->setInt(1, userData.getInforSender());
            pStmt->setInt(2, userData.getInforReceiver());
            pStmt->setInt(3, userData.getContentType());
            pStmt->setString(4, userData.getInforContent());
            pStmt->execute();
        }
        catch (SQLException &e) {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
}

void UserInforDAO::selectData(int infro_receiver, vector<UserInforData>& vecInfor)
{
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();

    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr<PreparedStatement> pStmt(pConn->prepareStatement("CALL selectUserInforTable(?)"));
            unique_ptr<ResultSet> pRes;
            pStmt->setInt(1, infro_receiver);
            pStmt->execute();
            pRes.reset(pStmt->getResultSet());
            while(pRes->next())
            {
                UserInforData userInforData = UserInforData(0, 0, 0);
                userInforData.setInforNum(pRes->getInt("infor_num"));
                userInforData.setInforSender(pRes->getInt("infor_sender"));
                userInforData.setInforReceiver(pRes->getInt("infor_receiver"));
                userInforData.setContentType(pRes->getInt("content_type"));
                userInforData.setInforContent(pRes->getString("infor_content"));
                vecInfor.push_back(userInforData);
            }
        }
        catch (SQLException &e) {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
}

void UserInforDAO::deleteData(int _infor_num)
{
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr<PreparedStatement> pStmt(pConn->prepareStatement("CALL deleteUserInforTable(?)"));
            unique_ptr<ResultSet> pRes;
            pStmt->setInt(1, _infor_num);
            pStmt->execute();
        }
        catch (SQLException &e) {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
}

void UserInforDAO::updateTable(const UserInforData &userData)
{

}




