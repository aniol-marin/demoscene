set(CMAKE_SYSTEM_NAME "Windows")
set(CMAKE_SYSTEM_PROCESSOR "x86_64")

#[[ real target
set(__prefix "x86_64-w64-mingw32")
]]#

#[[ mock target ]]#
set(__install_path "/usr/")
set(__prefix "x86_64-pc-linux-gnu")
set(__version "-11")
#
set(CMAKE_C_COMPILER "${__install_path}/bin/${__prefix}-gcc${__version}")
set(CMAKE_CXX_COMPILER "${__install_path}/bin/${__prefix}-g++${__version}")
set(CMAKE_RC_COMPILER "${__install_path}/bin/${__prefix}-windres${__version}")
#
set(CMAKE_FIND_ROOT_PATH "/usr/${__prefix}/sys-root/mingw/")
#
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
# execution emulation
set(CMAKE_CROSSCOMPILING_EMULATOR "/usr/local/bin/wine64")
