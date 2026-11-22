# author      Erashov Anton erashov2026@proton.me
# date        03.04.2026
# copyright   Erashov A.I.
# file        orangepi-arm64-gcc.cmake

# sudo apt install crossbuild-essential-arm64

set(U3_PLATFORM_NAME OrangePi)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(U3_SYSTEM_PROCESSOR_ARCH arm64)
set(ARM64 1)

set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
set(CMAKE_ASM_COMPILER aarch64-linux-gnu-gcc)
set(U3_CXX_COMPILER_ARCH gcc)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

#set(CMAKE_INSTALL_INCLUDEDIR /usr/aarch64-linux-gnu/include)
#set(CMAKE_INSTALL_LIBDIR /usr/aarch64-linux-gnu/lib)
#set(CMAKE_FIND_ROOT_PATH /usr/aarch64-linux-gnu)
#set(CMAKE_INSTALL_LIBDIR /lib/aarch64-linux-gnu)

#CMAKE_INSTALL_BINDIR	bin	User executables and Windows .dll runtime files.
#CMAKE_INSTALL_LIBDIR	lib or lib64	Object code libraries (.so, .a, .dylib, .lib).
#CMAKE_INSTALL_INCLUDEDIR	include	C and C++ header files.
#CMAKE_INSTALL_DATAROOTDIR	share	Root for read-only architecture-independent data.
#CMAKE_INSTALL_DATADIR	share (DATAROOTDIR)	Read-only architecture-independent data files.
#CMAKE_INSTALL_SYSCONFDIR	etc	Read-only single-machine configuration files.
#CMAKE_INSTALL_DOCDIR	share/doc/<PROJECT_NAME>	Documentation files.
#CMAKE_INSTALL_MANDIR	share/man	Manual pages.
#CMAKE_INSTALL_LIBEXECDIR	libexec
