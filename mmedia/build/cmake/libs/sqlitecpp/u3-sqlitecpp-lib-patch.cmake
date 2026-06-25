# author      Erashov Anton erashov2026@proton.me
# date        06.03.2026
# copyright   Erashov A.I.
# file        u3-sqlitecpp-lib-patch.cmake

cmake_minimum_required(VERSION 3.29.0)

project(u3-sqlitecpp)

file(TO_CMAKE_PATH "." dir-u3-sqlitecpp-lib)
set(files-u3-sqlitecpp-lib "${dir-u3-sqlitecpp-lib}/sqlite3.c")
add_library(u3-sqlitecpp-lib STATIC ${files-u3-sqlitecpp-lib})

target_compile_definitions(u3-sqlitecpp-lib PUBLIC -DBIONIC_IOCTL_NO_SIGNEDNESS_OVERLOAD=1)
