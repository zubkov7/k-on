#ifndef K_ON_DB_RECOMMENDATION_SYSTEM_H
#define K_ON_DB_RECOMMENDATION_SYSTEM_H

#include "db_worker_recommendations.h"
#include "recommendation_system.h"


class DbRecommendationSystem {
public:
    DbRecommendationSystem(const std::string &database, const std::string &host, const std::string &user,
                           const std::string &password);
    ~DbRecommendationSystem();

    std::vector<Song> get_recommendations(int user_id, int count = 0) const;

    void update_recommendations();
    void update_recommendations(int user_id) const;

    std::vector<Song> get_popular(int count) const;
    std::vector<Song> get_new(int count) const;
    std::vector<Song> get_similar(int song_id, int count) const;

private:
    DbWorkerRecommendations worker;
    RecommendationSystem recommendation_system;
};


#endif  // K_ON_DB_RECOMMENDATION_SYSTEM_H
