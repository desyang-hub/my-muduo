/**
 * @FilePath     : /gtest_demo/include/muduo/logger.h
 * @Description  :  
 * @Author       : desyang
 * @Date         : 2026-03-25 20:05:54
 * @LastEditors  : desyang
 * @LastEditTime : 2026-03-25 20:46:26
**/
#pragma once

#include "muduo/nonecopyable.h"
#include "muduo/blockedQueue.h"

#include <string>
#include <memory>
#include <atomic>
#include <fstream>
#include <thread>

// 开启异步日志写入
#define ENABLE_ASYNC_LOGING() \
    muduo::Logger::GetInstanse().enable_async_log_write()

#define LOG_INFO(format, ...) \
    if (muduo::Logger::GetInstanse().getLevel() >= muduo::INFO) {                                    \
        char buf[1024];                     \
        snprintf(buf, 1024, format, ##__VA_ARGS__);\
        muduo::Logger::GetInstanse().log(buf, muduo::INFO);     \
    };                             \


#define LOG_ERROR(format, ...) \
if (muduo::Logger::GetInstanse().getLevel() >= muduo::ERROR) {                                    \
        char buf[1024];                     \
        snprintf(buf, 1024, format, ##__VA_ARGS__);\
        muduo::Logger::GetInstanse().log(buf, muduo::ERROR);     \
    }; 

#define LOG_FATAL(format, ...) \
if (muduo::Logger::GetInstanse().getLevel() >= muduo::FATAL) {                                    \
        char buf[1024];                     \
        snprintf(buf, 1024, format, ##__VA_ARGS__);\
        muduo::Logger::GetInstanse().log(buf, muduo::FATAL);     \
    }; 


// 为了避免debug输出太多信息
#define LOG_DEBUG(format, ...) \
if (muduo::Logger::GetInstanse().getLevel() >= muduo::DEBUG) {                                    \
        char buf[1024];                     \
        snprintf(buf, 1024, format, ##__VA_ARGS__);\
        muduo::Logger::GetInstanse().log(buf, muduo::DEBUG);     \
    }; 
// 定义日志级别
namespace muduo
{
enum LoggerLevel {
    INFO,
    ERROR,
    FATAL,
    DEBUG
};

// 一个日志类
class Logger : public nonecopyable {
private:
    Logger();
    
    int log_level_;
    bool is_async_{false};
    std::unique_ptr<BlockedQueue<std::string>> blocked_que_;
    std::thread async_log_write_thread_;
    FILE* log_file_;

    void async_log_write();
    
public:
    ~Logger();

    static Logger& GetInstanse();

    // 开启异步线程
    void enable_async_log_write();
    Logger& setLevel(int level);
    int getLevel() const;

    void log(const std::string&, int log_level);
};


    
} // namespace muduo