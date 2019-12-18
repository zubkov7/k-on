//
// Created by andrey on 22.11.2019.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "manager.h"
#include "url_parser.h"

std::string Manager::handle_request(const std::string &request, const std::string &session) {
    UrlParser url_parser;
    url_parser.parse(request);
    std::string path = url_parser.path();

    try {
        if (path == "/login") {
            return on_auth(url_parser, "login");
        }
        if (path == "/logout") {
            return on_logout(session);
        }
        if (path == "/signup") {
            return on_auth(url_parser, "signup");
        }
        if (path == "/like") {
            return on_like(url_parser, session);
        }
        if (path == "/listen") {
            return on_listen(url_parser, session);
        }
        if (path == "/index") {
            return on_index(session);
        }
        if (path == "/top") {
            return on_top();
        }
        if (path == "/recent") {
            return on_recent();
        }
        if (path == "/similarsong") {
            return on_similar_song(url_parser);
        }
        if (path == "/update") {
            return on_update(session);
        }
        if (path == "/") {
            return "flavicon";
        }

        return on_fail(400, "bad request");
    }
    catch (boost::system::system_error const &e) {
        if (e.code() == boost::asio::error::connection_refused) {
            return on_fail(503, "service unavailable");
        } else {
            boost::throw_exception(e);
        }
    }

}

std::string Manager::on_auth(const UrlParser &url_parser, const std::string &method) {
    if (url_parser.has_parameter("login") && url_parser.has_parameter("password")) {
        std::string login = url_parser.get_parameter("login");
        std::string password = url_parser.get_parameter("password");

        boost::property_tree::ptree root;
        root.put("method", method);
        root.put("login", login);
        root.put("password", password);

        std::stringstream request;
        boost::property_tree::write_json(request, root);

        connect(USER_HOST, USER_PORT);
        write(request.str());
        return read();
    } else {
        return on_fail(400, "bad request, please add get parameters: login and password");
    }
}

std::string Manager::on_logout(const std::string &session) {
    boost::property_tree::ptree root;
    root.put("method", "logout");
    root.put("session", session);

    std::stringstream request;
    boost::property_tree::write_json(request, root);

    connect(USER_HOST, USER_PORT);
    write(request.str());
    return read();
}

std::string Manager::on_listen(const UrlParser &url_parser, const std::string &session) {
    if (url_parser.has_parameter("song_id")) {
        std::string song_id = url_parser.get_parameter("song_id");

        boost::property_tree::ptree root;
        root.put("method", "listen");
        root.put("song_id", song_id);
        root.put("session", session);

        std::stringstream request;
        boost::property_tree::write_json(request, root);

        connect(USER_HOST, USER_PORT);
        write(request.str());
        return read();
    } else {
        return on_fail(400, "bad request, please add get parameter: song_id");
    }
}

std::string Manager::on_like(const UrlParser &url_parser, const std::string &session) {
    if (url_parser.has_parameter("song_id") && url_parser.has_parameter("like")) {
        std::string song_id = url_parser.get_parameter("song_id");
        std::string like = url_parser.get_parameter("like");

        boost::property_tree::ptree root;
        root.put("method", "listen");
        root.put("song_id", song_id);
        root.put("like", like);
        root.put("session", session);

        std::stringstream request;
        boost::property_tree::write_json(request, root);

        connect(USER_HOST, USER_PORT);
        write(request.str());
        return read();
    } else {
        return on_fail(400, "bad request, please add get parameter: song_id and like");
    }
}

std::string Manager::on_index(const std::string &session) {
    //TODO() : реализовать метод
    return "On index";
}

std::string Manager::on_top() {
    boost::property_tree::ptree root;
    root.put("method", "get_popular");

    std::stringstream request;
    boost::property_tree::write_json(request, root);

    connect(RECOMMENDATION_HOST, RECOMMENDATION_PORT);
    write(request.str());
    return read();
}

std::string Manager::on_recent() {
    boost::property_tree::ptree root;
    root.put("method", "get_new");

    std::stringstream request;
    boost::property_tree::write_json(request, root);

    connect(RECOMMENDATION_HOST, RECOMMENDATION_PORT);
    write(request.str());
    return read();
}

std::string Manager::on_similar_song(const UrlParser &url_parser) {
    if (url_parser.has_parameter("song_id")) {
        std::string song_id = url_parser.get_parameter("song_id");

        boost::property_tree::ptree root;
        root.put("method", "get_similar");
        root.put("song_id", song_id);

        std::stringstream request;
        boost::property_tree::write_json(request, root);

        connect(RECOMMENDATION_HOST, RECOMMENDATION_PORT);
        write(request.str());
        return read();
    } else {
        return on_fail(400, "bad request, please add get parameter: song_id");
    }
}

std::string Manager::on_update(const std::string &session) {
    // TODO() : реализовать метод
    return "On update";
}

std::string Manager::on_fail(int code, const std::string &message) {
    boost::property_tree::ptree root;
    root.put("status", code);
    root.put("message", message);

    std::stringstream answer;
    boost::property_tree::write_json(answer, root);

    return answer.str();
}
