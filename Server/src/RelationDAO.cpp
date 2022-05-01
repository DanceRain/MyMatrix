//
// Created by 14773 on 2022/4/5.
//

#include "../include/RelationDAO.h"
#include "../include/MySQLPool.h"
#include "../include/DatabaseUtility.h"

void RelationDAO::insert(const RelationData &relation_data) {
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr<PreparedStatement> pStmt(pConn->prepareStatement("INSERT INTO user_relation_table (user_account, friend_account) VALUES(?, ?)"));
            pStmt->setInt(1,  relation_data.getUserAccount());
            pStmt->setInt(2, relation_data.getFriendAccount());
            pStmt->execute();
        }
        catch (SQLException &e) {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
}

vector<int> RelationDAO::select(int userAccount) {
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    vector<int> friend_id_vec;
    if(nullptr != pConn) {
        try {
            pConn->setSchema(getMatrixDBName());
            unique_ptr<PreparedStatement> pStmt(
                    pConn->prepareStatement("SELECT user_account as friend_account FROM user_relation_table WHERE friend_account = ?\n"
                                            "UNION\n"
                                            "SELECT friend_account FROM user_relation_table WHERE user_account = ?"));
            unique_ptr<ResultSet> pRes;
            pStmt->setInt(1, userAccount);
            pStmt->setInt(2, userAccount);
            if(pStmt->execute())
            {
                pRes.reset(pStmt->getResultSet());
            }
            while (pRes->next()) {
                friend_id_vec.push_back(pRes->getInt("friend_account"));
            }
        }
        catch (SQLException &e) {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
    return friend_id_vec;
}

void RelationDAO::deleteRelation(int user_account, int frined_account)
{

}
