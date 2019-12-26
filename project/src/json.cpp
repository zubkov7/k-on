//
// Created by andrey on 19.12.2019.
//

#include <sstream>

#include "json.h"

boost::property_tree::ptree parse_to_json(const std::string &str_to_parse) {
    boost::property_tree::ptree root;
    std::stringstream stream(str_to_parse);
    boost::property_tree::read_json(stream, root);
    return root;
}

std::string stringify_json(const boost::property_tree::ptree &root) {
    std::stringstream stream;
    boost::property_tree::write_json(stream, root);
    return stream.str();
}

std::string on_fail(int code, const std::string &message) {
    boost::property_tree::ptree root;
    root.put("status", code);
    root.put("message", message);

    return stringify_json(root);
}
