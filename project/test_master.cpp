#include <gtest/gtest.h>
#include <cstddef>
#include <iostream>
#include "server.h"


TEST(NULL, check_create) {
    HTTP_master master1 = new HTTP_master("127.0.0.1", 8000, 1);
    EXPECT_EQ(master1.workers.size(), 1);
    EXPECT_EQ(master1.server, "127.0.0.1");
    EXPECT_EQ(master1.port, 8000);
}

TEST(NULL, worker_obey) {
    HTTP_master master1 = new HTTP_master("127.0.0.1", 8000, 1);
    EXPECT_EQ(master1.create_worker(master1.workers), true);
    EXPECT_EQ(master1.kill_worker(master1.workers[0]), true);
}