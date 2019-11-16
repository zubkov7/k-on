#ifndef PROJECT_INCLUDE_RECOMMENDATION_SYSTEM_H_
#define PROJECT_INCLUDE_RECOMMENDATION_SYSTEM_H_

#include <vector>

#include "db_worker_recommendation.h"
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

#endif  // PROJECT_INCLUDE_RECOMMENDATION_SYSTEM_H_
