#include "db_worker_recommendations.h"


DbWorkerRecommendations::DbWorkerRecommendations(const std::string &database) : DbWorker(database) {}

DbWorkerRecommendations::~DbWorkerRecommendations() = default;

std::vector<User> DbWorkerRecommendations::get_users() {
    std::vector<User> users;

    sql::ResultSet *result = wrapper.execute_query(
            "select * from user"
    );

    for (int i = 0; result->next(); i++) {
        users.emplace_back(result->getInt("id"), result->getString("login"),
                           result->getString("password"));
    }
    return users;
}

std::vector<Song> DbWorkerRecommendations::get_songs() {
    std::vector<Song> songs;

    sql::ResultSet *result = wrapper.execute_query(
            "select * from song"
    );

    for (int i = 0; result->next(); i++) {
        songs.emplace_back(result->getInt("id"), result->getString("name"), result->getString("author"),
                           result->getString("genre"), result->getInt("duration"),
                           result->getString("date"));
    }
    return songs;
}

std::vector<Song> DbWorkerRecommendations::get_new_songs(int count) {
    std::vector<Song> songs;

    sql::ResultSet *result = wrapper.execute_query(
            "select * from song "
            "order by date desc "
            "limit " + std::to_string(count)
    );

    for (int i = 0; result->next(); i++) {
        songs.emplace_back(result->getInt("id"), result->getString("name"), result->getString("author"),
                           result->getString("genre"), result->getInt("duration"),
                           result->getString("date"));
    }

    return songs;
}

std::vector<Song> DbWorkerRecommendations::get_popular_songs(int count) {
    // TODO: implement
    return std::vector<Song>();
}

std::vector<LikeDislike> DbWorkerRecommendations::get_likes_dislikes() {
    std::vector<LikeDislike> likes_dislikes;

    sql::ResultSet *result = wrapper.execute_query(
            "select * from like_dislike"
    );

    for (int i = 0; result->next(); i++) {
        likes_dislikes.emplace_back(result->getInt("id"), result->getInt("user_id"), result->getInt("song_id"),
                                    result->getBoolean("value"));
    }
    return likes_dislikes;
}

std::vector<LikeDislike> DbWorkerRecommendations::get_likes_dislikes(int user_id) {
    std::vector<LikeDislike> likes_dislikes;

    sql::ResultSet *result = wrapper.execute_query(
            "select * from like_dislike "
            "where user_id = " + std::to_string(user_id)
    );

    for (int i = 0; result->next(); i++) {
        likes_dislikes.emplace_back(result->getInt("id"), result->getInt("user_id"), result->getInt("song_id"),
                                    result->getBoolean("value"));
    }
    return likes_dislikes;
}

std::vector<Listen> DbWorkerRecommendations::get_listens() {
    std::vector<Listen> listens;

    sql::ResultSet *result = wrapper.execute_query(
            "select * from listen"
    );

    for (int i = 0; result->next(); i++) {
        listens.emplace_back(result->getInt("id"), result->getInt("user_id"), result->getInt("song_id"),
                             result->getInt("count"));
    }
    return listens;
}

std::vector<Listen> DbWorkerRecommendations::get_listens(int user_id) {
    std::vector<Listen> listens;

    sql::ResultSet *result = wrapper.execute_query(
            "select * from listen "
            "where user_id = " + std::to_string(user_id)
    );

    for (int i = 0; result->next(); i++) {
        listens.emplace_back(result->getInt("id"), result->getInt("user_id"), result->getInt("song_id"),
                             result->getInt("count"));
    }
    return listens;
}

std::vector<Song> DbWorkerRecommendations::get_recommendations(int user_id, int count) {
    std::vector<Song> songs;

    sql::ResultSet *result = nullptr;
    if (count == 0) {
        result = wrapper.execute_query(
                "select * from recommendation "
                "join song on recommendation.song_id = song.id "
                "where user_id = " + std::to_string(user_id)
        );
    } else {
        result = wrapper.execute_query(
                "select * from recommendation "
                "join song on recommendation.song_id = song.id "
                "where user_id = " + std::to_string(user_id) +
                " limit " + std::to_string(count)
        );
    }

    for (int i = 0; result->next(); i++) {
        songs.emplace_back(result->getInt("id"), result->getString("name"), result->getString("author"),
                           result->getString("genre"), result->getInt("duration"),
                           result->getString("date"));
    }

    return songs;
}

void DbWorkerRecommendations::set_recommendations(int user_id, const std::vector<int> &song_ids) {
    wrapper.execute(
            "delete from recommendation "
            "where user_id = " + std::to_string(user_id)
    );

    for (int song_id : song_ids) {
        wrapper.execute(
                "insert into recommendation (user_id, song_id) "
                "values (" + std::to_string(user_id) + ", " + std::to_string(song_id) + ")"
        );
    }
}
