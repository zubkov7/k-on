#ifndef K_ON_CLIENT_H
#define K_ON_CLIENT_H

#include "boost/asio.hpp"
#include <boost/property_tree/ptree.hpp>

#include <string>


class Client : public std::enable_shared_from_this<Client> {
    boost::asio::ip::tcp::socket m_Sock;
    char m_Buf[4096];
    char m_SendBuf[4096];

public:
    Client(boost::asio::io_service &io) : m_Sock(io) {}
    boost::asio::ip::tcp::socket &sock() { return m_Sock; }
    void read();
    std::string parse_html(std::string html_way,std::string user_info,std::string data_info);
    std::string json_to_songs(boost::property_tree::ptree& response,std::string url);
    void handle_read(const boost::system::error_code &e,
                     std::size_t bytes_transferred);
};


#endif  // K_ON_CLIENT_H