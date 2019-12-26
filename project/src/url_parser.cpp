//
// Created by andrey on 18.12.2019.
//

#include <string>
#include <algorithm>
#include <cctype>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <exception>

#include "url_parser.h"

template <typename Iterator>
struct key_value_sequence
        : boost::spirit::qi::grammar<Iterator, std::map<std::string, std::string>()>
{
    key_value_sequence()
            : key_value_sequence::base_type(query)
    {
        query =  pair >> *((boost::spirit::qi::lit(';') | '&') >> pair);
        pair  =  key >> -('=' >> value);
        key   =  boost::spirit::qi::char_("a-zA-Z_") >> *boost::spirit::qi::char_("a-zA-Z_0-9");
        value = +boost::spirit::qi::char_("a-zA-Z_0-9_?_=");
    }

    boost::spirit::qi::rule<Iterator, std::map<std::string, std::string>()> query;
    boost::spirit::qi::rule<Iterator, std::pair<std::string, std::string>()> pair;
    boost::spirit::qi::rule<Iterator, std::string()> key, value;
};

void UrlParser::parse(const std::string &url) {
    std::string::const_iterator path_i = find(url.begin(), url.end(), '/');
    path_.reserve(distance(url.begin(), path_i));
    transform(url.begin(), path_i,
              back_inserter(path_),
              std::ptr_fun<int,int>(tolower)); // host is icase
    std::string::const_iterator query_i = find(path_i, url.end(), '?');
    path_.assign(path_i, query_i);
    if( query_i != url.end() )
        ++query_i;
    std::string query;
    query.assign(query_i, url.end());

    key_value_sequence<std::string::iterator> p;
    boost::spirit::qi::parse(query.begin(), query.end(), p, query_);
}

std::string UrlParser::path() const {
    return path_;
}

std::map<std::string, std::string> UrlParser::query() const {
    return query_;
}

bool UrlParser::has_parameter(const std::string & parameter) const {
    return query_.find(parameter) != query_.end();
}

std::string UrlParser::get_parameter(const std::string & parameter) const {
    auto iter = query_.find(parameter);
    if (iter != query_.end()) {
        return iter->second;
    } else {
        return "";
    }
}
