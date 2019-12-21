#include "db_worker_recommendations.h"


DbWorkerRecommendations::DbWorkerRecommendations(const std::string &database, const std::string &host,
        const std::string &user, const std::string &password) : DbWorker(database, host, user, password) {}

DbWorkerRecommendations::~DbWorkerRecommendations() = default;

std::vector<User> DbWorkerRecommendations::get_users() const {
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

std::vector<Song> DbWorkerRecommendations::get_songs() const {
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

std::vector<LikeDislike> DbWorkerRecommendations::get_likes_dislikes() const {
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

std::vector<Listen> DbWorkerRecommendations::get_listens() const {
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

std::vector<int> DbWorkerRecommendations::get_user_ids() const {
    std::vector<int> users;

    sql::ResultSet *result = wrapper.execute_query(
            "select * from user"
    );

    for (int i = 0; result->next(); i++) {
        users.emplace_back(result->getInt("id"));
    }
    return users;
}

std::vector<int> DbWorkerRecommendations::get_song_ids() const {
    std::vector<int> songs;

    sql::ResultSet *result = wrapper.execute_query(
            "select * from song"
    );

    for (int i = 0; result->next(); i++) {
        songs.emplace_back(result->getInt("id"));
    }
    return songs;
}

std::vector<Song> DbWorkerRecommendations::get_new_songs(int count) const {
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

std::vector<Song> DbWorkerRecommendations::get_popular_songs(int count) const {
    std::vector<Song> songs;

    sql::ResultSet *result = wrapper.execute_query(
            "select song.id, name, author, genre, duration, date, "
            "sum(if(value = true, 1, -1)) as rating, "
            "sum(if(count is null, 0, count)) as listens "
            "from song left join like_dislike on song.id = like_dislike.song_id "
            "left join listen on like_dislike.user_id = listen.user_id and like_dislike.song_id = listen.song_id "
            "group by song.id order by rating desc, listens desc "
            "limit " + std::to_string(count)
    );

    for (int i = 0; result->next(); i++) {
        songs.emplace_back(result->getInt("id"), result->getString("name"), result->getString("author"),
                           result->getString("genre"), result->getInt("duration"),
                           result->getString("date"));
    }
    return songs;
}

std::vector<Song> DbWorkerRecommendations::get_recommendations(int user_id, int count) const {
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
