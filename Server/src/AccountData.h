//
// Created by 14773 on 2022/3/5.
//

#ifndef MYMATRIX_SERVER_ACCOUNTDATA_H
#define MYMATRIX_SERVER_ACCOUNTDATA_H

#include <string>
class AccountData {
public:
    explicit AccountData(std::string userAccount = "", std::string userPwd = "", std::string userName = "",
                std::string userIconPath = "", unsigned int gender = 0, std::string area = "");

    const std::string &getUserAccount() const;
    void setUserAccount(const std::string &userAccount);

    const std::string &getUserPwd() const;
    void setUserPwd(const std::string &userPwd);

    const std::string &getUserName() const;
    void setUserName(const std::string &userName);

    const std::string &getUserIconPath() const;
    void setUserIconPath(const std::string &userIconPath);

    unsigned int getGender() const;
    void setGender(unsigned int gender);

    const std::string &getArea() const;
    void setArea(const std::string &area);

private:
    std::string user_account;
    std::string user_pwd;
    std::string user_name;
    std::string user_icon_path;
    unsigned gender;
    std::string area;
};


#endif //MYMATRIX_SERVER_ACCOUNTDATA_H
