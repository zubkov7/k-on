#ifndef K_ON_DB_RECOMMENDATION_SYSTEM_H
#define K_ON_DB_RECOMMENDATION_SYSTEM_H

#include "db_worker_recommendations.h"
#include "recommendation_system.h"


class DbRecommendationSystem {
public:
    explicit DbRecommendationSystem(const std::string &database);
    ~DbRecommendationSystem();

    std::vector<Song> get_recommendations(int user_id, int count=0);

    void update_recommendations();
    void update_recommendations(int user_id);

    std::vector<Song> get_popular(int count);
    std::vector<Song> get_new(int count);
    std::vector<Song> get_similar(int song_id, int count);

private:
    DbWorkerRecommendations worker;
    RecommendationSystem recommendation_system;
};

#endif  // K_ON_DB_RECOMMENDATION_SYSTEM_H
