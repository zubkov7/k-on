#ifndef K_ON_RECOMMENDATION_SYSTEM_H
#define K_ON_RECOMMENDATION_SYSTEM_H

#include <vector>

#include "db_entities.h"


typedef std::vector<std::vector<double>> DoubleMatrix;

template<class T1, class T2>
struct grater {
    bool operator()(const std::pair<T1, T2> &l, const std::pair<T1, T2> &r) {
        return l.second > r.second;
    }
};

class RecommendationSystem {
public:
    RecommendationSystem();
    ~RecommendationSystem();

    std::vector<int> calculate_recommendations(int user_id, const std::vector<int> &user_ids,
                                               const std::vector<int> &song_ids) const;
    std::vector<Song> get_similar(int song_id, int count) const;

    void update_pref_matrix(const std::vector<int> &user_ids, const std::vector<int> &song_ids,
                            const std::vector<LikeDislike> &likes_dislikes, const std::vector<Listen> &listens) const;

private:
    mutable DoubleMatrix pref_matrix;

private:
    static DoubleMatrix get_transposed(const DoubleMatrix &matrix);
    static double calculate_correlation(const std::vector<double> &first_user, const std::vector<double> &second_user);

    static std::vector<double> get_corr_matrix(const DoubleMatrix &pref_matrix, const std::vector<double> &user_pref);
    static std::vector<double> get_weight_matrix(const std::vector<double> &corr_matrix,
                                                 const DoubleMatrix &transposed_pref_matrix);
};


#endif  // K_ON_RECOMMENDATION_SYSTEM_H
