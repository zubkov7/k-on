#include <gtest/gtest.h>

#include "recommendation_system.h"


// for these tests all members and methods of RecommendationSystem must be public

TEST(RecommendationSystem, calculate_pref_matrix) {
    RecommendationSystem recommendation_system;

    std::vector<int> user_ids = { 1, 2, 3, 4 };
    std::vector<int> song_ids = { 1, 2, 3, 4, 5, 6, 7, 8 };
    std::vector<LikeDislike> likes_dislikes = {
            LikeDislike(1, 2, 1, false),
            LikeDislike(2, 3, 1, true),
            LikeDislike(3, 4, 1, false),
            LikeDislike(4, 2, 2, true),
            LikeDislike(5, 4, 2, true),
            LikeDislike(6, 1, 3, true),
            LikeDislike(7, 1, 4, true),
            LikeDislike(8, 2, 4, true),
            LikeDislike(9, 4, 4, true),
            LikeDislike(10, 1, 5, true),
            LikeDislike(11, 1, 6, true),
            LikeDislike(12, 2, 7, true),
            LikeDislike(13, 3, 7, true),
            LikeDislike(14, 4, 7, true),
            LikeDislike(15, 3, 8, false)
    };
    std::vector<Listen> listens = {
            Listen(1, 2, 1, 1),
            Listen(2, 3, 1, 6),
            Listen(3, 4, 1, 1),
            Listen(4, 2, 2, 7),
            Listen(5, 4, 2, 5),
            Listen(6, 1, 3, 9),
            Listen(7, 1, 4, 26),
            Listen(8, 2, 4, 28),
            Listen(9, 4, 4, 11),
            Listen(10, 1, 5, 20),
            Listen(11, 1, 6, 30),
            Listen(12, 2, 7, 10),
            Listen(13, 3, 7, 13),
            Listen(14, 4, 7, 3),
            Listen(15, 3, 8, 1)
    };

    recommendation_system.update_pref_matrix(user_ids, song_ids, likes_dislikes, listens);

    EXPECT_EQ(4, recommendation_system.pref_matrix.size());
    for (auto &row : recommendation_system.pref_matrix) {
        EXPECT_EQ(8, row.size());
    }

    DoubleMatrix expected_matrix = {
            { 0.0, 0.0, 3.7, 8.8, 7, 10, 0.0, 0.0 },
            { -1, 3.1, 0.0, 9.4, 0.0, 0.0, 4, 0.0 },
            { 2.8, 0.0, 0.0, 0.0, 0.0, 0.0, 4.9, -1 },
            { -1, 2.5, 0.0, 4.3, 0.0, 0.0, 1.9, 0.0 }
    };

    for (int i = 0; i < recommendation_system.pref_matrix.size(); i++) {
        for (int j = 0; j < recommendation_system.pref_matrix[0].size(); j++) {
            EXPECT_DOUBLE_EQ(expected_matrix[i][j], recommendation_system.pref_matrix[i][j]);
        }
    }
}

TEST(RecommendationSystem, calculate_pref_matrix_with_deleted) {
    RecommendationSystem recommendation_system;

    std::vector<int> user_ids = { 1, 3, 5, 7 };
    std::vector<int> song_ids = { 1, 2, 4, 5, 7, 8, 10, 11 };
    std::vector<LikeDislike> likes_dislikes = {
            LikeDislike(1, 3, 1, false),
            LikeDislike(2, 5, 1, true),
            LikeDislike(3, 7, 1, false),
            LikeDislike(4, 3, 2, true),
            LikeDislike(5, 7, 2, true),
            LikeDislike(6, 1, 4, true),
            LikeDislike(7, 1, 5, true),
            LikeDislike(8, 3, 5, true),
            LikeDislike(9, 7, 5, true),
            LikeDislike(10, 1, 7, true),
            LikeDislike(11, 1, 8, true),
            LikeDislike(12, 3, 10, true),
            LikeDislike(13, 5, 10, true),
            LikeDislike(14, 7, 10, true),
            LikeDislike(15, 5, 11, false)
    };
    std::vector<Listen> listens = {
            Listen(1, 3, 1, 1),
            Listen(2, 5, 1, 6),
            Listen(3, 7, 1, 1),
            Listen(4, 3, 2, 7),
            Listen(5, 7, 2, 5),
            Listen(6, 1, 4, 9),
            Listen(7, 1, 5, 26),
            Listen(8, 3, 5, 28),
            Listen(9, 7, 5, 11),
            Listen(10, 1, 7, 20),
            Listen(11, 1, 8, 30),
            Listen(12, 3, 10, 10),
            Listen(13, 5, 10, 13),
            Listen(14, 7, 10, 3),
            Listen(15, 5, 11, 1)
    };

    recommendation_system.update_pref_matrix(user_ids, song_ids, likes_dislikes, listens);

    EXPECT_EQ(4, recommendation_system.pref_matrix.size());
    for (auto &row : recommendation_system.pref_matrix) {
        EXPECT_EQ(8, row.size());
    }

    DoubleMatrix expected_matrix = {
            { 0.0, 0.0, 3.7, 8.8, 7, 10, 0.0, 0.0 },
            { -1, 3.1, 0.0, 9.4, 0.0, 0.0, 4, 0.0 },
            { 2.8, 0.0, 0.0, 0.0, 0.0, 0.0, 4.9, -1 },
            { -1, 2.5, 0.0, 4.3, 0.0, 0.0, 1.9, 0.0 }
    };

    for (int i = 0; i < recommendation_system.pref_matrix.size(); i++) {
        for (int j = 0; j < recommendation_system.pref_matrix[0].size(); j++) {
            EXPECT_DOUBLE_EQ(expected_matrix[i][j], recommendation_system.pref_matrix[i][j]);
        }
    }
}

