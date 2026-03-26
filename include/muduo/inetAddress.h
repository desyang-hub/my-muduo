#pragma once

#include "muduo/copyable.h"

#include <string>
#include <arpa/inet.h>

namespace muduo
{

class InetAddress : public copyable
{
private:
    int port_;
    sockaddr_in addr_in_;

public:
    explicit InetAddress(int port, const std::string& addr="127.0.0.1");
    explicit InetAddress(const sockaddr_in& addr_in) : addr_in_(addr_in) {}
    ~InetAddress() = default;

    std::string toIp() const;
    uint16_t toPort() const;
    std::string toIpPort() const;
};
    
} // namespace muduo
