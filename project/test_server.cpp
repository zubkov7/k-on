#include <gtest/gtest.h>
#include <cstddef>
#include <iostream>
#include <iostream>
#include <fstream>

extern "C" {
#include "server.h"
}

TEST(NULL, check_start) {
    std::string host = "127.0.0.1";
    std::string result = "";
    int port = 8000;
    char buffer[128];
    std::ofstream outfile1("config.txt");
    outfile1 << "workers:4 host:127.0.0.1 port:8000" << std::endl;
    outfile1.close();
    std::ofstream outfile2("index.html");
    outfile2 << "<html><head></head><body>Hello , world!</body></html>" << std::endl;
    outfile2.close();
    Web_server serv = new Web_server();
    serv.start();
    FILE *cmd = popen("telnet 127.0.0.1:8000", "r");
    while (!feof(cmd)) {
        // use buffer to read and add to result
        if (fgets(buffer, 128, cmd) != NULL)
            result += buffer;
    }
    pclose(cmd);
    EXPECT_EQ("Hello , world!", result);
}

TEST(NULL, check_stop) {
    std::string host = "127.0.0.1";
    std::string result = "";
    int port = 8000;
    char buffer[128];
    std::ofstream outfile1("config.txt");
    outfile1 << "workers:4 host:127.0.0.1 port:8000" << std::endl;
    outfile1.close();
    std::ofstream outfile2("index.html");
    outfile2 << "<html><head></head><body>Hello , world!</body></html>" << std::endl;
    outfile2.close();
    Web_server serv = new Web_server();
    serv.start();
    serv.stop();
    FILE *cmd = popen("telnet 127.0.0.1:8000", "r");
    while (!feof(cmd)) {
        // use buffer to read and add to result
        if (fgets(buffer, 128, cmd) != NULL)
            result += buffer;
    }
    pclose(cmd);
    EXPECT_EQ("Unable to connect to remote host", result);
}

TEST(NULL, check_restart) {
    std::ofstream outfile1("config.txt");
    outfile1 << "workers:4 host:127.0.0.1 port:8000" << std::endl;
    Web_server serv = new Web_server();
    serv.start();
    std::string line;
    std::string line1;
    std::ifstream myfile("pid.txt");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {}
        myfile.close();
    }
    serv.restart();
    if (myfile.is_open()) {
        while (getline(myfile, line1)) {}
        myfile.close();
    }
    EXPECT_NE(line, line1);

}