TEST(RecommendationSystem, add_user_and_song) {
    RecommendationSystem recommendation_system;

    std::vector<int> user_ids(4);
    std::vector<int> song_ids(8);
    std::vector<LikeDislike> likes_dislikes;
    std::vector<Listen> listens;
    recommendation_system.update_pref_matrix(user_ids, song_ids, likes_dislikes, listens);

    user_ids.resize(5);
    song_ids.resize(9);
    recommendation_system.update_pref_matrix(user_ids, song_ids, likes_dislikes, listens);

    EXPECT_EQ(5, recommendation_system.pref_matrix.size());
    for (auto &row : recommendation_system.pref_matrix) {
        EXPECT_EQ(9, row.size());
    }
}

TEST(RecommendationSystem, delete_user_and_song) {
    RecommendationSystem recommendation_system;

    std::vector<int> user_ids(4);
    std::vector<int> song_ids(8);
    std::vector<LikeDislike> likes_dislikes;
    std::vector<Listen> listens;
    recommendation_system.update_pref_matrix(user_ids, song_ids, likes_dislikes, listens);

    user_ids.resize(3);
    song_ids.resize(7);
    recommendation_system.update_pref_matrix(user_ids, song_ids, likes_dislikes, listens);

    EXPECT_EQ(3, recommendation_system.pref_matrix.size());
    for (auto &row : recommendation_system.pref_matrix) {
        EXPECT_EQ(7, row.size());
    }
}

TEST(RecommendationSystem, transposed_matrix_size) {
    DoubleMatrix matrix(3, std::vector<double>(7));
    DoubleMatrix got_matrix = RecommendationSystem::get_transposed(matrix);

    EXPECT_EQ(7, got_matrix.size());
    for (auto &row : got_matrix) {
        EXPECT_EQ(3, row.size());
    }
}

TEST(RecommendationSystem, transposed_matrix_values) {
    DoubleMatrix matrix = {
            { 1.0, 2.0, 3.0, 4.0, 5.0 },
            { 6.0, 7.0, 8.0, 9.0, 10.0 }
    };

    DoubleMatrix got_matrix = RecommendationSystem::get_transposed(matrix);
    DoubleMatrix expected_matrix = {
            { 1.0, 6.0 },
            { 2.0, 7.0 },
            { 3.0, 8.0 },
            { 4.0, 9.0 },
            { 5.0, 10.0 }
    };
    EXPECT_EQ(expected_matrix, got_matrix);
}

TEST(RecommendationSystem, calculate_correlation) {
    std::vector<double> first_user = { 1.0, 0.0, 2.0, 3.0, 1.0, 1.0 };
    std::vector<double> second_user = { 4.0, 2.0, 2.0, 0.0, 1.0, 0.0 };

    double correlation = RecommendationSystem::calculate_correlation(first_user, second_user);
    EXPECT_DOUBLE_EQ(0.45, correlation);
}

TEST(RecommendationSystem, calculate_calculation_zero) {
    std::vector<double> first_user = { 1.0, 0.0, 2.0, 3.0, 1.0, 1.0 };
    std::vector<double> second_user = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    double correlation = RecommendationSystem::calculate_correlation(first_user, second_user);
    EXPECT_DOUBLE_EQ(0.0, correlation);
}

TEST(RecommendationSystem, get_corr_matrix) {
    DoubleMatrix pref_matrix = {
            { 1.0, 0.0, 2.0, 3.0, 1.0, 1.0 },
            { 4.0, 2.0, 2.0, 0.0, 1.0, 0.0 },
            { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }
    };

    std::vector<double> got_matrix = RecommendationSystem::get_corr_matrix(pref_matrix, pref_matrix[0]);
    std::vector<double> expected_matrix = { 1.0, 0.45, 0.0 };
    EXPECT_EQ(3, got_matrix.size());
    EXPECT_EQ(expected_matrix, got_matrix);
}

