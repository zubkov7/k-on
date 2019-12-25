#include <gtest/gtest.h>

#include "db_worker_recommendations.h"


TEST(DbWorkerRecommendations, add_users) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");
    DbWrapper wrapper("test", "localhost", "root", "");

    std::vector<User> expected_users = {
            User(1, "alice", "alice"),
            User(2, "andrew", "andrew"),
            User(3, "oleg", "oleg"),
            User(4, "antony", "antony")
    };

    for (const auto &user : expected_users) {
        EXPECT_TRUE(worker.add_user(user.login, user.password));
    }

    std::vector<User> got_users = worker.get_users();
    EXPECT_EQ(expected_users, got_users);
}

TEST(DbWorkerRecommendations, add_songs) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");

    std::vector<Song> expected_songs = {
            Song(1, "Nice Boi", "Eskimo Callboy", "metalcore", 159, "2019-11-01"),
            Song(2, "Black Files", "Ben Howard", "indie folk", 381, "2011-09-30"),
            Song(3, "Waiting for You", "Nick Cave & The Bad Seeds", "alternative rock", 234, "2019-10-04"),
            Song(4, "Hunger", "The Score", "alternative rock", 123, "2019-08-09"),
            Song(5, "Sweet Disposition", "The Temper Trap", "indie rock", 234, "2008-01-01"),
            Song(6, "Into My Arms", "Nick Cave & The Bad Seeds", "alternative rock", 256, "1997-03-02"),
            Song(7, "Prey", "The Neighbourhood", "indie pop", 282, "2015-10-30"),
            Song(8, "Mr. Brightside", "The Killers", "alternative rock", 222, "2003-09-29")
    };

    for (const auto &song : expected_songs) {
        EXPECT_TRUE(worker.add_song(song.name, song.author, song.genre, song.duration, song.date));
    }

    std::vector<Song> got_songs = worker.get_songs();
    EXPECT_EQ(expected_songs, got_songs);
}

TEST(DbWorkerRecommendations, get_songs_by_ids) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");

    std::vector<int> song_ids = { 1, 3, 4, 6 };
    std::vector<Song> expected_songs = {
            Song(1, "Nice Boi", "Eskimo Callboy", "metalcore", 159, "2019-11-01"),
            Song(3, "Waiting for You", "Nick Cave & The Bad Seeds", "alternative rock", 234, "2019-10-04"),
            Song(4, "Hunger", "The Score", "alternative rock", 123, "2019-08-09"),
            Song(6, "Into My Arms", "Nick Cave & The Bad Seeds", "alternative rock", 256, "1997-03-02")
    };

    std::vector<Song> got_songs = worker.get_songs_by_ids(song_ids);
    EXPECT_EQ(expected_songs, got_songs);
}

TEST(DbWorkerRecommendations, get_new_songs) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");
    const int size = 3;

    std::vector<Song> got_songs = worker.get_new_songs(size);
    EXPECT_EQ(size, got_songs.size());

    std::vector<int> expected_songs = {1, 3, 4};
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(expected_songs[i], got_songs[i].id);
    }
}

TEST(DbWorkerRecommendations, get_all_new_songs) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");
    const int size = 8;

    std::vector<Song> got_songs = worker.get_new_songs(size);
    EXPECT_EQ(size, got_songs.size());

    std::vector<int> expected_songs = {1, 3, 4, 7, 2, 5, 8, 6};
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(expected_songs[i], got_songs[i].id);
    }
}

TEST(DbWorkerRecommendations, get_more_new_songs) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");

    std::vector<Song> got_songs = worker.get_new_songs(10);
    EXPECT_EQ(8, got_songs.size());
}

TEST(DbWorkerRecommendations, add_likes_dislikes) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");
    
    std::vector<LikeDislike> expected_likes_dislikes = {
            LikeDislike(1, 2, 1, false),
            LikeDislike(2, 3, 1, true),
            LikeDislike(3, 4, 1, true),
            LikeDislike(4, 2, 2, false),
            LikeDislike(5, 4, 2, true),
            LikeDislike(6, 1, 3, true),
            LikeDislike(7, 1, 4, false),
            LikeDislike(8, 2, 4, true),
            LikeDislike(9, 4, 4, true),
            LikeDislike(10, 1, 5, false),
            LikeDislike(11, 1, 6, true),
            LikeDislike(12, 2, 7, true),
            LikeDislike(13, 3, 7, true),
            LikeDislike(14, 4, 7, true),
            LikeDislike(15, 3, 8, false)
    };

    for (const auto &like_dislike : expected_likes_dislikes) {
        EXPECT_TRUE(worker.add_like_dislike(like_dislike.user_id, like_dislike.song_id, like_dislike.value));
    }

    std::vector<LikeDislike> got_likes_dislikes = worker.get_likes_dislikes();
    EXPECT_EQ(expected_likes_dislikes, got_likes_dislikes);
}

