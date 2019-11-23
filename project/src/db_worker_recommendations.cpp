#include <db_worker_recommendations.h>


DbWorkerRecommendations::DbWorkerRecommendations() {

}

DbWorkerRecommendations::~DbWorkerRecommendations() {

}

std::vector<Song> DbWorkerRecommendations::get_songs() {
    return std::vector<Song>();
}

std::vector<Song> DbWorkerRecommendations::get_popular_songs(int count) {
    return std::vector<Song>();
}

std::vector<Song> DbWorkerRecommendations::get_new_songs(int count) {
    return std::vector<Song>();
}

std::vector<LikeDislike> DbWorkerRecommendations::get_likes_dislikes() {
    return std::vector<LikeDislike>();
}

std::vector<LikeDislike> DbWorkerRecommendations::get_likes_dislikes(int user_id) {
    return std::vector<LikeDislike>();
}

std::vector<Listen> DbWorkerRecommendations::get_listens() {
    return std::vector<Listen>();
}

std::vector<Listen> DbWorkerRecommendations::get_listens(int user_id) {
    return std::vector<Listen>();
}

std::vector<Recommendation> DbWorkerRecommendations::get_recommendations(int user_id) {
    return std::vector<Recommendation>();
}

void DbWorkerRecommendations::set_recommendations(int user_id, std::vector<Song> songs) {

}
