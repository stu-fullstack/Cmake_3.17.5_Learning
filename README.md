# Cmake教程
以下描述基于Cmake官网教程，下面是链接:
https://cmake.org/cmake/help/v3.17/guide/tutorial/index.html#adding-usage-requirements-for-library-step-3
## Step 1
最基本的项目是从源代码文件构建的可执行文件。 对于简单项目，CMakeLists.txt文件中只需要如下三行代码。  
### CMakeLists.txt
    cmake_minimum_required(VERSION 3.17)

    # 设置项目名称, 可指定项目版本(可选)
    project(Step1)
    
    # 从c++源文件中添加可执行文件，命名为step1，源文件为step1.cpp
    add_executable(step1 step1.cpp)
### step1.cc

    #include <iostream>
    using namespace std;
    
    int main()
    {
        std::cout<<"Hello Cmake!"<<std::endl;
        return 0;
    }
这样就可以在 Step1 目录下进行编译运行了。
可以在上述基础添加 项目版本号(可选) 和 通过配置头文件传入Cmake相关参数到cpp文件中使用
### step1_config.h.in
    // Step1 项目的配置文件
    // @Tutorial_VERSION_MAJOR@ 和 @Tutorial_VERSION_MINOR@ 会替换成CMakeLists.txt中的值
    # define Step1_VERSION_MAJOR @Step1_VERSION_MAJOR@
    # define Step1_VERSION_MINOR @Step1_VERSION_MINOR@
### CMakeLists.txt
    cmake_minimum_required(VERSION 3.17)

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
    add_executable(step1 src/step1.cpp)
### step1.cc
    #include <iostream>
    #include "step1_config.h"
    using namespace std;
    int main(int argc, char *argv[])
    {
        if (argc < 2) {
        // report version
        std::cout << argv[0] << " Version " << Step1_VERSION_MAJOR << "."
        << Step1_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
        }
        return 0;
    }
### 指定 C++ 版本
    # 指定C++版本, CMAKE_CXX_STANDARD_REQUIRED确保使用的是C++标准
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
### build 然后 测试
按照如下步骤

    cd {project_root}/Step1
    mkdir build
    cd build
    cmake ..
    cmake --build .
然后运行生成的可执行文件，可以得到如下结果

    huiyan@huiyan:~/CLionProjects/Cmake_3.17.5_Learning/Step1/build$ ./step1
    ./step1 Version 1.2
    Usage: ./step1 number
