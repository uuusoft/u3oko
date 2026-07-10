# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        libs-utility.cmake

u3_add_target_lib(TARGET_NAME utility-lib SOURCE_PATH ${U3_PATH_ROOT}/libs/utility)

target_include_directories(utility-lib PUBLIC "${U3_INCLUDE_DIR_EXTLIB_SQLITE}")
add_dependencies(utility-lib ${U3_NAME_EXTLIB_BOOST_UTIL})

if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
  target_link_libraries(utility-lib android-cpufeatures-lib)
endif()
