# author      Erashov Anton erashov2026@proton.me, erashov2021@gmail.com
# date        01.01.2017
# copyright   Erashov A.I.
# file        appl-list-cmake

#message(FATAL_ERROR "U3_APPL_NAME=${U3_APPL_NAME}")
if(${U3_APPL_NAME} STREQUAL "u3oko")
    include("${U3_BUILD_PATH_TO_LIBS}/appls/u3oko/_make/appls-u3oko.cmake")
elseif(${U3_APPL_NAME} STREQUAL "u3iplo")
    include("${U3_BUILD_PATH_TO_LIBS}/appls/u3iplo/_make/appls-u3iplo.cmake")
elseif(${U3_APPL_NAME} STREQUAL "u3yduff")
    include( "${U3_BUILD_PATH_TO_LIBS}/appls/uuu_yduff/appls-yduff.cmake" )
else()
    message(FATAL_ERROR "unknown type application U3_APPL_NAME=${U3_APPL_NAME}")
endif()
