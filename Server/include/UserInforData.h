//
// Created by 14773 on 2022/4/17.
//

#ifndef MYMATRIX_SERVER_USERINFORDATA_H
#define MYMATRIX_SERVER_USERINFORDATA_H

#include <string>
class UserInforData {
public:
    UserInforData(int _infor_sender, int _infor_receiver, short _content_type, const std::string& _infor_content = "");

    int getInforNum() const;

    void setInforNum(int inforNum);

    int getInforSender() const;

    void setInforSender(int inforSender);

    int getInforReceiver() const;

    void setInforReceiver(int inforReceiver);

    short getContentType() const;

    void setContentType(short contentType);

    const std::string &getInforContent() const;

    void setInforContent(const std::string &inforContent);

private:
    int infor_num{};
    int infor_sender{};
    int infor_receiver{};
    short content_type{};
    std::string infor_content;
};


#endif //MYMATRIX_SERVER_USERINFORDATA_H
