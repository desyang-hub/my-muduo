#include "muduo/poller.h"
#include "muduo/channel.h"

using namespace muduo;

Poller::Poller(EventLoop* loop) : ownerLoop_(loop) {}

bool Poller::hasChannel(Channel* ch) const {
    return channelMap_.find(ch->fd()) != channelMap_.end();
}