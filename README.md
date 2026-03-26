# MyMuduo - 轻量级网络库学习项目

## 项目简介

MyMuduo 是一个基于 C++14 开发的轻量级网络库学习项目，灵感来源于陈硕的 Muduo 网络库。本项目旨在通过实现一个高性能、非阻塞的 TCP 网络库，深入学习和理解现代 C++ 网络编程的核心概念和实现技术。

## 核心特性

- **异步日志系统**：支持多级别日志输出（INFO、ERROR、FATAL、DEBUG），支持异步日志写入
- **事件驱动模型**：基于 Reactor 模式，使用 Channel 封装文件描述符和事件
- **阻塞队列**：线程安全的阻塞队列实现，用于生产者-消费者模型
- **网络地址封装**：对 sockaddr_in 进行面向对象封装，简化网络地址操作
- **非拷贝设计**：关键类采用不可拷贝设计，确保资源安全

## 项目结构

```
moduo_demo/
├── CMakeLists.txt          # CMake 构建配置
├── include/muduo/          # 头文件目录
│   ├── blockedQueue.h      # 阻塞队列模板类
│   ├── channel.h           # 事件通道封装
│   ├── copyable.h          # 可拷贝基类
│   ├── eventLoop.h         # 事件循环（待实现）
│   ├── inetAddress.h       # 网络地址封装
│   ├── logger.h            # 日志系统
│   ├── nonecopyable.h      # 不可拷贝基类
│   └── tcpServer.h         # TCP 服务器（待实现）
├── src/                    # 源文件目录
│   ├── main.cc            # 主程序示例
│   └── muduo/             # 实现文件
├── demo/                  # 示例程序
│   ├── main.cpp           # 简单示例
│   └── Makefile           # 示例构建配置
└── lib/                   # 编译生成的库文件目录
```

## 核心组件

### 1. Logger（日志系统）
- 单例模式实现
- 支持多级别日志：INFO、ERROR、FATAL、DEBUG
- 支持异步日志写入（通过定义 `ENABLE_ASYNC_LOGGING` 启用）
- 使用阻塞队列实现异步日志缓冲

### 2. BlockedQueue（阻塞队列）
- 模板类实现，支持任意类型
- 线程安全设计，使用互斥锁和条件变量
- 支持优雅关闭机制

### 3. Channel（事件通道）
- 封装文件描述符和感兴趣的事件（读、写、关闭、错误）
- 支持设置各类事件回调函数
- 提供事件状态的查询和修改接口

### 4. InetAddress（网络地址）
- 封装 sockaddr_in 结构体
- 提供 IP 地址、端口的便捷转换接口
- 支持默认地址（127.0.0.1）

### 5. EventLoop（事件循环）
- 目前为框架类，待进一步实现
- 计划实现基于 epoll 的事件循环机制

## 编译与运行

### 环境要求
- CMake >= 3.15
- C++14 或更高版本的编译器（GCC/Clang）
- Linux 操作系统

### 编译步骤

```bash
# 1. 创建构建目录
mkdir build && cd build

# 2. 运行 CMake 配置
cmake ..

# 3. 编译
make

# 4. 运行示例程序
./main
```

### 安装

```bash
# 安装到系统目录（默认为 /usr/local）
sudo make install

# 卸载
sudo make uninstall
```

## 使用示例

### 日志使用

```cpp
#include "muduo/logger.h"

int main() {
    // 基本日志输出
    LOG_INFO("This is an info message");
    LOG_ERROR("Error occurred: %s", "file not found");

    // 地址信息日志
    muduo::InetAddress addr(8080);
    LOG_INFO("Server address: %s", addr.toIpPort().data());

    return 0;
}
```

### 网络地址使用

```cpp
#include "muduo/inetAddress.h"
#include <iostream>

int main() {
    // 创建地址对象
    muduo::InetAddress addr(8080);

    // 获取地址信息
    std::cout << "IP:Port: " << addr.toIpPort() << std::endl;
    std::cout << "IP: " << addr.toIp() << std::endl;
    std::cout << "Port: " << addr.toPort() << std::endl;

    return 0;
}
```

## 学习目标

本项目主要用于学习和实践以下技术：

1. **现代 C++ 编程**：智能指针、移动语义、lambda 表达式等
2. **网络编程**：TCP/IP 协议、socket 编程、非阻塞 I/O
3. **并发编程**：多线程、互斥锁、条件变量、线程安全队列
4. **设计模式**：单例模式、Reactor 模式、观察者模式
5. **系统编程**：epoll、文件描述符、事件驱动模型

## 开发进度

- [x] 基础框架搭建
- [x] 日志系统实现
- [x] 阻塞队列实现
- [x] 网络地址封装
- [x] Channel 基本框架
- [ ] EventLoop 完整实现
- [ ] Poller（epoll 封装）实现
- [ ] TcpServer 实现
- [ ] TcpConnection 实现
- [ ] Buffer 实现

## 注意事项

1. 本项目为学习项目，不建议用于生产环境
2. 部分功能仍在开发中，API 可能发生变化
3. 代码中包含详细注释，方便学习理解

## 参考资料

- 陈硕《Linux 多线程服务端编程》
- Muduo 网络库源码：https://github.com/chenshuo/muduo
- Linux epoll 文档

## 许可证

本项目仅供学习交流使用。

## 作者

desyang

## 更新日志

- 2026-03-25: 项目初始化，实现基础日志系统和网络地址封装
