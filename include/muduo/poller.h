#pragma once

#include "muduo/nonecopyable.h"
#include "muduo/timeStamp.h"

#include <vector>
#include <unordered_map>

namespace muduo
{

class Channel;
class EventLoop;

class Poller : public nonecopyable
{
public:
    using ChannelList = std::vector<Channel*>;

    Poller(EventLoop* loop);
    virtual ~Poller() = default;

    virtual TimeStamp poll(int timeoutMs, Channel* activateChannel) = 0;
    virtual void updateChannel(Channel* ch) = 0;
    virtual void removeChannel(Channel* ch) = 0;

    bool hasChannel(Channel*) const;

    // 可以通过该接口获取Poller的具体实现
    static Poller* NewDefaultPoller(EventLoop* loop);
protected:
    // key socket fd, value Channel*
    using ChannelMap = std::unordered_map<int, Channel*>;

private:
    EventLoop* ownerLoop_;
    ChannelMap channelMap_;
};
    
} // namespace muduo
