#set src files
file(GLOB SRC "*.[ch]pp")
file(GLOB HEADERS "*.h")
set(TARGET_NAME sample)
add_executable(${TARGET_NAME} ${SRC} ${HEADERS})
target_link_libraries(${TARGET_NAME}   public
                                        curl ssl crypto
					dl
                                        )
set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++ -Wl,--no-undefined")
