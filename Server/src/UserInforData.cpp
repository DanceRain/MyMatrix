//
// Created by 14773 on 2022/4/17.
//

#include "../include/UserInforData.h"

UserInforData::UserInforData(int _infor_sender, int _infor_receiver, short _content_type, const std::string& _infor_content)
        : infor_sender(_infor_sender), infor_receiver(_infor_receiver), content_type(_content_type), infor_content(_infor_content)
{

}

int UserInforData::getInforNum() const {
    return infor_num;
}

void UserInforData::setInforNum(int inforNum) {
    infor_num = inforNum;
}

int UserInforData::getInforSender() const {
    return infor_sender;
}

void UserInforData::setInforSender(int inforSender) {
    infor_sender = inforSender;
}

int UserInforData::getInforReceiver() const {
    return infor_receiver;
}

void UserInforData::setInforReceiver(int inforReceiver) {
    infor_receiver = inforReceiver;
}

short UserInforData::getContentType() const {
    return content_type;
}

void UserInforData::setContentType(short contentType) {
    content_type = contentType;
}

const std::string &UserInforData::getInforContent() const {
    return infor_content;
}

void UserInforData::setInforContent(const std::string &inforContent) {
    infor_content = inforContent;
}


