set(THIRD_PATH ${CMAKE_SOURCE_DIR}/thirdparty)

macro(add_thirdparty_library DIR LIBNAME)
    include_directories(${DIR}/include)
    add_library(${LIBNAME} STATIC IMPORTED)
        set_property(TARGET ${LIBNAME} PROPERTY
                IMPORTED_LOCATION ${DIR}/lib/lib${LIBNAME}.a)
    message("add lib: ${LIBNAME}")
endmacro(add_thirdparty_library)

#set curl
add_thirdparty_library(${THIRD_PATH}/curl curl)

#set openssl 
add_thirdparty_library(${THIRD_PATH}/openssl ssl)
add_thirdparty_library(${THIRD_PATH}/openssl crypto)
