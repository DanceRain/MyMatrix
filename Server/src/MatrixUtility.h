//
// Created by 14773 on 2022/3/5.
//

#ifndef MYMATRIX_SERVER_MATRIXUTILITY_H
#define MYMATRIX_SERVER_MATRIXUTILITY_H
#include <string>
#include "AccountDAO.h"

std::string userRegister(std::string user_name, std::string user_pwd)
{
    AccountData userInfor("",user_pwd, user_name, "", 0, "");
    return AccountDAO::insertIntoTable(userInfor);
}


#endif //MYMATRIX_SERVER_MATRIXUTILITY_H
