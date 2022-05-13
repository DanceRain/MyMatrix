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
    static void insert(const UserInforData& userData);
    static void select(int infro_receiver, std::vector<UserInforData>& vecInfor);
    static void deleteInfor(int userAccount);
};


#endif //MYMATRIX_SERVER_USERINFORDAO_H
