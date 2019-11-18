#ifndef K_ON_DBWORKERRECOMMENDATIONS_H
#define K_ON_DBWORKERRECOMMENDATIONS_H

#include <vector>

#include "db_wrapper.h"
#include "db_entities.h"

class DbWorkerRecommendations {
public:
    DbWorkerRecommendations();
    ~DbWorkerRecommendations();

    std::vector<Song> get_songs();
    std::vector<Song> get_popular_songs(int count);
    std::vector<Song> get_new_songs(int count);

    std::vector<LikeDislike> get_likes_dislikes();
    std::vector<LikeDislike> get_likes_dislikes(int user_id);

    std::vector<Listen> get_listens();
    std::vector<Listen> get_listens(int user_id);

    std::vector<Recommendations> get_recommendations(int user_id);
    void set_recommendations(int user_id, std::vector<Song> songs);

private:
    DbWrapper db_wrapper;
};

#endif  // K_ON_DBWORKERRECOMMENDATIONS_H
