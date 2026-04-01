#include "muduo/logger.h"
#include "muduo/inetAddress.h"
#include "muduo/channel.h"
#include "muduo/blockedQueue.h"
#include "muduo/timeStamp.h"

#include <iostream>

int main() {

    ENABLE_ASYNC_LOGING();
    std::cout << "TimeNow: " << muduo::TimeStamp::Now().toString() << std::endl;

    // LOG_INFO("print message to log");

    muduo::Logger::GetInstanse().setLevel(muduo::FATAL);

    LOG_ERROR("error");
    LOG_FATAL("fatal");
    LOG_DEBUG("debug");

    muduo::InetAddress addr(8080);

    LOG_INFO("ip addr: %s", addr.toIpPort().data());

    for (int i = 0; i < 10; ++i) {
        LOG_INFO("info %d", i);
    }
    return 0;
}