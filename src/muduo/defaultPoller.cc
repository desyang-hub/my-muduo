#include "muduo/poller.h"

#include <stdlib.h>

using namespace muduo;

// 这种方式避免了基类定义文件依赖子类依赖
// 基类不要依赖派生类

Poller* Poller::NewDefaultPoller(EventLoop* loop) {
    if (::getenv("MUDUO_USE_POLL")) {
        // TODO:   实现后来进行修改
        return nullptr;
    }
    else {
        // TODO:
        return nullptr;
    }
}