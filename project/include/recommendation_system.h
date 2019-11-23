#ifndef K_ON_RECOMMENDATION_SYSTEM_H
#define K_ON_RECOMMENDATION_SYSTEM_H

#include "db_worker_recommendations.h"
#include "db_entities.h"


class RecommendationSystem {
public:
    RecommendationSystem();
    ~RecommendationSystem();

    std::vector<Song> get_recommendations(int user_id);
    void update_recommendations();
    std::vector<Song> get_popular();
    std::vector<Song> get_new();
    std::vector<Song> get_similar(int song_id);

private:
    DbWorkerRecommendation db_worker;
};

#endif  // K_ON_RECOMMENDATION_SYSTEM_H
