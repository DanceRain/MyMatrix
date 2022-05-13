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
#include <vector>



#include "include/MatrixUtility.h"

typedef websocketpp::server<websocketpp::config::asio> server;

using namespace std;

map<int, websocketpp::connection_hdl> online_user;
mutex main_mutex;

void print_message(const boost::json::value& decode_infor)
{
    cout << "the message is " << decode_infor << endl;
}

void on_message(server* s, const websocketpp::connection_hdl& hdl, const server::message_ptr& msg)
{
    lock_guard<mutex> ws_guard(main_mutex);
    auto decode_infor = boost::json::parse(msg->get_payload());
    print_message(decode_infor);
    switch(decode_infor.as_object()["content_type"].as_int64())
    {
        case 4:
        {
            string infor_sender = decode_infor.as_object()["infor_sender"].as_string().data();
            string infor_receiver = decode_infor.as_object()["infor_receiver"].as_string().data();

            AccountData receiverAccount = getUserInfor(atoi(infor_receiver.c_str()));
            AccountData senderAccount = getUserInfor(atoi(infor_sender.c_str()));

            //判断账户是否存在，若不存在则告知请求方；若存在则判断其是否在线；
            // 若在线，加入消息列表，等待下一次轮询发送；若不在线，存入数据库
            if(-1 == receiverAccount.getUserAccount())
            {
                boost::json::value response = {
                        {"content_type", 5},
                        {"is_exist", false}
                };
                cout << "this is response " << boost::json::serialize(response) << endl;
                s->send(hdl, boost::json::serialize(response), msg->get_opcode());
            }
            else
            {
                //向请求好友方发送确认报文。
                boost::json::object response_request = {
                        {"content_type", 5},
                        {"is_exist", true}
                };
                cout << "this is response " << boost::json::serialize(response_request) << endl;
                s->send(hdl, boost::json::serialize(response_request), msg->get_opcode());

                //请求的好友方在线，附加上请求方信息，直接转发给好友;好友方不在线，则将请求消息存储起来。
                boost::json::object request = {
                        {"content_type", 4},
                        {"infor_sender", senderAccount.getUserAccount()},
                        {"infor_receiver", receiverAccount.getUserAccount()}
                };
                boost::json::value sender_infor = {
                        {"user_account", senderAccount.getUserAccount()},
                        {"user_name", senderAccount.getUserName()},
                        {"user_icon", senderAccount.getUserIconPath()},
                        {"user_gender", senderAccount.getGender()},
                        {"user_area", senderAccount.getArea()}
                };
                request["friend"] = sender_infor;
                if(online_user.end() != online_user.find(receiverAccount.getUserAccount()))
                {
                    s->send(online_user[receiverAccount.getUserAccount()], boost::json::serialize(request), msg->get_opcode());
                }
                else
                {
                    UserInforData data(atoi(infor_sender.c_str()), atoi(infor_receiver.c_str()), 4);
                    insertMessage(data);
                }
            }
            break;
        }

        case 6:
        {
            string infor_sender = decode_infor.as_object()["infor_sender"].as_string().data();
            string infor_receiver = decode_infor.as_object()["infor_receiver"].as_string().data();
            AccountData friendInfor = getUserInfor(atoi(infor_sender.c_str()));

            boost::json::object response = {
                    {"content_type", 6},
                    {"infor_sender", infor_sender},
                    {"infor_receiver", infor_receiver},
            };
            boost::json::value val = {
                    {"content_type", 3},
                    {"user_account", friendInfor.getUserAccount()},
                    {"user_name", friendInfor.getUserName()},
                    {"user_icon", friendInfor.getUserIconPath()},
                    {"user_gender", friendInfor.getGender()},
                    {"user_area", friendInfor.getArea()}
            };
            response["friend"] = val;

            if(online_user.find(atoi(infor_receiver.c_str())) != online_user.end())
            {
                s->send(online_user[atoi(infor_receiver.c_str())], boost::json::serialize(response), msg->get_opcode());
            }
            else
            {
                UserInforData data(atoi(infor_sender.c_str()), atoi(infor_receiver.c_str()), 6);
                insertMessage(data);
            }
            insertRelation(RelationData(atoi(infor_sender.c_str()), atoi(infor_receiver.c_str())));
            break;
        }

        case 7:
        {
            string infor_sender = decode_infor.as_object()["infor_sender"].as_string().data();
            string infor_receiver = decode_infor.as_object()["infor_receiver"].as_string().data();

            if(online_user.find(atoi(infor_receiver.c_str())) != online_user.end())
            {
                cout << "the infor_receiver is online" << endl;
                s->send(online_user[atoi(infor_receiver.c_str())], msg->get_payload(), msg->get_opcode());
            }
            else
            {
                UserInforData data(atoi(infor_sender.c_str()), atoi(infor_receiver.c_str()), 7);
                insertMessage(data);
            }
            break;
        }

        case 8:
        {
            string infor_sender = decode_infor.as_object()["infor_sender"].as_string().data();
            string infor_receiver = decode_infor.as_object()["infor_receiver"].as_string().data();
            string infor_content = decode_infor.as_object()["infor_content"].as_string().data();
            cout << "this is infor_receiver" << infor_receiver << endl;
            if(online_user.find(atoi(infor_receiver.c_str())) != online_user.end())
            {
                cout << "the infor_receiver is online" << endl;
                s->send(online_user[atoi(infor_receiver.c_str())], msg->get_payload(), msg->get_opcode());
            }
            else
            {
                UserInforData data(atoi(infor_sender.c_str()), atoi(infor_receiver.c_str()), 8, infor_content);
                insertMessage(data);
            }
            break;
        }

        case 9:
        {
            string user_id = decode_infor.as_object()["user_id"].as_string().data();
            if(online_user.find(atoi(user_id.c_str())) == online_user.end())
            {
                online_user[atoi(user_id.c_str())] = hdl;
            }
            vector<UserInforData> userInfor;
            getMessage(atoi(user_id.c_str()), userInfor);
            for(auto it = userInfor.begin(); it != userInfor.end(); ++it)
            {
                boost::json::value response = {
                        {"content_type", it->getContentType()},
                        {"infor_sender", std::to_string(it->getInforSender())},
                        {"infor_receiver", std::to_string(it->getInforReceiver())},
                        {"infor_content", it->getInforContent()}
                };
                cout << "this is response " << boost::json::serialize(response) << endl;
                s->send(hdl, boost::json::serialize(response), msg->get_opcode());
            }
            break;
        }

        case 10:
        {
            string infor_sender = decode_infor.as_object()["infor_sender"].as_string().data();
            boost::json::value response = {
                    {"content_type", 10},
            };
            s->send(hdl, boost::json::serialize(response), msg->get_opcode());
            if(online_user.find(atoi(infor_sender.c_str())) != online_user.end())
            {
                cout << "user sign out" << endl;
                online_user.erase(atoi(infor_sender.c_str()));
            }
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
        string newId = std::to_string(userRegister(user_name, user_pwd));
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

    //initial user and his(her) friends' detail.
    httpSvr.Post("/userInitialize", [](const httplib::Request& req, httplib::Response& res)
    {
        lock_guard<mutex> ws_guard(main_mutex);
        cout << req.body << endl;
        auto decode_infor = boost::json::parse(req.body.c_str());
        string user_id = decode_infor.as_object()["user_id"].as_string().data();

        AccountData userInfor = getUserInfor(atoi(user_id.c_str()));
        vector<int> friendIdVec = getRelation(userInfor.getUserAccount());

        boost::json::object response;
        boost::json::value val = {
                {"content_type", 3},
                {"user_account", userInfor.getUserAccount()},
                {"user_name", userInfor.getUserName()},
                {"user_icon", userInfor.getUserIconPath()},
                {"user_gender", userInfor.getGender()},
                {"user_area", userInfor.getArea()}
        };
        response["user_detail"] = val;

        int num = 0;
        for(auto frinedId : friendIdVec)
        {
            ++num;
            AccountData friendInfor = getUserInfor(frinedId);
            boost::json::value val = {
                    {"content_type", 3},
                    {"user_account", friendInfor.getUserAccount()},
                    {"user_name", friendInfor.getUserName()},
                    {"user_icon", friendInfor.getUserIconPath()},
                    {"user_gender", friendInfor.getGender()},
                    {"user_area", friendInfor.getArea()}
            };
            response["friend " + to_string(num)] = val;
        }
        cout << "this is response " << boost::json::serialize(response) << endl;
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
    thread listen_http(httpListener);
    thread listen_ws(wsListener);

    listen_ws.join();
    listen_http.join();

    return 0;
}
