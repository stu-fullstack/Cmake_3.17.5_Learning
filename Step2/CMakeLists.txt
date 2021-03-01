cmake_minimum_required(VERSION 3.16)

# 指定C++版本, CMAKE_CXX_STANDARD_REQUIRED确保使用的是指定的C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Step2)

if(USE_MYMATH)
    add_subdirectory(MathFunctions)
    list(APPEND EXTRA_LIBS MathFunctions)
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
endif()

add_executable(step2 src/step2.cc)

option(USE_MYMATH "Use Step2 provided math implementation" ON)
configure_file(config/step2_config.h.in step2_config.h)

target_link_libraries(step2 PUBLIC ${EXTRA_LIBS})
target_include_directories(
        step2 PUBLIC
        "${PROJECT_BINARY_DIR}"
        ${EXTRA_INCLUDES}
)