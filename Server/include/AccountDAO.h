//
// Created by 14773 on 2022/3/5.
//

#ifndef MYMATRIX_SERVER_ACCOUNTDAO_H
#define MYMATRIX_SERVER_ACCOUNTDAO_H


#include <string>
#include "AccountData.h"

class AccountDAO{
public:
    static std::string insert(const AccountData& userData);
    static void update(const AccountData& userData);
    static AccountData select(int userAccount);
    static void deleteAccount(int userAccount);
};


#endif //MYMATRIX_SERVER_ACCOUNTDAO_H
