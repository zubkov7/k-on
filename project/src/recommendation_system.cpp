#include <algorithm>
#include <cmath>
#include <numeric>
#include <unordered_map>

#include "recommendation_system.h"

typedef int id;
typedef int position;


RecommendationSystem::RecommendationSystem() = default;

RecommendationSystem::~RecommendationSystem() = default;

std::vector<int> RecommendationSystem::calculate_recommendations(int user_id, const std::vector<int> &user_ids,
                                                                 const std::vector<int> &song_ids) const {
    int user_pos = 0;
    while (user_ids[user_pos] != user_id) {
        user_pos++;
    }

    std::vector<double> corr_matrix = get_corr_matrix(pref_matrix, pref_matrix[user_pos]);

    DoubleMatrix transposed_matrix = get_transposed(pref_matrix);
    std::vector<double> weight_matrix = get_weight_matrix(corr_matrix, transposed_matrix);

    std::vector<std::pair<int, double>> songs;
    for (int i = 0; i < song_ids.size(); i++) {
        if (pref_matrix[user_pos][i] < 1) {
            songs.emplace_back(std::make_pair(song_ids[i], weight_matrix[i]));
        }
    }
    std::sort(songs.begin(), songs.end(), grater<int, double>());

    std::vector<int> result;
    for (const auto &pair : songs) {
        result.emplace_back(pair.first);
    }
    return result;
}

std::vector<Song> RecommendationSystem::get_similar(int song_id, int count) const {
    // TODO: implement
    return std::vector<Song>();
}

void RecommendationSystem::update_pref_matrix(const std::vector<int> &user_ids, const std::vector<int> &song_ids,
                                              const std::vector<LikeDislike> &likes_dislikes,
                                              const std::vector<Listen> &listens) const {
    pref_matrix.resize(user_ids.size());
    for (auto &row : pref_matrix) {
        row.resize(song_ids.size(), 0.0);
    }

    std::unordered_map<id, position> users_map{};
    for (int i = 0; i < user_ids.size(); i++) {
        users_map[user_ids[i]] = i;
    }

    std::unordered_map<id, position> songs_map{};
    for (int i = 0; i < song_ids.size(); i++) {
        songs_map[song_ids[i]] = i;
    }

    for (const auto &like_dislike : likes_dislikes) {
        int user_pos = users_map[like_dislike.user_id];
        int song_pos = songs_map[like_dislike.song_id];
        pref_matrix[user_pos][song_pos] = like_dislike.value ? 1.0 : -1.0;
    }
    for (const auto &listen : listens) {
        int user_pos = users_map[listen.user_id];
        int song_pos = songs_map[listen.song_id];
        pref_matrix[user_pos][song_pos] += pref_matrix[user_pos][song_pos] > 0 ? 0.3 * listen.count : 0.0;
    }
}

DoubleMatrix RecommendationSystem::get_transposed(const DoubleMatrix &matrix) {
    DoubleMatrix transposed_matrix(matrix[0].size());

    for (const auto &row : matrix) {
        for (int j = 0; j < row.size(); j++) {
            transposed_matrix[j].emplace_back(row[j]);
        }
    }
    return transposed_matrix;
}

double RecommendationSystem::calculate_correlation(const std::vector<double> &first_user,
                                                   const std::vector<double> &second_user) {
    double correlation = 0.0;
    double first_average = 0.0;
    double second_average = 0.0;

    for (int i = 0; i < first_user.size(); i++) {
        correlation += double(first_user[i]) * double(second_user[i]);
        first_average += pow(double(first_user[i]), 2);
        second_average += pow(double(second_user[i]), 2);
    }

    first_average = sqrt(first_average);
    second_average = sqrt(second_average);

    if (first_average != 0) {
        correlation = correlation / first_average;
    }
    if (second_average != 0) {
        correlation = correlation / second_average;
    }
    return correlation;
}

std::vector<double> RecommendationSystem::get_corr_matrix(const DoubleMatrix &pref_matrix,
                                                          const std::vector<double> &user_pref) {
    std::vector<double> corr_matrix;

    for (const auto &i_pref : pref_matrix) {
        corr_matrix.emplace_back(calculate_correlation(i_pref, user_pref));
    }
    return corr_matrix;
}

std::vector<double> RecommendationSystem::get_weight_matrix(const std::vector<double> &corr_matrix,
                                                            const DoubleMatrix &transposed_pref_matrix) {
    std::vector<double> weight_matrix;

    for (const auto & row : transposed_pref_matrix) {
        double weight = std::inner_product(corr_matrix.begin(), corr_matrix.end(), row.begin(), 0.0);
        weight_matrix.emplace_back(weight);
    }
    return weight_matrix;
}
