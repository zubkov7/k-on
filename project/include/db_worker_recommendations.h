#ifndef K_ON_DB_WORKER_RECOMMENDATIONS_H
#define K_ON_DB_WORKER_RECOMMENDATIONS_H

#include <vector>

#include "db_worker.h"
#include "db_entities.h"


class DbWorkerRecommendations : public DbWorker {
public:
    DbWorkerRecommendations(const std::string &database, const std::string &host,
                            const std::string &user, const std::string &password);
    ~DbWorkerRecommendations();

    std::vector<User> get_users() const;
    std::vector<Song> get_songs() const;
    std::vector<LikeDislike> get_likes_dislikes() const;
    std::vector<Listen> get_listens() const;

    std::vector<int> get_user_ids() const;
    std::vector<int> get_song_ids() const;

    std::vector<Song> get_new_songs(int count) const;
    std::vector<Song> get_popular_songs(int count) const;
    std::vector<Song> get_recommendations(int user_id, int count = 0) const;
    void set_recommendations(int user_id, const std::vector<int> &song_ids) const;
};


#endif  // K_ON_DB_WORKER_RECOMMENDATIONS_H
