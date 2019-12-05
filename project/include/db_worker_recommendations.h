#ifndef K_ON_DBWORKERRECOMMENDATIONS_H
#define K_ON_DBWORKERRECOMMENDATIONS_H

#include "db_worker.h"
#include "db_entities.h"


class DbWorkerRecommendations : public DbWorker {
public:
    explicit DbWorkerRecommendations(const std::string &database);
    ~DbWorkerRecommendations();

    std::vector<User> get_users();

    std::vector<Song> get_songs();
    std::vector<Song> get_new_songs(int count);
    std::vector<Song> get_popular_songs(int count);

    std::vector<LikeDislike> get_likes_dislikes();
    std::vector<LikeDislike> get_likes_dislikes(int user_id);

    std::vector<Listen> get_listens();
    std::vector<Listen> get_listens(int user_id);

    std::vector<Song> get_recommendations(int user_id, int count=0);
    void set_recommendations(int user_id, const std::vector<int> &song_ids);
};

#endif  // K_ON_DBWORKERRECOMMENDATIONS_H
