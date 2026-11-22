# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        appl-list-cmake

if (U3_APPL_NAME STREQUAL "u3oko")
  include("${U3_PATH_ROOT}/appls/u3oko/appls-u3oko.cmake")
else ()

  if (U3_COMMERCIAL_PART EQUAL 1)
    if (U3_APPL_NAME STREQUAL "u3iplo")
      include("${U3_PATH_ROOT}/appls/u3iplo/appls-u3iplo.cmake")
    elseif (U3_APPL_NAME STREQUAL "u3yduff")
      include("${U3_PATH_ROOT}/appls/u3yduff/appls-yduff.cmake")
    endif ()
  endif ()

endif ()

if (NOT U3_APPL_CMAKE_FILE_LOAD)
  message(FATAL_ERROR "${U3_MARK_FATAL}Unknown type application U3_APPL_NAME=${U3_APPL_NAME}")
endif ()
