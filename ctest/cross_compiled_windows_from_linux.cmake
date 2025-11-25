set(CMAKE_SYSTEM_NAME "Windows")
set(CMAKE_SYSTEM_PROCESSOR "x86_64")

set(__prefix "x86_64-w64-mingw32")
#
set(CMAKE_C_COMPILER "/usr/local/bin/${__prefix}-gcc")
set(CMAKE_CXX_COMPILER "/usr/local/bin/${__prefix}-g++")
set(CMAKE_RC_COMPILER "/usr/local/bin/${__prefix}-windres")
#
set(CMAKE_FIND_ROOT_PATH "/usr/${__prefix}/sys-root/mingw/")
#
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
# execution emulation
set(CMAKE_CROSSCOMPILING_EMULATOR "/usr/local/bin/wine64")
