# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        14.10.2024
# copyright   Erashov A.I.
# file        u3-check-git.cmake
# source      https://jonathanhamberg.com/post/cmake-embedding-git-hash/

if(NOT U3_USE_GIT_HASH_FOR_MARK_BUILD)
  return()
endif()

set(U3_LOCAL_FILE_NAME_GIT_STATE "u3-git-state.txt")

# Get the latest abbreviated commit hash of the working branch
execute_process(COMMAND git log -1 --format=%h WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} OUTPUT_VARIABLE U3_GIT_HASH OUTPUT_STRIP_TRAILING_WHITESPACE)

# This command is used to save git commit hash.
file(WRITE ${CMAKE_BINARY_DIR}/${U3_LOCAL_FILE_NAME_GIT_STATE} ${U3_GIT_HASH})

# This following command is used to retreive the git commit hash from the file.
if(EXISTS ${CMAKE_BINARY_DIR}/${U3_LOCAL_FILE_NAME_GIT_STATE})
  file(STRINGS ${CMAKE_BINARY_DIR}/${U3_LOCAL_FILE_NAME_GIT_STATE} U3_LOCAL_CONTENT_FILE)
  list(GET U3_LOCAL_CONTENT_FILE 0 U3_LOCAL_ONE_STRING)
  set(${U3_GIT_HASH} ${U3_LOCAL_ONE_STRING} PARENT_SCOPE)
endif()
