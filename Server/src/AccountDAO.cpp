//
// Created by 14773 on 2022/3/5.
//

#include "../include/AccountDAO.h"
#include "../include/MySQLPool.h"
#include "../include/DatabaseUtility.h"

using namespace std;

int AccountDAO::insert(const AccountData& userData)
{
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    int newId = 0;
    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr<PreparedStatement> pStmt(pConn->prepareStatement("INSERT INTO user_detail_table (user_pwd, user_name) VALUES(?, ?)"));

            pStmt->setString(1,  userData.getUserPwd());
            pStmt->setString(2, userData.getUserName());
            pStmt->execute();
            pStmt.reset(pConn->prepareStatement("SELECT LAST_INSERT_ID() as _userId FROM user_detail_table LIMIT 1,1"));
            pStmt->execute();
            unique_ptr<ResultSet> pRes(pStmt->getResultSet());
            while(pRes->next())
            {
                newId = pRes->getInt("_userId");
            }
        }
        catch (SQLException &e) {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
    return newId;
}

void AccountDAO::update(const AccountData &userData)
{
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr <PreparedStatement> pStmt(
                    pConn->prepareStatement("UPDATE ? SET user_account = ?, user_pwd = ?, user_name = ?"
                                            "user_icon_path = ?, user_gender = ?, user_area = ? WHERE user_account = ?"));
            pStmt->setString(1, getUserAccountTableName());
            pStmt->setInt(2,  userData.getUserAccount());
            pStmt->setString(3,  userData.getUserPwd());
            pStmt->setString(4,  userData.getUserName());
            pStmt->setString(5,  userData.getUserIconPath());
            pStmt->setUInt(6,  userData.getGender());
            pStmt->setString(7,  userData.getArea());
            pStmt->setInt(8,  userData.getUserAccount());

            pStmt->execute();
        }
        catch (SQLException &e) {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
}

AccountData AccountDAO::select(int userAccount) {
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    AccountData userData;
    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr <PreparedStatement> pStmt(pConn->prepareStatement("SELECT * FROM user_detail_table WHERE user_account = ?"));
            unique_ptr <ResultSet> pRes;
            pStmt->setInt(1,  userAccount);

            if(pStmt->execute())
            {
                pRes.reset(pStmt->getResultSet());
            }
            while(pRes->next())
            {
                userData.setUserAccount(pRes->getInt("user_account"));
                userData.setUserPwd(pRes->getString("user_pwd"));
                userData.setUserName(pRes->getString("user_name"));
                userData.setUserIconPath(pRes->getString("user_icon_path"));
                userData.setGender(pRes->getInt("user_gender"));
                userData.setArea(pRes->getString("user_area"));
            }
        }
        catch (SQLException &e) {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
    return userData;
}

void AccountDAO::deleteAccount(int userAccount) {
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr <PreparedStatement> pStmt(
                    pConn->prepareStatement("DELETE FROM ? WHERE user_account = ?"));
            pStmt->setString(1,  getUserAccountTableName());
            pStmt->setInt(2,  userAccount);
            pStmt->execute();
        }
        catch (SQLException &e) {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
}
