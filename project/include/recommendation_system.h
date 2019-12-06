#ifndef K_ON_RECOMMENDATION_SYSTEM_H
#define K_ON_RECOMMENDATION_SYSTEM_H

#include <vector>

#include "db_entities.h"


class RecommendationSystem {
public:
    RecommendationSystem();
    ~RecommendationSystem();

    std::vector<int> calculate_recommendations(int user_id, const std::vector<int> &user_ids,
                                               const std::vector<int> &song_ids,
                                               const std::vector<LikeDislike> &likes_dislikes);
    std::vector<Song> get_similar(int song_id, int count);

private:
    std::vector<std::vector<int>> get_pref_matrix(const std::vector<int> &user_ids,
                                                  const std::vector<int> &song_ids,
                                                  const std::vector<LikeDislike> &likes_dislikes);

    std::vector<double> get_corr_matrix(const std::vector<std::vector<int>> &pref_matrix,
                                        const std::vector<int> &user_pref);
    double calculate_correlation(const std::vector<int> &first_user, const std::vector<int> &sec_user);

    std::vector<double> get_weight_matrix(const std::vector<double> &corr_matrix,
                                          const std::vector<std::vector<int>> &transposed_pref_matrix);
    std::vector<std::vector<int>> get_transposed(const std::vector<std::vector<int>> &matrix);
};

template<class T1, class T2>
struct less {
    bool operator()(const std::pair<T1, T2>& l, const std::pair<T1, T2>& r) {
        return l.second < r.second;
    }
};

#endif  // K_ON_RECOMMENDATION_SYSTEM_H
