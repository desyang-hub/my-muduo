cmake_minimum_required(VERSION 3.15)

project(mymoduo)

# so save path
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# set compoile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14")

# SOURCE CODE
set(SOURCE_CODE
    src/muduo/logger.cc
    src/muduo/inetAddress.cc
)

# include dir
include_directories(${PROJECT_SOURCE_DIR}/include)

# generate lib
add_library(mymuduo SHARED ${SOURCE_CODE})

add_executable(main
    src/main.cc
)

# link library mymoduo
target_link_libraries(main mymuduo)


# ==========================================
# 3. 【关键】添加 install 规则
# ==========================================

# --- 安装可执行文件 ---
# 将 'main' 安装到 ${CMAKE_INSTALL_PREFIX}/bin
install(TARGETS main 
        RUNTIME DESTINATION bin)

# --- 安装库文件 ---
# 将 'mymuduo' 安装到 ${CMAKE_INSTALL_PREFIX}/lib
# LIBRARY 对应 .so (Linux), ARCHIVE 对应 .a, RUNTIME 对应 .dll (Windows)
install(TARGETS mymuduo
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

# --- 安装头文件 ---
# 将 include 目录下的文件安装到 ${CMAKE_INSTALL_PREFIX}/include/mylib
# 注意：这里通常保留目录结构，方便用户 #include <mylib/header.h>
install(DIRECTORY include/muduo 
    DESTINATION include)


if(NOT TARGET uninstall)
    add_custom_target(uninstall
        COMMAND sh -c "cat install_manifest.txt | xargs sudo rm -v && sudo ldconfig"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Uninstalling files and refreshing ldconfig..."
        VERBATIM
    )
endif()