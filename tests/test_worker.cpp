#include <gtest/gtest.h>
#include <cstddef>
#include <iostream>
extern "C" {
#include "../project/server.h"
}


TEST(NULL,check__deadline)
{
    worker_pid=1;
    worker_timeout=1;
    status=0
    HTTP_worker worker1=new HTTP_worker(worker_pid,worker_timeout,status);
    worker1.start_work();
    worker1.status='200';
    EXPECT_EQ(worker1.check_deadline(),1);
    worker1.start_work();
    sleep(10);
    EXPECT_EQ(worker1.check_deadline(),0);
}
TEST(NULL,check__send_bad_response)
{
    worker_pid=1;
    worker_timeout=1;
    status=0
    HTTP_worker worker1=new HTTP_worker(worker_pid,worker_timeout,status);
    worker1.start_work();
    worker1.request='?qawszdtfr54edfd2h';
    worker1.read_request();
    EXPECT_EQ(worker1.status,400);
}

TEST(NULL,check__send_bad_response)
{
    worker_pid=1;
    worker_timeout=1;
    status=0
    HTTP_worker worker1=new HTTP_worker(worker_pid,worker_timeout,status);
    worker1.start_work();
    worker1.request='?1=1';
    worker1.read_request();
    EXPECT_EQ(worker1.status,200);
}
