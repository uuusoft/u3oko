# author      Erashov Anton erashov2026@proton.me
# date        12.09.2024
# copyright   Erashov A.I.
# file        u3-is-target-os-linux-func.cmake

function(u3_is_target_os_linux)
  unset(U3_FUNCT_RESULT PARENT_SCOPE)
  cmake_parse_arguments(U3_GVXX_IS_TARGET_OS_LINUX "" "OS_TYPE" "" ${ARGN})

  set(U3_INTERNAL_LINUX_OS_LIST "Linux" "Ubuntu" "Raspberry" "OrangePi" "Debian")
  if(NOT ${U3_GVXX_IS_TARGET_OS_LINUX_OS_TYPE} IN_LIST U3_INTERNAL_LINUX_OS_LIST)
    set(U3_FUNCT_RESULT TRUE PARENT_SCOPE)
  endif()  
endfunction(u3_is_target_os_linux)
