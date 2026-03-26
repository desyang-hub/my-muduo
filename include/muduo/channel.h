#pragma once

#include "muduo/nonecopyable.h"

#include <functional>
#include <memory>

namespace muduo
{

class EventLoop;

// 封装感兴趣的fd和event, epollIN epollOUT时间
/// 还有poller返回的事件
class Channel : public nonecopyable
{
private:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void()>;
public:
    Channel(EventLoop* loop, int fd);
    ~Channel();

    void handleEvent();

    void setReadEventCallback(ReadEventCallback cb) {
        readEventCallback_ = std::move(cb);
    }

    void setWriteEventCallback(ReadEventCallback cb) {
        writeEventCallback_ = std::move(cb);
    }


    void setCloseEventCallback(ReadEventCallback cb) {
        closeEventCallback_ = std::move(cb);
    }

    void setErrorEventCallback(ReadEventCallback cb) {
        errorEventCallback_ = std::move(cb);
    }

    // 防止channel被手动析构后，还在回调函数
    void tie(const std::shared_ptr<void>&);

    int fd() const {
        return fd_;
    }

    int events() const {
        return events_;
    }

    void setREvents(int revents) {
        revents_ = revents;
    }

    void update() {

    }

    void enableReading() {
        events_ |= kReadEvent;
        update();
    }

    void disableReading() {
        events_ &= ~kReadEvent;
        update();
    }

    void enableWriting() {
        events_ |= kWriteEvent;
        update();
    }

    void disableWriting() {
        events_ &= ~kWriteEvent;
        update();
    }

    void disableAll() {
        events_ = kNoneEvent;
        update();
    }

    bool isNoneEvent() const {
        return events_ == kNoneEvent;
    }

    bool isReading() const {
        return events_ & kReadEvent;
    }

    bool isWriting() const {
        return events_ & kWriteEvent;
    }

    int index() const {
        return index_;
    }

    void set_index(int index) {
        index_ = index;
    }

private:
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop* loop_;
    int fd_;
    int events_; // 感兴趣事件
    int revents_; // 具体发生的事件
    int index_;

    std::weak_ptr<void> tie_;
    bool tied_;

    // 因为channel能够从epoll获取发生的事件revents, 从而调用对应的事件回调函数
    ReadEventCallback readEventCallback_;
    EventCallback writeEventCallback_;
    EventCallback closeEventCallback_;
    EventCallback errorEventCallback_;
};

    
} // namespace muduo
