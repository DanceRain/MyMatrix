//
// Created by 14773 on 2022/4/14.
//
#include <DatabaseUtility.h>
const std::string& getUserAccountTableName()
{
    static std::string talbeName = "user_detail_table";
    return talbeName;
}

const std::string& getMatrixDBName()
{
    static std::string matrixDBName = "MatrixDB";
    return matrixDBName;
}

const std::vector<std::string>& getAccountTableColName()
{
    static std::vector<std::string> colNames = {"user_account", "user_pwd", "user_name", "user_icon_path", "user_gender",
                                                "user_area"};
    return colNames;
}

