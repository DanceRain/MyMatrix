//
// Created by 14773 on 2022/3/5.
//

#ifndef MYMATRIX_SERVER_MATRIXUTILITY_H
#define MYMATRIX_SERVER_MATRIXUTILITY_H
#include <string>
#include <vector>
#include "AccountData.h"
#include "UserInforData.h"
#include "RelationData.h"


//account表的操作
int userRegister(const std::string& user_name, const std::string& user_pwd);

bool userLogin(int user_id, std::string& user_pwd);

AccountData getUserInfor(int user_id);

//message表的操作
void insertMessage(const UserInforData& _data);

void getMessage(int _receive_id, std::vector<UserInforData>& vecMessage);

//relation表的操作
void insertRelation(const RelationData& _data);

std::vector<int> getRelation(int _user_id);

#endif //MYMATRIX_SERVER_MATRIXUTILITY_H
