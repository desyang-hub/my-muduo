# 定义测试可执行文件
# 注意：这里不需要写 ../src/... 如果路径复杂，建议使用绝对路径或目标依赖
add_executable(run_tests test.cc)

# 链接库
# GTest::gtest_main 是由父目录的 FetchContent 提供的
target_link_libraries(run_tests 
    GTest::gtest_main 
    pthread
    # 如果有内部库，可以链接：$<TARGET_OBJECTS:my_lib_obj>
)

# 注册测试
include(GoogleTest)
gtest_discover_tests(run_tests)