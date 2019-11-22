#include <gtest/gtest.h>
#include <cstddef>
#include <iostream>

extern "C" {
#include "server.h"
}

TEST(NULL, work) {
    HTTP_worker worker;
    EXPECT_EQ(worker.start_work(), true);
}