/*
 * author:Wang Guixin
 * e-mail:1477364283@qq.com
 * date:2022/2/28
 */
#include <algorithm>
#include <boost/json/serialize.hpp>
#include <boost/property_tree/ptree_fwd.hpp>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
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
//#define CPPCONN_LIB_BUILD 1
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

string userRegister(const string& _user_name, const string& _user_pwd)
{
    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    pConn->setSchema(DataBase);
    string newId;
    if(pConn != nullptr)
    {
        try
        {
            cout << "start register" << endl;
            unique_ptr<PreparedStatement> pStmt(pConn->prepareStatement("CALL userRegister(?, ?)"));
            unique_ptr<ResultSet> pRes;
            pStmt->setString(1, _user_name);
            pStmt->setString(2, _user_pwd);
            pStmt->execute();
            pRes.reset(pStmt->getResultSet());
            pRes->next();
            cout << "the new id:";
            cout << pRes->getString("_user_account") << endl;
            newId = pRes->getString("_user_account");
        }
        catch(SQLException& e)
        {
            cerr << e.what() << endl;
        }
        ConnectionPool::getConnectionPool().releaseConnection(pConn);
    }
    return newId;
}

void on_message(server* s, websocketpp::connection_hdl hdl, server::message_ptr msg)
{
    auto decode_infor = boost::json::parse(msg->get_payload());
    switch(decode_infor.as_object()["content_type"].as_int64())
    {
        case 1:
        {
            string user_name = decode_infor.as_object()["user_name"].as_string().data();
            string user_pwd = decode_infor.as_object()["user_pwd"].as_string().data();
            string newId = userRegister(user_name, user_pwd);
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
    try
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
    }
    return 0;
}
