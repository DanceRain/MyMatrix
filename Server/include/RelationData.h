//
// Created by 14773 on 2022/4/6.
//

#ifndef MYMATRIX_SERVER_RELATIONDATA_H
#define MYMATRIX_SERVER_RELATIONDATA_H

class RelationData {

public:
    int getRelationNum() const;
    void setRelationNum(int relationNum);

    int getUserAccount() const;
    void setUserAccount(int userAccount);

    int getFriendAccount() const;
    void setFriendAccount(int friendAccount);

private:
    int relation_num;
    int user_account;
    int friend_account;
};


#endif //MYMATRIX_SERVER_RELATIONDATA_H
