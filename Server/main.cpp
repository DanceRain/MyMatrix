/*
 * author:Wang Guixin
 * e-mail:1477364283@qq.com
 * date:2022/2/28
 */
#include <boost/json/serialize.hpp>
#include <boost/property_tree/ptree_fwd.hpp>
#include <iostream>
#include <websocketpp/common/connection_hdl.hpp>
#include <websocketpp/error.hpp>
#include <websocketpp/logger/levels.hpp>
#include <websocketpp/roles/server_endpoint.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <string>
#include <boost/json.hpp>
#include "MatrixUtility.h"
#include <httplib.h>
#include <stdlib.h>

using namespace std;

typedef websocketpp::server<websocketpp::config::asio> server;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

void on_message(server* s, websocketpp::connection_hdl hdl, server::message_ptr msg)
{
    auto decode_infor = boost::json::parse(msg->get_payload());
    switch(decode_infor.as_object()["content_type"].as_int64())
    {
        case 1:
        {
            string user_name = decode_infor.as_object()["user_name"].as_string().data();
            string user_pwd = decode_infor.as_object()["user_pwd"].as_string().data();
            cout << "start register" << endl;
            string newId = userRegister(user_name, user_pwd);
            cout << "finish register" << endl;
            boost::json::value response = {
                {"content_type", 1},
                { "new_id", newId}
            };
            try{
                cout << boost::json::serialize(response) << endl;
                s->send(hdl, boost::json::serialize(response), msg->get_opcode());
            }catch(websocketpp::exception const& e)
            {
                cerr << e.what() << endl;
            }
            break;
        }

        case 2:
        {
            break;
        }

        case 3:
        {
         break;   
        }

        default:
        {
            cerr << "content_type error" << endl;
        }
    }
}

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
        bool  IsRight = userLogin(atoi(user_id.c_str()), user_pwd);
        boost::json::value response = {
                {"content_type", 2},
                { "is_right", IsRight}
        };
        res.set_content(boost::json::serialize(response), "text/plain");
    });
    svr.listen("0.0.0.0", 9999);
/*    try
    {
        server matrix_server;
        matrix_server.set_reuse_addr(true);
        matrix_server.set_message_handler(bind(&on_message, &matrix_server, ::_1, ::_2));
        matrix_server.set_access_channels(websocketpp::log::alevel::all);
        matrix_server.set_error_channels(websocketpp::log::elevel::all);

        matrix_server.init_asio();
        matrix_server.listen(9999);
        matrix_server.start_accept();
        matrix_server.run();
    }catch(const websocketpp::exception& e)
    {
        cerr << e.what() << endl;
    }*/
    return 0;
}
