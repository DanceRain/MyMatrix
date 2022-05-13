//
// Created by 14773 on 2022/4/5.
//

#ifndef MYMATRIX_SERVER_RELATIONDAO_H
#define MYMATRIX_SERVER_RELATIONDAO_H

#include "RelationData.h"
#include <string>
#include <vector>

class RelationDAO {
public:
    static void insert(const RelationData& relation_data);
    static std::vector<int> select(int userAccount);
    static void deleteRelation(int user_account, int frined_account);
};


#endif //MYMATRIX_SERVER_RELATIONDAO_H
