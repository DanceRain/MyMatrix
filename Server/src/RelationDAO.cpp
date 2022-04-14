//
// Created by 14773 on 2022/4/5.
//

#include "RelationDAO.h"
#include "MySQLPool.h"
#include "DatabaseUtility.h"

std::string RelationDAO::insertIntoTable(const RelationData &_relation_data)
{
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    string relationId;
    if(nullptr != pConn) {
        try {
            cout << "start prepareStatement 1" << endl;
            pConn->setSchema(getMatrixDBName());
            unique_ptr<PreparedStatement> pStmt(pConn->prepareStatement("CALL insertUserRelationTable(?, ?)"));
            unique_ptr<ResultSet> pRes;
            pStmt->setInt(1,  _relation_data.getUserAccount());
            pStmt->setInt(2, _relation_data.getFriendAccount());
            pStmt->execute();
            pRes.reset(pStmt->getResultSet());
            pRes->next();
            relationId = pRes->getString("_relationId");
        }
        catch (SQLException &e) {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
    return relationId;
}

void RelationDAO::updateTable(const RelationData &userData)
{

}

RelationData RelationDAO::selectData(int userAccount)
{
    return RelationData();
}

void RelationDAO::deleteData(int userAccount)
{

}
