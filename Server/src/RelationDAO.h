//
// Created by 14773 on 2022/4/5.
//

#ifndef MYMATRIX_SERVER_RELATIONDAO_H
#define MYMATRIX_SERVER_RELATIONDAO_H

#include "RelationData.h"
#include <string>

class RelationDAO {
    static std::string insertIntoTable(const RelationData& userData);
    static void updateTable(const RelationData& userData);
    static RelationData selectData(int userAccount);
    static void deleteData(int userAccount);
};


#endif //MYMATRIX_SERVER_RELATIONDAO_H
