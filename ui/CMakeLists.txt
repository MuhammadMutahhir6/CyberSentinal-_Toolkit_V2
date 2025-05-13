add_library(uilib
    toolbase.h toolbase.cpp
    bruteforcewidget.h bruteforcewidget.cpp
    cipherwidget.h     cipherwidget.cpp
    passgenwidget.h    passgenwidget.cpp
    strengthwidget.h   strengthwidget.cpp
    aboutdialog.h      aboutdialog.cpp
    loginwidget.h  loginwidget.cpp
    fileeraserwidget.h  fileeraserwidget.cpp
    dictattackwidget.h  dictattackwidget.cpp
    virusscannerwidget.h virusscannerwidget.cpp
    viruscreatorwidget.h viruscreatorwidget.cpp
    logindialog.h
    logindialog.cpp
    logindialog.h       logindialog.cpp

)
target_link_libraries(uilib PRIVATE Qt6::Widgets Qt6::Concurrent corelib)
target_include_directories(uilib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
