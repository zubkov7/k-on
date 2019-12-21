//
// Created by andrey on 18.12.2019.
//

#ifndef K_ON_URL_PARSER_H
#define K_ON_URL_PARSER_H

#include <string>
#include <map>


class UrlParser {
public:
    UrlParser() {}
    ~UrlParser() {}
    void parse(const std::string &url);
    std::string path() const;
    std::map<std::string, std::string> query() const;
    bool has_parameter(const std::string &parameter) const;
    std::string get_parameter(const std::string &parameter) const;

private:
    std::map<std::string, std::string> query_;
    std::string path_;
};


#endif  // K_ON_URL_PARSER_H
