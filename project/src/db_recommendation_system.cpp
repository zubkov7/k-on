#include "db_recommendation_system.h"


DbRecommendationSystem::DbRecommendationSystem(const std::string &database, const std::string &host,
        const std::string &user, const std::string &password) : worker(database, host, user, password) {}

DbRecommendationSystem::~DbRecommendationSystem() = default;

std::vector<Song> DbRecommendationSystem::get_recommendations(int user_id, int count) const {
    return worker.get_recommendations(user_id, count);
}

void DbRecommendationSystem::update_recommendations() {
    std::vector<int> user_ids = worker.get_user_ids();
    std::vector<int> song_ids = worker.get_song_ids();
    std::vector<LikeDislike> likes_dislikes = worker.get_likes_dislikes();
    std::vector<Listen> listens = worker.get_listens();

    recommendation_system.update_pref_matrix(user_ids, song_ids, likes_dislikes, listens);
    for (int i : user_ids) {
        std::vector<int> recommends = recommendation_system.calculate_recommendations(i, user_ids, song_ids);
        worker.set_recommendations(i, recommends);
    }
}

void DbRecommendationSystem::update_recommendations(int user_id) {
    std::vector<int> user_ids = worker.get_user_ids();
    std::vector<int> song_ids = worker.get_song_ids();
    std::vector<LikeDislike> likes_dislikes = worker.get_likes_dislikes();
    std::vector<Listen> listens = worker.get_listens();

    recommendation_system.update_pref_matrix(user_ids, song_ids, likes_dislikes, listens);
    std::vector<int> recommends = recommendation_system.calculate_recommendations(user_id, user_ids, song_ids);
    worker.set_recommendations(user_id, recommends);
}

std::vector<Song> DbRecommendationSystem::get_popular(int count) const {
    return worker.get_popular_songs(count);
}

std::vector<Song> DbRecommendationSystem::get_new(int count) const {
    return worker.get_new_songs(count);
}

std::vector<Song> DbRecommendationSystem::get_similar(int song_id, int count) {
    return recommendation_system.get_similar(song_id, count);
}
