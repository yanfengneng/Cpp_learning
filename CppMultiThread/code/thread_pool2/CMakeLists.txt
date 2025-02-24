cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(thread_pool2)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置源文件
set(SOURCES main.cpp)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 链接 pthread 库
target_link_libraries(${PROJECT_NAME} pthread)