# Cmake 3.17.5 教程
以下内容基于Cmake官网教程，下面是链接:
https://cmake.org/cmake/help/v3.17/guide/tutorial/index.html#adding-usage-requirements-for-library-step-3

## Step 1 基本结构，指定C++版本，传入CmakeLists.txt相关参数给.cc源文件
最基本的项目是从源代码文件构建的可执行文件。 对于简单项目，CMakeLists.txt文件中只需要如下三行代码。  
### Step1/CMakeLists.txt
    cmake_minimum_required(VERSION 3.17)

    # 设置项目名称, 可指定项目版本(可选)
    project(Step1)
    
    # 从c++源文件中添加可执行文件，命名为step1，源文件为step1.cpp
    add_executable(step1 step1.cpp)
### Step1/src/step1.cc

    #include <iostream>
    using namespace std;
    
    int main()
    {
        std::cout<<"Hello Cmake!"<<std::endl;
        return 0;
    }
这样就可以在 Step1 目录下进行编译运行了。
可以在上述基础添加 项目版本号(可选) 和 通过配置头文件传入Cmake相关参数到cpp文件中使用
### Step1/config/step1_config.h.in
    // Step1 项目的配置文件
    // @Tutorial_VERSION_MAJOR@ 和 @Tutorial_VERSION_MINOR@ 会替换成CMakeLists.txt中的值
    # define Step1_VERSION_MAJOR @Step1_VERSION_MAJOR@
    # define Step1_VERSION_MINOR @Step1_VERSION_MINOR@
### Step1/CMakeLists.txt
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
### Step1/src/step1.cc
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

## Step 2 添加库文件,让添加的库文件是可选的(大型项目会很常见)
### Step2/MathFunctions
自定义一个自己的库 MathFunctions ，内容如下
#### Step2/MathFunction/MathFunction.h (省略预处理命令)

    float mySqrt(float number);
    
#### Step2/MathFunction/mySqrt.cc

    #include "MathFunction.h"
    float mySqrt(float number) {
    //来自维基百科
    //number 必须是 IEEE 754标准格式的32位浮点数
    long i;
    float x2, y;
    const float threehalfs = 1.5F;
    
        x2 = number * 0.5F;
        y = number;
        i = *(long *) &y;                       // evil floating point bit level hacking（对浮点数的邪恶位元hack）
        i = 0x5f3759df - (i >> 1);               // what the fuck?（这他妈的是怎么回事？）
        y = *(float *) &i;
        y = y * (threehalfs - (x2 * y * y));   // 1st iteration （第一次迭代）
        y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed（第二次迭代，可以删除）
    
        return 1.0f / y;    //返回的 是 平方根
    }

#### Step2/MathFunction/CMakeLists.txt

    add_library(MathFunctions mySqrt.cc)

上述三个文件构成了一个新的库，可以通过add_subdirectory()来添加到项目中

#### Step2/src/step2.cc

    #include <iostream>
    #include <cmath>
    using namespace std;
    int main(int argc, char *argv[])
    {
    
        #ifdef USE_MYMATH
            float outputValue = mySqrt(100.0f)
        #else
            float outputValue = sqrt(100.f);
        #endif
    
        std::cout<<"Sqrt:"<<fixed<<outputValue<<std::endl;
        return 0;
    }
#### Step2/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

    # 指定C++版本, CMAKE_CXX_STANDARD_REQUIRED确保使用的是指定的C++标准
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
    
    project(Step2)
    
    add_executable(step2 src/step2.cc)
    
    add_subdirectory(MathFunctions)
    target_link_libraries(step2 PUBLIC MathFunctions)
    target_include_directories(
    step2 PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}"
    )
如果要通过变量控制是否使用该库，可以通过option()来实现，这对于大型项目来说是非常有必要的
