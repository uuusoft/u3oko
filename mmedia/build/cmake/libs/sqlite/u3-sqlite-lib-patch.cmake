# author      Erashov Anton erashov2026@proton.me
# date        06.09.2024
# copyright   Erashov A.I.
# file        u3-sqlite-lib-patch.cmake

cmake_minimum_required(VERSION 3.29.0)

project(u3-sqlite)

file(TO_CMAKE_PATH "." dir-u3-sqlite-lib)
set(files-u3-sqlite-lib "${dir-u3-sqlite-lib}/sqlite3.c")
add_library(u3-sqlite-lib STATIC ${files-u3-sqlite-lib})

target_compile_definitions(u3-sqlite-lib PUBLIC -DBIONIC_IOCTL_NO_SIGNEDNESS_OVERLOAD=1)
