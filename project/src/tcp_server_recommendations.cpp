#include "tcp_server_recommendations.h"
#include "json.h"

#define NUMBER_OF_SONGS 10


TcpServerRecommendations::TcpServerRecommendations(unsigned short port, const std::string &database,
        const std::string &host, const std::string &user, const std::string &password) :
        TcpServer(port), recommendation_system(database, host, user, password) {}

std::string TcpServerRecommendations::handle_request(const std::string &request) const {
    try {
        boost::property_tree::ptree root = parse_to_json(request);
        auto method = root.get<std::string>("method");

        if (method == "get_recommendations") {
            return on_recommendations(root);
        }
        if (method == "get_popular") {
            return on_top(root);
        }
        if (method == "get_new") {
            return on_recent(root);
        }
        if (method == "get_similar") {
            return on_similar(root);
        }
        if (method == "update_recommendations") {
            return on_update(root);
        }

        return on_fail(500, "Internal server error: request to the wrong method");
    }
    catch (boost::property_tree::ptree_bad_path const &e) {
        std::cout << e.what() << std::endl;
        return on_fail(500, "Internal server error");
    }
    catch (boost::property_tree::json_parser_error const &e) {
        std::cout << e.what() << std::endl;
        return on_fail(500, "Internal server error");
    }
}

std::string TcpServerRecommendations::songs_to_answer(const std::vector<Song> &songs) const {
    boost::property_tree::ptree answer;
    answer.put("status", 200);

    boost::property_tree::ptree songs_array;
    for (const auto& song : songs) {
        boost::property_tree::ptree element;
        element.put("id", song.id);
        element.put("name", song.name);
        element.put("author", song.author);
        element.put("genre", song.genre);
        element.put("duration", song.duration);
        element.put("date", song.date);

        songs_array.push_back(std::make_pair("", element));
    }
    answer.add_child("songs", songs_array);

    return stringify_json(answer);
}

std::string TcpServerRecommendations::on_recommendations(const boost::property_tree::ptree &root) const {
    int user = root.get<int>("user_id");
    
    std::vector<Song> songs;
    try {
        songs = recommendation_system.get_recommendations(user, NUMBER_OF_SONGS);
    } catch (sql::SQLException &e) {
        std::cout << e.what() << std::endl;
        return on_fail(500, "Database error");
    }
    
    return songs_to_answer(songs);
}

std::string TcpServerRecommendations::on_top(const boost::property_tree::ptree &root) const {
    std::vector<Song> songs;
    try {
        songs = recommendation_system.get_popular(NUMBER_OF_SONGS);
    } catch (sql::SQLException &e) {
        std::cout << e.what() << std::endl;
        return on_fail(500, "Database error");
    }

    return songs_to_answer(songs);
}

std::string TcpServerRecommendations::on_recent(const boost::property_tree::ptree &root) const {
    std::vector<Song> songs;
    try {
        songs = recommendation_system.get_new(NUMBER_OF_SONGS);
    } catch (sql::SQLException &e) {
        std::cout << e.what() << std::endl;
        return on_fail(500, "Database error");
    }

    return songs_to_answer(songs);
}

std::string TcpServerRecommendations::on_similar(const boost::property_tree::ptree &root) const {
    int song = root.get<int>("song_id");

    std::vector<Song> songs;
    try {
        songs = recommendation_system.get_similar(song, NUMBER_OF_SONGS);
    } catch (sql::SQLException &e) {
        std::cout << e.what() << std::endl;
        return on_fail(500, "Database error");
    }

    return songs_to_answer(songs);
}

std::string TcpServerRecommendations::on_update(const boost::property_tree::ptree &root) const {
    int user = root.get<int>("user_id");

    std::vector<Song> songs;
    try {
        recommendation_system.update_recommendations(user);
    } catch (sql::SQLException &e) {
        std::cout << e.what() << std::endl;
        return on_fail(500, "Database error");
    }

    return on_recommendations(root);
}
