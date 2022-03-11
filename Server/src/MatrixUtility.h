//
// Created by 14773 on 2022/3/5.
//

#ifndef MYMATRIX_SERVER_MATRIXUTILITY_H
#define MYMATRIX_SERVER_MATRIXUTILITY_H
#include <string>
#include <utility>
#include "AccountDAO.h"

std::string userRegister(const std::string& user_name, const std::string& user_pwd)
{
    AccountData userInfor(-1, user_pwd, user_name, "", 0, "");
    return AccountDAO::insertIntoTable(userInfor);
}

bool userLogin(int user_id, std::string& user_pwd)
{
    AccountData userInfor = AccountDAO::selectData(user_id);
    if(userInfor.getUserAccount() != -1 && userInfor.getUserPwd() == user_pwd)
    {
        return true;
    }
    return false;
}

#endif //MYMATRIX_SERVER_MATRIXUTILITY_H
