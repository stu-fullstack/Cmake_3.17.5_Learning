cmake_minimum_required(VERSION 3.16)

# 指定C++版本, CMAKE_CXX_STANDARD_REQUIRED确保使用的是C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# 设置项目名称, 可指定项目版本(可选), 下面两种方式设置版本号都可
project(Step1 VERSION 1.2)
# set(Step1_VERSION_MAJOR 1)
# set(Step1_VERSION_MINOR 2)

# 将项目的版本号传给 step1.cpp 中调用(传递Cmake的相关信息给源文件调用)
# 第一个参数是输入的头文件
# 第二个参数是输出的头文件名称，之后cpp文件中可以通过这个名称来 include : #include "step1_config.h"
configure_file(config/step1_config.h.in step1_config.h)

# 添加自定义的头文件路径,将指定目录添加到编译器的头文件搜索路径之下
include_directories(
        "${PROJECT_BINARY_DIR}"
        include/
)

# 从c++源文件中添加可执行文件，命名为step1，源文件为step1.cpp
add_executable(step1 src/step1.cc)

# 添加的头文件会被写进二进制树，必须添加搜索路径让系统能够找到
# 第一个参数可以是 add_executable() 或者 add_library() 创建的目标，因此要在add_executable之后
# 第二个参数指定作用范围
# 第三个参数指定路径
target_include_directories(step1 PUBLIC "${PROJECT_BINARY_DIR}")