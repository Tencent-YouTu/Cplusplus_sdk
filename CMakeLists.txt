project(sdk_cpp)
cmake_minimum_required(VERSION 2.8)

macro(add_thirdparty_library DIR LIBNAME)
    include_directories(${DIR}/include)
    add_library(${LIBNAME} STATIC IMPORTED)
        set_property(TARGET ${LIBNAME} PROPERTY
                IMPORTED_LOCATION ${DIR}/lib/lib${LIBNAME}.a)
    message("add lib: ${LIBNAME}")
endmacro(add_thirdparty_library)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -g3  -fPIC -Wall -Wextra -Wno-unused-variable -Wno-unused-local-typedefs -Wno-unused-parameter -rdynamic -fpermissive -std=c++11 ")

#set gflags 
add_thirdparty_library(${CMAKE_CURRENT_SOURCE_DIR}/gflags gflags)

#set curl
add_thirdparty_library(${CMAKE_CURRENT_SOURCE_DIR}/curl curl)

#set openssl 
add_thirdparty_library(${CMAKE_CURRENT_SOURCE_DIR}/openssl ssl)
add_thirdparty_library(${CMAKE_CURRENT_SOURCE_DIR}/openssl crypto)

#set src files
include_directories(sign/include)
file(GLOB_RECURSE SRC "*.[ch]pp")
file(GLOB_RECURSE HEADERS "*.h")

add_executable(${PROJECT_NAME} ${SRC} ${HEADERS})
target_link_libraries(${PROJECT_NAME} gflags curl ssl crypto
                                        rt m  dl
                                        bz2
                                        z
                                        )
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++ -Wl,--no-undefined")