TEST(DbWorkerRecommendations, change_likes_dislikes) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");

    std::vector<LikeDislike> expected_likes_dislikes = {
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

    std::vector<LikeDislike> changed_likes_dislikes = {
            LikeDislike(3, 4, 1, false),
            LikeDislike(4, 2, 2, true),
            LikeDislike(7, 1, 4, true),
            LikeDislike(10, 1, 5, true),
            LikeDislike(12, 2, 7, true),
    };

    for (const auto &like_dislike : changed_likes_dislikes) {
        EXPECT_TRUE(worker.add_like_dislike(like_dislike.user_id, like_dislike.song_id, like_dislike.value));
    }

    std::vector<LikeDislike> got_likes_dislikes = worker.get_likes_dislikes();
    EXPECT_EQ(expected_likes_dislikes, got_likes_dislikes);
}

TEST(DbWorkerRecommendations, add_listens) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");
    
    std::vector<Listen> expected_listens = {
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
    
    for (const auto &listen : expected_listens) {
        EXPECT_TRUE(worker.add_listen(listen.user_id, listen.song_id, listen.count));
    }

    std::vector<Listen> got_listens = worker.get_listens();
    EXPECT_EQ(expected_listens, got_listens);
}

TEST(DbWorkerRecommendations, get_popular_songs) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");
    const int size = 3;

    std::vector<Song> got_songs = worker.get_popular_songs(size);
    EXPECT_EQ(size, got_songs.size());

    std::vector<int> expected_songs = {4, 7, 2};
    for (int i = 0; i < got_songs.size(); i++) {
        EXPECT_EQ(expected_songs[i], got_songs[i].id);
    }
}

TEST(DbWorkerRecommendations, get_all_popular_songs) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");
    const int size = 8;

    std::vector<Song> got_songs = worker.get_popular_songs(size);
    EXPECT_EQ(size, got_songs.size());

    std::vector<int> expected_songs = {4, 7, 2, 6, 5, 3, 1, 8};
    for (int i = 0; i < got_songs.size(); i++) {
        EXPECT_EQ(expected_songs[i], got_songs[i].id);
    }
}

TEST(DbWorkerRecommendations, get_more_popular_songs) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");

    std::vector<Song> got_songs = worker.get_popular_songs(10);
    EXPECT_EQ(8, got_songs.size());
}

TEST(DbWorkerRecommendations, set_recommendations) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");
    const int user_id = 3;
    const int size = 3;

    std::vector<int> expected_recommendations = {3, 4, 5};
    worker.set_recommendations(user_id, expected_recommendations);

    std::vector<Song> got_recommendations = worker.get_recommendations(user_id, size);
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(expected_recommendations[i], got_recommendations[i].id);
    }
}

TEST(DbWorkerRecommendations, set_new_recommendations) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");
    const int user_id = 3;
    const int size = 3;

    std::vector<int> expected_recommendations = {2, 3, 8};
    worker.set_recommendations(user_id, expected_recommendations);

    std::vector<Song> got_recommendations = worker.get_recommendations(user_id, size);
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(expected_recommendations[i], got_recommendations[i].id);
    }
}

TEST(DbWorkerRecommendations, get_recommendations) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");
    const int user_id = 3;
    const int size = 2;

    std::vector<Song> got_recommendations = worker.get_recommendations(user_id, size);
    EXPECT_EQ(size, got_recommendations.size());
}

TEST(DbWorkerRecommendations, get_more_recommendations) {
    DbWorkerRecommendations worker("test", "localhost", "root", "");
    const int user_id = 3;

    std::vector<Song> got_recommendations = worker.get_recommendations(user_id, 5);
    EXPECT_EQ(3, got_recommendations.size());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
