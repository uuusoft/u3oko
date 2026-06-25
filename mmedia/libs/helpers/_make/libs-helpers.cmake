# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        libs-helpers.cmake

u3_add_target_lib(TARGET_NAME helpers-lib SOURCE_PATH ${U3_BUILD_PATH_TO_LIBS}/libs/helpers)

target_include_directories(helpers-lib PUBLIC "${U3_INCLUDE_DIR_EXTLIB_SQLITE}")
add_dependencies(helpers-lib ${U3_NAME_EXTLIB_BOOST_UTIL})

if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
  target_link_libraries(helpers-lib android-cpufeatures-lib)
endif()
