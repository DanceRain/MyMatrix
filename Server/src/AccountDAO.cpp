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
            pStmt->setString(2,  userData.getUserAccount());
            pStmt->setString(3,  userData.getUserPwd());
            pStmt->setString(4,  userData.getUserName());
            pStmt->setString(5,  userData.getUserIconPath());
            pStmt->setUInt(6,  userData.getGender());
            pStmt->setString(7,  userData.getArea());
            pStmt->setString(8,  userData.getUserAccount());
            pStmt->execute();
        }
        catch (SQLException &e) {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
}

AccountData AccountDAO::selectData(const string& userAccount) {
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    AccountData userData;
    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr <PreparedStatement> pStmt(
                    pConn->prepareStatement("SELECT * FROM ? WHERE user_account = ?"));
            unique_ptr <ResultSet> pRes;
            pStmt->setString(1,  getUserAccountTableName());
            pStmt->setString(2,  userAccount);
            pStmt->execute();
            pRes.reset(pStmt->getResultSet());

            {
                pRes->next();
                userData.setUserAccount(userAccount);
                pRes->next();
                userData.setUserPwd(pRes->getString("user_pwd"));
                pRes->next();
                userData.setUserName(pRes->getString("user_name"));
                pRes->next();
                userData.setUserIconPath(pRes->getString("user_icon_path"));
                pRes->next();
                userData.setGender(pRes->getInt("user_gender"));
                pRes->next();
                userData.setArea(pRes->getString("user_area"));
            }
            for(int i = 0; pRes->next() && i < getAccountTableColName().size(); ++i)
            {

            }
        }
        catch (SQLException &e) {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
    return userData;
}

void AccountDAO::deleteData(const string &userAccount) {
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr <PreparedStatement> pStmt(
                    pConn->prepareStatement("DELETE FROM ? WHERE user_account = ?"));
            pStmt->setString(1,  getUserAccountTableName());
            pStmt->setString(2,  userAccount);
            pStmt->execute();
        }
        catch (SQLException &e) {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
}
