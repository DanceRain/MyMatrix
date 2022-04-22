/*
 * author:Wang Guixin
 * e-mail:1477364283@qq.com
 * date:2022/2/28
 */
#include <boost/json/serialize.hpp>
#include <iostream>
#include <string>
#include <boost/json.hpp>
#include <httplib.h>
#include <cstdlib>
#include <list>
#include <algorithm>
#include <UserInforDAO.h>

#include "MatrixUtility.h"


using namespace std;

list<int> online_user;
list<boost::json::value> online_infor;

int main()
{
    httplib::Server svr;

    svr.Post("/register", [](const httplib::Request& req, httplib::Response& res)
    {
        cout << req.body << endl;
        auto decode_infor = boost::json::parse(req.body);
        string user_name = decode_infor.as_object()["user_name"].as_string().data();
        string user_pwd = decode_infor.as_object()["user_pwd"].as_string().data();
        string newId = userRegister(user_name, user_pwd);
        boost::json::value response = {
                {"content_type", 1},
                { "new_id", newId}
        };
       res.set_content(boost::json::serialize(response), "text/plain");
    });

    svr.Post("/login", [](const httplib::Request& req, httplib::Response& res)
    {
        cout << req.body << endl;
        auto decode_infor = boost::json::parse(req.body.c_str());
        string user_id = decode_infor.as_object()["user_id"].as_string().data();
        string user_pwd = decode_infor.as_object()["user_pwd"].as_string().data();

        bool IsRight = userLogin(atoi(user_id.c_str()), user_pwd);
        if(IsRight)
        {
            online_user.push_back(atoi(user_id.c_str()));
        }
        boost::json::value response = {
                {"content_type", 2},
                { "is_right", IsRight}
        };
        res.set_content(boost::json::serialize(response), "application/json");
    });

    svr.Post("/request", [](const httplib::Request& req, httplib::Response& res)
    {
        cout << req.body << endl;
        auto decode_infor = boost::json::parse(req.body.c_str());
        string user_id = decode_infor.as_object()["user_id"].as_string().data();

        AccountData userInfor = getUserInfor(atoi(user_id.c_str()));
        boost::json::value response = {
                {"content_type", 3},
                {"user_account", userInfor.getUserAccount()},
                {"user_name", userInfor.getUserName()},
                {"user_icon", userInfor.getUserIconPath()},
                {"user_gender", userInfor.getGender()},
                {"user_area", userInfor.getArea()}
        };
        cout << boost::json::serialize(response) << " this is response" << endl;
        res.set_content(boost::json::serialize(response), "application/json");
    });

    svr.Post("/addFriend", [](const httplib::Request& req, httplib::Response& res)
    {
        cout << req.body << endl;
        auto decode_infor = boost::json::parse(req.body.c_str());
        string friend_id = decode_infor.as_object()["friend_id"].as_string().data();
        string user_id = decode_infor.as_object()["user_id"].as_string().data();


        AccountData userInfor = getUserInfor(atoi(friend_id.c_str()));

        //判断账户是否存在，若不存在则告知请求方；若存在则判断其是否在线；若在线，加入消息列表，等待下一次轮询发送；若不在线，存入数据库
        if(-1 == userInfor.getUserAccount())
        {
            boost::json::value response = {
                    {"content_type", 4},
                    {"is_exist", false}
            };
            cout << boost::json::serialize(response) << " this is response" << endl;
            res.set_content(boost::json::serialize(response), "application/json");
        }
        else
        {
            boost::json::value response = {
                    {"content_type", 4},
                    {"is_exist", true}
            };
            cout << boost::json::serialize(response) << " this is response" << endl;
            res.set_content(boost::json::serialize(response), "application/json");
            //请求的好友方在线，加入待发送消息队列;好友方不在线，则将请求消息存储起来。
            if(std::find(online_user.begin(), online_user.end(), userInfor.getUserAccount()) != online_user.end())
            {
                online_infor.push_back(decode_infor);
            }
            else
            {
                UserInforData data(atoi(user_id.c_str()), atoi(friend_id.c_str()), 5);
                insertMessage(data);
            }
        }
    });

    svr.Post("/getMessage", [](const httplib::Request& req, httplib::Response& res)
    {
        cout << req.body << endl;
        auto decode_infor = boost::json::parse(req.body.c_str());
        string user_id = decode_infor.as_object()["user_id"].as_string().data();

        vector<UserInforData> vec;
        getMessage(vec);
        boost::json::object response;
        for(auto it = vec.begin(); it != vec.end(); ++it)
        {
            boost::json::value message = {
                    {"content_type", it->getContentType()},
                    {"infor_sender", it->getInforSender()},
                    {"infor_receiver", it->getInforReceiver()},
                    {"infor_content", it->getInforContent()}
            };
            response["message " + to_string(it - vec.begin())] = message;
        }
        cout << "response: " << boost::json::serialize(response) << endl;
        res.set_content(boost::json::serialize(response), "application/json");
    });

    svr.listen("0.0.0.0", 9999);

    return 0;
}
