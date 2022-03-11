//
// Created by 14773 on 2022/3/5.
//

#include "AccountDAO.h"
#include "MySQLPool.h"
#include <vector>

using namespace std;

const string& getUserAccountTableName()
{
    static string talbeName = "user_detail_table";
    return talbeName;
}

const string& getMatrixDBName()
{
    static string matrixDBName = "MatrixDB";
    return matrixDBName;
}

const vector<string>& getAccountTableColName()
{
    static vector<string> colNames = {"user_account", "user_pwd", "user_name", "user_icon_path", "user_gender",
                                      "user_area"};
    return colNames;
}

string AccountDAO::insertIntoTable(const AccountData& userData)
{
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    string newId;
    if(nullptr != pConn) {
        try {
            cout << "start prepareStatement 1" << endl;
            pConn->setSchema(getMatrixDBName());
            unique_ptr<PreparedStatement> pStmt(pConn->prepareStatement("CALL insertUserDetail(?, ?)"));
            unique_ptr<ResultSet> pRes;
            pStmt->setString(1,  userData.getUserPwd());
            pStmt->setString(2, userData.getUserName());
            pStmt->execute();
            pRes.reset(pStmt->getResultSet());
            pRes->next();
            newId = pRes->getString("_userId");
        }
        catch (SQLException &e) {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
    return newId;
}

void AccountDAO::updateTable(const AccountData &userData)
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

AccountData AccountDAO::selectData(int userAccount) {
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    AccountData userData;
    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr <PreparedStatement> pStmt(
                    pConn->prepareStatement("CALL selectUserDetail(?)"));
            unique_ptr <ResultSet> pRes;
            pStmt->setInt(1,  userAccount);
            pStmt->executeUpdate();
            pRes.reset(pStmt->getResultSet());
            if(pRes->next())
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

void AccountDAO::deleteData(int userAccount) {
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
