# author      Erashov Anton erashov2026@proton.me
# date        12.09.2024
# copyright   Erashov A.I.
# file        u3-selector-os-specific-options.cmake

if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
  include("./build/cmake/os-specific/u3-android-specific.cmake")
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
if(DEFINED U3_PREFIX_LIB_NAME AND DEFINED U3_SUFFIX_LIB_NAME AND DEFINED U3_SUFFIX_DLL_NAME)

else()
  message(NOTICE "U3_PREFIX_LIB_NAME=${U3_PREFIX_LIB_NAME}")
  message(NOTICE "U3_SUFFIX_LIB_NAME=${U3_SUFFIX_LIB_NAME}")
  message(NOTICE "U3_SUFFIX_DLL_NAME=${U3_SUFFIX_DLL_NAME}")
  message(FATAL_ERROR "required platform dependent variables are not set")
endif()
