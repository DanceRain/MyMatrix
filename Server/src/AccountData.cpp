//
// Created by 14773 on 2022/3/5.
//

#include "AccountData.h"
#include <utility>

int AccountData::getUserAccount() const {
    return user_account;
}

void AccountData::setUserAccount(int userAccount) {
    user_account = userAccount;
}

const std::string &AccountData::getUserPwd() const {
    return user_pwd;
}

void AccountData::setUserPwd(const std::string &userPwd) {
    user_pwd = userPwd;
}

const std::string &AccountData::getUserName() const {
    return user_name;
}

void AccountData::setUserName(const std::string &userName) {
    user_name = userName;
}

const std::string &AccountData::getUserIconPath() const {
    return user_icon_path;
}

void AccountData::setUserIconPath(const std::string &userIconPath) {
    user_icon_path = userIconPath;
}

unsigned int AccountData::getGender() const {
    return gender;
}

void AccountData::setGender(unsigned int gender) {
    AccountData::gender = gender;
}

const std::string &AccountData::getArea() const {
    return area;
}

void AccountData::setArea(const std::string &area) {
    AccountData::area = area;
}

AccountData::AccountData(int userAccount,std::string userPwd,std::string userName,
                         std::string userIconPath,unsigned int gender,std::string area) :
                         user_account(userAccount),
                         user_pwd(std::move(userPwd)),
                         user_name(std::move(userName)),
                         user_icon_path(std::move(userIconPath)),
                         gender(gender),
                         area(std::move(area)) {

}

