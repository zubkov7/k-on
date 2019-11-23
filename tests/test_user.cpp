#include <gtest/gtest.h>
#include <iostream>

#include "user.h"
#include "db_worker_user.h"

#define DB_PATH "db_path"
#define DB_HOST "localhost"
#define DB_LOGIN "user"
#define DB_PASS "pass"

#define WRONG_USER_ID 2
#define WRONG_USER_LOGIN "wrong_login"
#define WRONG_USER_PASS "wrong_pass"

#define TEST_USER_ID 1
#define TEST_USER_LOGIN "user"
#define TEST_USER_PASS "pass"

#define NEW_USER_ID 2
#define NEW_USER_LOGIN "new_user"
#define NEW_USER_PASS "new_pass"

#define TEST_SONG_ID 1

TEST(user_test, get_user_positive) {
    User tmp_user = User(DB_PATH, DB_HOST, DB_LOGIN, DB_PASS);

    user test_user = user(TEST_USER_ID, TEST_USER_LOGIN, TEST_USER_PASS);

    user received_user = tmp_user.get_user(TEST_USER_ID);

    EXPECT_EQ(test_user, received_user);
}

TEST(user_test, get_user_negative) {
    User tmp_user = User(DB_PATH, DB_HOST, DB_LOGIN, DB_PASS);

    try {
        user received_user = tmp_user.get_user(WRONG_USER_ID);
        FAIL() << "User::get_user should throw an error\n";
    }
    catch (MySqlException e) {
        EXPECT_EQ(e.what(), "User doesn't exists");
    }
}

TEST(user_test, login_positive) {
    User tmp_user = User(DB_PATH, DB_HOST, DB_LOGIN, DB_PASS);

    EXPECT_TRUE(tmp_user.login(TEST_USER_LOGIN, TEST_USER_PASS));
}

TEST(user_test, login_negative) {
    User tmp_user = User(DB_PATH, DB_HOST, DB_LOGIN, DB_PASS);

    EXPECT_FALSE(tmp_user.login(WRONG_USER_LOGIN, WRONG_USER_PASS));
}

TEST(user_test, register_positive) {
    User tmp_user = User(DB_PATH, DB_HOST, DB_LOGIN, DB_PASS);

    try {
        tmp_user.get_user(NEW_USER_ID);
        FAIL() << "User::get_user should throw an error\n";
    }
    catch (MySqlException e) {
        EXPECT_EQ(e.what(), "User doesn't exists");
    }

    user new_user = user(NEW_USER_ID, NEW_USER_LOGIN, NEW_USER_PASS);

    EXPECT_TRUE(tmp_user.register_user(NEW_USER_LOGIN, NEW_USER_PASS));

    user received_user = tmp_user.get_user(NEW_USER_ID);

    EXPECT_EQ(new_user, received_user);
}

TEST(user_test, register_negative) {
    User tmp_user = User(DB_PATH, DB_HOST, DB_LOGIN, DB_PASS);

    try {
        tmp_user.register_user(NEW_USER_LOGIN, NEW_USER_PASS);
        FAIL() << "User::register_user should throw an error\n";
    }
    catch (MySqlException e) {
        EXPECT_EQ(e.what(), "Login already in use");
    }
}

TEST(user_test, increment_listening_positive) {
    DbWorkerUser db_worker_user = DbWorkerUser(DB_PATH, DB_HOST, DB_LOGIN, DB_PASS);

    int current_listening = db_worker_user.get_listening(TEST_SONG_ID, TEST_USER_ID);

    User tmp_user = User(DB_PATH, DB_HOST, DB_LOGIN, DB_PASS);
    int new_listening = tmp_user.increment_listening(TEST_SONG_ID, TEST_USER_ID);

    EXPECT_EQ(new_listening, current_listening + 1);
}

TEST(user_test, increment_listening_negative) {
    DbWorkerUser db_worker_user = DbWorkerUser(DB_PATH, DB_HOST, DB_LOGIN, DB_PASS);

    int current_listening = db_worker_user.get_listening(TEST_SONG_ID, TEST_USER_ID);

    User tmp_user = User(DB_PATH, DB_HOST, DB_LOGIN, DB_PASS);
    int new_listening = tmp_user.increment_listening(TEST_SONG_ID, TEST_USER_ID);

    EXPECT_NE(new_listening, current_listening);
}

TEST(user_test, like_song) {
    User tmp_user = User(DB_PATH, DB_HOST, DB_LOGIN, DB_PASS);
    bool new_like = tmp_user.like_song(TEST_SONG_ID, TEST_SONG_ID, true);

    DbWorkerUser db_worker_user = DbWorkerUser(DB_PATH, DB_HOST, DB_LOGIN, DB_PASS);
    EXPECT_TRUE(db_worker_user.get_like_song(TEST_SONG_ID, TEST_USER_ID));
}