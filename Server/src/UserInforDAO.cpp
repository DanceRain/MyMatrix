//
// Created by 14773 on 2022/4/17.
//

#include "../include/UserInforDAO.h"
#include "../include/DatabaseUtility.h"
#include "../include/MySQLPool.h"

void UserInforDAO::insert(const UserInforData &userData)
{
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    pConn->rollback();
    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr<PreparedStatement> pStmt(pConn->prepareStatement("INSERT INTO user_infor_table (infor_sender, infor_receiver, content_type, infor_content) "
                                                                        "VALUES(?, ?, ?, ?)"));
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

void UserInforDAO::select(int infro_receiver, vector<UserInforData>& vecInfor)
{
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr<PreparedStatement> pStmt(
                    pConn->prepareStatement("SELECT * FROM user_infor_table WHERE infor_receiver = ?"));
            unique_ptr<ResultSet> pRes;
            pStmt->setInt(1, infro_receiver);
            if(pStmt->execute())
            {
                pRes.reset(pStmt->getResultSet());
            }
            while (pRes->next()) {
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

void UserInforDAO::deleteInfor(int _infor_num)
{
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr<PreparedStatement> pStmt(pConn->prepareStatement("DELETE FROM user_infor_table WHERE infor_num = ?"));
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





