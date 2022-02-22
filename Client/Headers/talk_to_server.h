#ifndef TALK_TO_SERVER_H
#define TALK_TO_SERVER_H

#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/utility.hpp>
#include <boost/thread.hpp>
#include <string>

static boost::asio::io_service IOSERVICE;
static const unsigned _max_msg = 1024;

class Talk_To_Server :
        public boost::enable_shared_from_this<Talk_To_Server>,
        boost::noncopyable
{
private:
    Talk_To_Server(const std::string& user_name, const std::string& pwd) : {

    }
public:

private:
    boost::asio::ip::tcp::socket _sock;
    char _read_buffer[_max_msg];
    char _write_buffe[_max_msg];
    bool _is_online;

};

#endif // TALK_TO_SERVER_H
