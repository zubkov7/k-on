#include <gtest/gtest.h>
#include <cstddef>
#include <iostream>
#include <fstream>
#include "include/web_server.h"
#include "include/client.h"
#include <string>
#include <boost/property_tree/json_parser.hpp>
#include <regex>
#include <map>


TEST(NULL, test_parse_html) {
    boost::asio::io_service service_;
    std::shared_ptr<Client> c(new Client(service_));
    std::string html =
            c->parse_html("/Users/elenaelizarova/CLionProjects/k-on/project/index.html", "test1", "test2");
    EXPECT_LT(html.find("test1"), html.size());
    EXPECT_LT(html.find("test2"), html.size());
    EXPECT_LT(html.find("test1"), html.find("test2"));
}


TEST(NULL, test_json_to_songs) {
    boost::asio::io_service service_;
    std::shared_ptr<Client> c(new Client(service_));

    boost::property_tree::ptree response;
    boost::property_tree::read_json("/Users/elenaelizarova/CLionProjects/k-on/project/package.json", response);

    std::string songs = c->json_to_songs(response);
    EXPECT_LT(songs.find("/similarsong?song_id=1"), songs.size());
    EXPECT_LT(songs.find("/similarsong?song_id=8"), songs.size());
    EXPECT_LT(songs.find("/similarsong?song_id=4"), songs.find("/similarsong?song_id=8"));
}

TEST(NULL, test_read_config) {
    Web_server serv("/Users/elenaelizarova/CLionProjects/k-on/project/config.txt");
    std::stringstream buffer;
    std::ifstream in("/Users/elenaelizarova/CLionProjects/k-on/project/config.txt"); //// окрываем файл для чтения
    if (in.is_open()) {
        buffer << in.rdbuf();
    }
    in.close();

    std::string port = buffer.str().substr(
            buffer.str().find("PORT: ") + 6, buffer.str().find("HOST") - 7);
    std::string host = buffer.str().substr(
            buffer.str().find("HOST: ") + 6, buffer.str().find("N") - 18);

    std::string numbr = buffer.str().substr(
            buffer.str().find("NUM_THREADS: ")+13);


    std::map<std::string, std::string> m = serv.read_config();
    EXPECT_EQ(m["PORT"], port);
    EXPECT_EQ(m["NUM_THREADS"],numbr);
    EXPECT_EQ(m["HOST"], host);

}