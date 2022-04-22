//
// Created by 14773 on 2022/4/6.
//

#include "RelationData.h"

int RelationData::getRelationNum() const {
    return relation_num;
}

void RelationData::setRelationNum(int relationNum) {
    relation_num = relationNum;
}

int RelationData::getUserAccount() const {
    return user_account;
}

void RelationData::setUserAccount(int userAccount) {
    user_account = userAccount;
}

int RelationData::getFriendAccount() const {
    return friend_account;
}

void RelationData::setFriendAccount(int friendAccount) {
    friend_account = friendAccount;
}
