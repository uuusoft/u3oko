#!/bin/bash

find mmedia/ -name *.h | xargs clang-format -style=file -i
find mmedia/ -name *.hpp | xargs clang-format -style=file -i
find mmedia/ -name *.cpp | xargs clang-format -style=file -i
find mmedia/ -name *.c | xargs clang-format -style=file -i
