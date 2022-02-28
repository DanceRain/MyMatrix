/*
 * author:Wang Guixin
 * e-mail:1477364283@qq.com
 * date:2022/2/28
 */
#include <algorithm>
#include <boost/property_tree/ptree_fwd.hpp>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>
#include <memory>
#include "src/mysqlPool.h"
#include <websocketpp/common/connection_hdl.hpp>
#include <websocketpp/connection_base.hpp>
#include <websocketpp/error.hpp>
#include <websocketpp/logger/levels.hpp>
#include <websocketpp/roles/server_endpoint.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <string>
#include <boost/json.hpp>

using namespace std;
using namespace sql;
const string DataBase = "MatrixDB";

typedef websocketpp::server<websocketpp::config::asio> server;

string userRegister(const string& _user_name, const string& _user_pwd)
{
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    cout << ConnectionPool::getConnectionPool().getCurrentSize() << endl;
    if(pConn != nullptr)
    {
        cout << "start register" << endl;
        unique_ptr<Statement> pStmt(pConn->createStatement());
        pStmt->execute("use " + DataBase + ";");
        unique_ptr<ResultSet> pRes(pStmt->executeQuery("call userRegister(\"" + _user_name + "\"," + "\"" + _user_pwd + "\")"));
        while(pRes->next())
        {
            return pRes->getString("new_id");
        } 
    }
    ConnectionPool::getConnectionPool().releaseConnection(pConn);
    return "";
}

void on_message(websocketpp::connection_hdl, server::message_ptr msg)
{
    auto decode_infor = boost::json::parse(msg->get_payload());
    switch(decode_infor.as_object()["content_type"].as_int64())
    {
        case 1:
        {
            string user_name = decode_infor.as_object()["user_name"].as_string().data();
            string user_pwd = decode_infor.as_object()["user_pwd"].as_string().data();
            userRegister(user_name, user_pwd);
        }break;

        case 2:
        {

        }break;

        case 3:
        {
            
        }break;

        default:
        {
            cerr << "content_type error" << endl;
        }
    }
}


int main()
{
    try
    {
        server print_server;
        print_server.set_message_handler(&on_message);
        print_server.set_access_channels(websocketpp::log::alevel::all);
        print_server.set_error_channels(websocketpp::log::elevel::all);

        print_server.init_asio();
        print_server.listen(9999);
        print_server.start_accept();
        print_server.run();
    }catch(const websocketpp::exception& e)
    {
        cerr << e.what() << endl;
    }
    return 0;
}
