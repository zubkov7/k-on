//
// Created by andrey on 19.12.2019.
//

#ifndef K_ON_JSON_H
#define K_ON_JSON_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>

boost::property_tree::ptree parse_to_json(const std::string &str_to_parse);
std::string stringify_json(const boost::property_tree::ptree &root);
std::string on_fail(int code, const std::string &message);

#endif  // K_ON_JSON_H
