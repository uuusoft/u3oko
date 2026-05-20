# author      Erashov Anton erashov2004@yandex.ru
# date        06.05.2026
# copyright   Erashov A.I.
# file        readme.md

dependencies
all:
+ perl    https://strawberryperl.com/
+ git 
+ wget
+ python  https://www.python.org/
+ nasm    https://www.nasm.us/
+ clang      

windows:
+ msys2   https://www.msys2.org/ 
+ cygwin  https://www.cygwin.com/install.html

orangepi:
android:
linux:
raspberrypi:
    #sudo apt-get update
    #sudo apt-get install autoconf automake libtool
    #sudo apt-get update && sudo apt-get install pkg-config
+ meson
+ autoconf 
+ automake 
+ libtool
+ pkg-config
