//
// Created by 14773 on 2022/4/6.
//

#ifndef MYMATRIX_SERVER_DATABASEUTILITY_H
#define MYMATRIX_SERVER_DATABASEUTILITY_H
#include <string>
#include <vector>

const std::string& getUserAccountTableName();
const std::string& getMatrixDBName();
const std::vector<std::string>& getAccountTableColName();

#endif //MYMATRIX_SERVER_DATABASEUTILITY_H
