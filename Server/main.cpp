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
#include <websocketpp/common/connection_hdl.hpp>
#include <websocketpp/connection_base.hpp>
#include <websocketpp/error.hpp>
#include <websocketpp/logger/levels.hpp>
#include <websocketpp/roles/server_endpoint.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <thread>
#include <mutex>


#include <openssl/conf.h>

#include "include/UserInforDAO.h"
#include "include/MatrixUtility.h"

#define SERVER_CERT_FILE "~/MyGitProject/MyMatrix/Server/ssl/certificate.pem"
#define SERVER_PRIVATE_KEY_FILE "~/MyGitProject/MyMatrix/Server/ssl/privateKey.pem"

typedef websocketpp::server<websocketpp::config::asio> server;

using namespace std;

map<int, websocketpp::connection_hdl> online_user;
list<boost::json::value> online_infor;
mutex main_mutex;

void on_message(server* s, websocketpp::connection_hdl hdl, server::message_ptr msg)
{
    lock_guard<mutex> ws_guard(main_mutex);
    auto decode_infor = boost::json::parse(msg->get_payload());
    switch(decode_infor.as_object()["content_type"].as_int64())
    {
        case 4:
        {
            cout << decode_infor << endl;
            string friend_id = decode_infor.as_object()["friend_id"].as_string().data();
            string user_id = decode_infor.as_object()["user_id"].as_string().data();

            AccountData userInfor = getUserInfor(atoi(friend_id.c_str()));

            //判断账户是否存在，若不存在则告知请求方；若存在则判断其是否在线；若在线，加入消息列表，等待下一次轮询发送；若不在线，存入数据库
            if(-1 == userInfor.getUserAccount())
            {
                boost::json::value response = {
                        {"content_type", 5},
                        {"is_exist", false}
                };
                cout << boost::json::serialize(response) << " this is response" << endl;
                s->send(hdl, boost::json::serialize(response), msg->get_opcode());
            }
            else
            {
                boost::json::value response = {
                        {"content_type", 5},
                        {"is_exist", true}
                };
                cout << boost::json::serialize(response) << " this is response" << endl;
                s->send(hdl, boost::json::serialize(response), msg->get_opcode());
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
        }

        case 6:
        {
            break;
        }
        default:
        {
            cerr << "content_type error" << endl;
        }
    }
}

void httpListener()
{
    httplib::Server httpSvr;

    //user register
    httpSvr.Post("/register", [](const httplib::Request& req, httplib::Response& res)
    {
        lock_guard<mutex> ws_guard(main_mutex);
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

    //user login
    httpSvr.Post("/login", [](const httplib::Request& req, httplib::Response& res)
    {
        lock_guard<mutex> ws_guard(main_mutex);
        cout << req.body << endl;
        auto decode_infor = boost::json::parse(req.body.c_str());
        string user_id = decode_infor.as_object()["user_id"].as_string().data();
        string user_pwd = decode_infor.as_object()["user_pwd"].as_string().data();

        bool IsRight = userLogin(atoi(user_id.c_str()), user_pwd);
        boost::json::value response = {
                {"content_type", 2},
                { "is_right", IsRight}
        };
        res.set_content(boost::json::serialize(response), "application/json");
    });

    //user request self data
    httpSvr.Post("/request", [](const httplib::Request& req, httplib::Response& res)
    {
        lock_guard<mutex> ws_guard(main_mutex);
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

    httpSvr.listen("0.0.0.0", 9999);
}

void wsListener()
{
    try
    {
        server matrix_server;
        matrix_server.set_reuse_addr(true);
        matrix_server.set_message_handler(websocketpp::lib::bind(&on_message, &matrix_server, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
        matrix_server.set_access_channels(websocketpp::log::alevel::all);
        matrix_server.set_error_channels(websocketpp::log::elevel::all);

        matrix_server.init_asio();
        matrix_server.listen(10000);
        matrix_server.start_accept();
        matrix_server.run();
    }catch(const websocketpp::exception& e)
    {
        cerr << e.what() << endl;
    }
}
int main()
{
    /*
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
    httplib::SSLServer httpSvr(SERVER_CERT_FILE, SERVER_PRIVATE_KEY_FILE);
#else
    httplib::Server httpSvr;
#endif

    if(!httpSvr.is_valid())
    {
        cout << "the httpSvr is invalid" << endl;
        return -1;
    }
    httpSvr.Post("/register", [](const httplib::Request& req, httplib::Response& res)
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

    httpSvr.Post("/login", [](const httplib::Request& req, httplib::Response& res)
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

    httpSvr.Post("/request", [](const httplib::Request& req, httplib::Response& res)
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

    httpSvr.Post("/addFriend", [](const httplib::Request& req, httplib::Response& res)
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

    httpSvr.Post("/getMessage", [](const httplib::Request& req, httplib::Response& res)
    {
        cout << req.body << endl;
        auto decode_infor = boost::json::parse(req.body.c_str());
        string user_id = decode_infor.as_object()["user_id"].as_string().data();

        vector<UserInforData> vec;
        getMessage(atoi(user_id.c_str()), vec);
        if(vec.size() == 1)
        {

        }
        boost::json::object response;
        for(auto it = vec.begin(); it != vec.end(); ++it)
        {
            boost::json::value message = {
                    {"content_type", it->getContentType()},
                    {"infor_sender", it->getInforSender()},
                    {"infor_receiver", it->getInforReceiver()},
                    {"infor_content", it->getInforContent()}
            };
            response[to_string(it - vec.begin())] = message;
        }
        cout << "response: " << boost::json::serialize(response) << endl;
        res.set_content(boost::json::serialize(response), "application/json");
    });

    httpSvr.set_error_handler([](const httplib::Request & req, httplib::Response &res) {
        const char *fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
        char buf[BUFSIZ];
        snprintf(buf, sizeof(buf), fmt, res.status);
        res.set_content(buf, "text/html");
    });

    httpSvr.listen("0.0.0.0", 9999);

    return 0;*/

    thread listen_http(httpListener);
    thread listen_ws(wsListener);

    listen_ws.join();
    listen_http.join();

    return 0;
}