TEST(RecommendationSystem, get_weight_matrix) {
    std::vector<double> corr_matrix = { 1, 0.45, 0.5 };
    DoubleMatrix transposed_pref_matrix = {
            { 1.0, 4.0, 5.0 },
            { 0.0, 2.0, 0.0 },
            { 2.0, 2.0, 0.0 },
            { 3.0, 0.0, 1.0 },
            { 1.0, 1.0, 1.0 },
            { 1.0, 0.0, 3.0 }
    };

    std::vector<double> got_matrix = RecommendationSystem::get_weight_matrix(corr_matrix, transposed_pref_matrix);
    std::vector<double> expected_matrix = { 5.3, 0.9, 2.9, 3.5, 1.95, 2.5 };
    EXPECT_EQ(6, got_matrix.size());
    EXPECT_EQ(expected_matrix, got_matrix);
}

TEST(RecommendationSystem, calculate_recommendations) {
    RecommendationSystem recommendation_system;
    std::vector<int> user_ids = { 1, 2, 3 };
    std::vector<int> song_ids = { 1, 2, 3, 4, 5, 6 };

    recommendation_system.pref_matrix = {
            { 0.0, 3.0, 4.0, 0.0, 0.0, 0.0 },
            { 1.0, 0.0, 2.0, 3.0, 1.0, 1.0 },
            { 4.0, 2.0, 2.0, 0.0, 1.0, 0.0 }
    };
    std::vector<int> got_songs = recommendation_system.calculate_recommendations(1, user_ids, song_ids);
    std::vector<int> expected_songs = { 1, 4, 5, 6 };

    EXPECT_EQ(expected_songs, got_songs);
}

TEST(RecommendationSystem, calculate_recommendations_with_deleted) {
    RecommendationSystem recommendation_system;
    std::vector<int> user_ids = { 2, 4, 6 };
    std::vector<int> song_ids = { 1, 2, 4, 6, 8, 9 };

    recommendation_system.pref_matrix = {
            { 0.0, 3.0, 4.0, 0.0, 0.0, 0.0 },
            { 1.0, 0.0, 2.0, 3.0, 1.0, 1.0 },
            { 4.0, 2.0, 2.0, 0.0, 1.0, 0.0 }
    };
    std::vector<int> got_songs = recommendation_system.calculate_recommendations(2, user_ids, song_ids);
    std::vector<int> expected_songs = { 1, 6, 8, 9 };

    EXPECT_EQ(expected_songs, got_songs);
}

TEST(RecommendationSystem, get_similar_songs) {
    RecommendationSystem recommendation_system;
    std::vector<int> user_ids = { 1, 2, 3 };
    std::vector<int> song_ids = { 1, 2, 3, 4, 5, 6 };

    recommendation_system.pref_matrix = {
            { 0.0, 3.0, 4.0, 0.0, 0.0, 0.0 },
            { 1.0, 0.0, 2.0, 3.0, 1.0, 1.0 },
            { 4.0, 2.0, 2.0, 0.0, 1.0, 0.0 }
    };
    std::vector<int> got_songs = recommendation_system.get_similar_songs(3, 10, user_ids, song_ids);
    std::vector<int> expected_songs = { 2, 5, 1, 4, 6 };

    EXPECT_EQ(expected_songs, got_songs);
}

TEST(RecommendationSystem, get_similar_songs_with_deleted) {
    RecommendationSystem recommendation_system;
    std::vector<int> user_ids = { 2, 4, 6 };
    std::vector<int> song_ids = { 1, 2, 4, 6, 8, 9 };

    recommendation_system.pref_matrix = {
            { 0.0, 3.0, 4.0, 0.0, 0.0, 0.0 },
            { 1.0, 0.0, 2.0, 3.0, 1.0, 1.0 },
            { 4.0, 2.0, 2.0, 0.0, 1.0, 0.0 }
    };
    std::vector<int> got_songs = recommendation_system.get_similar_songs(4, 10, user_ids, song_ids);
    std::vector<int> expected_songs = { 2, 8, 1, 6, 9 };

    EXPECT_EQ(expected_songs, got_songs);
}

TEST(RecommendationSystem, get_less_similar_songs) {
    RecommendationSystem recommendation_system;
    std::vector<int> user_ids = { 1, 2, 3 };
    std::vector<int> song_ids = { 1, 2, 3, 4, 5, 6 };

    recommendation_system.pref_matrix = {
            { 0.0, 3.0, 4.0, 0.0, 0.0, 0.0 },
            { 1.0, 0.0, 2.0, 3.0, 1.0, 1.0 },
            { 4.0, 2.0, 2.0, 0.0, 1.0, 0.0 }
    };
    std::vector<int> got_songs = recommendation_system.get_similar_songs(3, 3, user_ids, song_ids);
    std::vector<int> expected_songs = { 2, 5, 1 };

    EXPECT_EQ(expected_songs, got_songs);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
