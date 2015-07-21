project(sdk_cpp)
cmake_minimum_required(VERSION 2.8)

include(thirdparty/CMakeLists.txt)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})

add_subdirectory(TencentYoutuyun)
add_subdirectory(sample)
