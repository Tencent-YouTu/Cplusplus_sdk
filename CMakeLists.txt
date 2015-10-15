project(sdk_cpp)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -g3  -fPIC -Wall -Wextra -Wno-unused-variable -Wno-unused-local-typedefs -Wno-unused-parameter -rdynamic -fpermissive")

include(thirdparty/CMakeLists.txt)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})

add_subdirectory(TencentYoutuyun)
add_subdirectory(sample)
