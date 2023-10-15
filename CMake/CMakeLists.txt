# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (CMake_Test)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加 math 子目录
<<<<<<< HEAD
add_subdirectory(./math)
=======
add_subdirectory(math)
>>>>>>> d49a3322628c88fc25a9c2611897d7efd5b75190

# 指定生成目标 
add_executable(demo main.cpp)

# 添加链接库
target_link_libraries(demo MathFunctions)