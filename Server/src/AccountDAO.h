//
// Created by 14773 on 2022/3/5.
//

#ifndef MYMATRIX_SERVER_ACCOUNTDAO_H
#define MYMATRIX_SERVER_ACCOUNTDAO_H


#include <string>
#include "AccountData.h"

class AccountDAO{
public:
    static std::string insertIntoTable(const AccountData& userData);
    static void updateTable(const AccountData& userData);
    static AccountData selectData(const std::string& userAccount);
    static void deleteData(const std::string& userAccount);
};


#endif //MYMATRIX_SERVER_ACCOUNTDAO_H
