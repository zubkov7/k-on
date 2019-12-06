#ifndef SERVER_H
#define SERVER_H

#define BOOST_ASIO_HAS_STD_STRING_VIEW
#include "boost/asio.hpp"

class HTTP_worker {
public:
    HTTP_worker() {}

    ~HTTP_worker() {}

    bool start_work();

    boost::asio::ip::tcp::socket set_socket();

    bool is_busy(bool busy);

private:
    //разноситьь по приватам функции и поля
    int timeout;

//    Request request;

//    socket client_socket;

    bool busy;


//    Manager manager;

private:

    void handle();

//    bool write(socket client_socket);

//    bool read(socket client_socket);

//    bool process_request(Request request);

    bool check_deadline(int timeout);
};

class HTTP_master {
public:
    ~HTTP_master() {}

private:
    HTTP_master(std::string server, int port, int nuw_workers) {}

    std::vector<HTTP_worker> workers;
//    socket server_socket;
    std::string server;
    int port;
    int time_sleep;

    HTTP_worker create_worker(std::vector<HTTP_worker> workers);

    bool kill_worker(HTTP_worker worker);

//    bool connect(socket client_socket, std::vector<HTTP_worker> workers);

//    bool read_socket(socket server_socket);

    bool get_free_worker(std::vector<HTTP_worker> workers);


};

class Client : public std::enable_shared_from_this<Client> {
    boost::asio::ip::tcp::socket m_Sock;
    char m_Buf[1024];
    char m_SendBuf[1024];

public:
    Client(boost::asio::io_service &io) : m_Sock(io) {}

    boost::asio::ip::tcp::socket &sock() { return m_Sock; }

    void read();

    void handleRead(const boost::system::error_code &e,
                    std::size_t bytes_transferred);
};

class Web_server {
public:
    Web_server() : acceptor_(service_) {}

    ~Web_server() {}

    void start();

    void restart();

    void stop();

private:
    int port;

    boost::asio::ip::address host;

    int threads_num;

    boost::asio::io_service service_;

    boost::asio::ip::tcp::acceptor acceptor_;
private:
    std::map<std::string, std::string> read_config();

    void onAccept(std::shared_ptr<Client> c, const boost::system::error_code &e);

    void startAccept();

    void run();

};

#endif
