# author      Erashov Anton erashov2026@proton.me
# date        12.09.2024
# copyright   Erashov A.I.
# file        u3-selector-os-specific-options.cmake

#message(FATAL_ERROR "U3_SYSTEM_NAME=${U3_SYSTEM_NAME}")

if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
  if(U3_COMMERCIAL_PART EQUAL 1)
    include("./build/cmake/os-specific/u3-android-specific.cmake")
  endif()
elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_LINUX})
  include("./build/cmake/os-specific/u3-linux-specific.cmake")
elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
  include("./build/cmake/os-specific/u3-windows-specific.cmake")
elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_RASPBERRY})
  include("./build/cmake/os-specific/u3-raspberry-specific.cmake")
elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ORANGE_PI})
  include("./build/cmake/os-specific/u3-orangepi-specific.cmake")
elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_DARWIN})
  include("./build/cmake/os-specific/u3-darwin-specific.cmake")
else()
  message(FATAL_ERROR "unknown OS U3_SYSTEM_NAME=${U3_SYSTEM_NAME}")
endif()

# postconditions
if(NOT (DEFINED U3_PREFIX_LIB_NAME AND DEFINED U3_SUFFIX_LIB_NAME AND DEFINED U3_SUFFIX_DLL_NAME))
  message(NOTICE "${U3_MARK_REQUARED} U3_PREFIX_LIB_NAME=${U3_PREFIX_LIB_NAME}")
  message(NOTICE "${U3_MARK_REQUARED} U3_SUFFIX_LIB_NAME=${U3_SUFFIX_LIB_NAME}")
  message(NOTICE "${U3_MARK_REQUARED} U3_SUFFIX_DLL_NAME=${U3_SUFFIX_DLL_NAME}")
  message(FATAL_ERROR "${U3_MARK_REQUARED} dependent variables are not set")
endif()
