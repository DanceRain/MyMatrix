//
// Created by 14773 on 2022/4/17.
//

#ifndef MYMATRIX_SERVER_USERINFORDAO_H
#define MYMATRIX_SERVER_USERINFORDAO_H

#include <string>
#include <vector>
#include "UserInforData.h"

class UserInforDAO {
public:
    static void insertIntoTable(const UserInforData& userData);
    static void updateTable(const UserInforData& userData);
    static void selectData(int infro_receiver, std::vector<UserInforData>& vecInfor);
    static void deleteData(int userAccount);
};


#endif //MYMATRIX_SERVER_USERINFORDAO_H
