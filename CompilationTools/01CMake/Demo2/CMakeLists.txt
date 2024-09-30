# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.1)

# 项目信息
project(Demo2)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 编译 math 子目录
add_subdirectory(./math)


# 指定生成目标 
add_executable(Demo2 main.cpp)

# 添加链接库
target_link_libraries(Demo2 MathFunctions)