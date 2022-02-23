#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>
#include <memory>
#include "src/mysqlPool.h"
#include <websocketpp/common/connection_hdl.hpp>
#include <websocketpp/connection_base.hpp>
#include <websocketpp/logger/levels.hpp>
#include <websocketpp/roles/server_endpoint.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

using namespace std;
using namespace sql;


typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(websocketpp::connection_hdl, server::message_ptr msg)
{
    cout << msg->get_payload() << endl;
}


int main()
{
/*    Connection* pConn = ConnectionPool::getConnectionPool().getConnectionFromPool();
    if(pConn != nullptr)
    {
        cout << "Succesful! Current size is " << ConnectionPool::getConnectionPool().getCurrentSize() << endl;
        unique_ptr<Statement> pStmt(pConn->createStatement());
        pStmt->execute("use MatrixDB");
        unique_ptr<ResultSet> pRes(pStmt->executeQuery("call getUserTable()"));
        cout << "find " << pRes->rowsCount() << " data";
        while(pRes->next())
        {
            cout << "accout: " << pRes->getString("user_account");
            cout << "password: " << pRes->getString("user_pwd");
        }

    }*/
    server print_server;
    print_server.set_message_handler(&on_message);
    print_server.set_access_channels(websocketpp::log::alevel::all);
    print_server.set_error_channels(websocketpp::log::elevel::all);
    
    print_server.init_asio();
    print_server.listen(9999);
    print_server.start_accept();
    cout <<"hello" << endl;
    print_server.run();
    return 0;
}
