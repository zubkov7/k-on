//
// Created by andrey on 04.12.2019.
//

#ifndef K_ON_TCPCLIENT_H
#define K_ON_TCPCLIENT_H

#include <boost/asio.hpp>
#include <string>

#define READ_UNTIL_DELIM "\n"

class TcpClient {
public:
    TcpClient();
    ~TcpClient();
    void connect(char *host, char *port);
    void write(const std::string &message);
    std::string read();
    void close_connection();

private:
    unsigned short port_;
    std::string host_;
    boost::asio::io_service service_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::ip::tcp::resolver resolver_;

private:
    std::string to_string(boost::asio::streambuf &buf);
};


#endif  //K_ON_TCPCLIENT_H
