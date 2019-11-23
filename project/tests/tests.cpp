#include <gtest/gtest.h>
#include <fstream>

#include "db_wrapper.h"


TEST(Sort, create_database) {
    DbWrapper wrapper;
    wrapper.execute("ttt");
    std::cout << "Hello";
    EXPECT_EQ(1, 1);
    EXPECT_EQ(2, 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
