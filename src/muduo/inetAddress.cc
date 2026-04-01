#include "muduo/inetAddress.h"

#include <strings.h>
#include <string.h>

using namespace muduo;


InetAddress::InetAddress(int port, const std::string& addr) {
    bzero(&addr_in_, sizeof(addr_in_));
    addr_in_.sin_family = AF_INET;
    addr_in_.sin_port = htons(port);
    addr_in_.sin_addr.s_addr = inet_addr(addr.data());
}

std::string InetAddress::toIp() const {
    char buf[64];
    ::inet_ntop(AF_INET, &addr_in_.sin_addr.s_addr, buf, sizeof(buf));

    return std::string(buf);
}

uint16_t InetAddress::toPort() const {
    // ip:port
    return ntohs(addr_in_.sin_port);
}
std::string InetAddress::toIpPort() const {
    char buf[64];
    ::inet_ntop(AF_INET, &addr_in_.sin_addr.s_addr, buf, sizeof(buf));

    uint16_t port = ntohs(addr_in_.sin_port);

    snprintf(buf + strlen(buf), 64, ":%u", port);
    
    return buf;
}