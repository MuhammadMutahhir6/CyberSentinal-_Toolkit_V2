add_library(corelib
    bruteforce.h bruteforce.cpp
    xorcipher.h  xorcipher.cpp
    passwordutils.h passwordutils.cpp
)
target_include_directories(corelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
