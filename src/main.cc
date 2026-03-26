#include "muduo/logger.h"
#include "muduo/inetAddress.h"
#include "muduo/channel.h"
#include "muduo/blockedQueue.h"

#include <iostream>

int main() {

    // LOG_INFO("print message to log");

    muduo::InetAddress addr(8080);

    LOG_INFO("ip addr: %s", addr.toIpPort().data());

    for (int i = 0; i < 10; ++i) {
        LOG_INFO("info %d", i);
    }
    return 0;
}