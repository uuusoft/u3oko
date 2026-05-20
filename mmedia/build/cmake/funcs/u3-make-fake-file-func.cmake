# author      Erashov Anton erashov2026@proton.me
# date        06.09.2024
# copyright   Erashov A.I.
# file        u3-make-fake-file-func.cmake

function(u3_make_fake_file)
  cmake_parse_arguments(U3_GVXX_MAKE_FAKE_FILE "FORCE_CREATE" "FILE_NAME;CONTENT" "" ${ARGN})

  if(NOT EXISTS "${U3_GVXX_MAKE_FAKE_FILE_FILE_NAME}" OR ${U3_GVXX_MAKE_FAKE_FILE_FORCE_CREATE} EQUAL 1)
    string(TIMESTAMP U3_GVXX_MAKE_FAKE_FILE_CURRENT_TIME)
    file(CONFIGURE OUTPUT ${U3_GVXX_MAKE_FAKE_FILE_FILE_NAME} CONTENT "${U3_SYSTEM_NAME}-${U3_GVXX_MAKE_FAKE_FILE_CURRENT_TIME}-${U3_GVXX_MAKE_FAKE_FILE_CONTENT}")
    message(NOTICE "${U3_MARK_DEV}create fake file ${U3_GVXX_MAKE_FAKE_FILE_FILE_NAME}")
  endif()
endfunction(u3_make_fake_file)
