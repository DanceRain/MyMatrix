//
// Created by 14773 on 2022/4/21.
//
#include "MatrixUtility.h"
#include "AccountDAO.h"
#include "UserInforDAO.h"


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

AccountData getUserInfor(int user_id)
{
    AccountData userInfor = AccountDAO::selectData(user_id);
    return userInfor;
}

//message表的操作
void insertMessage(const UserInforData& _data)
{
    UserInforDAO::insertIntoTable(_data);
}

void getMessage(std::vector<UserInforData> &vecMessage)
{

}


