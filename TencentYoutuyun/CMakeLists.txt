include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/sign/include")

file(GLOB_RECURSE SRC "*.[ch]pp")
file(GLOB_RECURSE HEADERS "*.h")

add_library(public STATIC ${SRC} ${HEADERS})

set_target_properties(public PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++ -Wl,--no-undefined")
