# author      Erashov Anton erashov2026@proton.me
# date        07.04.2026
# copyright   Erashov A.I.
# file        module-test.cmake

#if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
#  message(WARNING "Unsupported OS received " ${U3_SYSTEM_NAME})
#  return()
#endif()

file(TO_CMAKE_PATH "${U3_BUILD_PATH_TO_LIBS}/modules/uuu_test" graph-module-u3_test)
file(GLOB_RECURSE files-module-u3_test "${graph-module-u3_test}" "${graph-module-u3_test}/*.cpp" "${graph-module-u3_test}/*.c")

if(U3_BUILD_MODULES_AS_LIBS)
  add_executable(module-u3_test ${files-module-u3_test})
else()
  add_library(module-u3_test SHARED ${files-module-u3_test})
endif()

set_target_properties(module-u3_test PROPERTIES OUTPUT_NAME "mpl_u3_test")
target_compile_definitions(module-u3_test PUBLIC ${U3_SHARED_COMPILE_DEF_CPP})
target_compile_options(module-u3_test PUBLIC ${U3_SHARED_COMPILE_OPTIONS_CPP} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
  set_property(TARGET module-u3_test PROPERTY MSVC_RUNTIME_LIBRARY ${U3_TARGET_PROPERTY_MSVC_RUNTIME_LIBRARY})
endif()

set(U3_LOCAL_MODULE_TEST_EXT_LIBS)

if(U3_BUILD_MODULES_AS_LIBS)
  #add_dependencies( module-u3_test ${U3_LIBS_OUR_VARIABLE_LIST} )
  set(U3_LOCAL_MODULE_TEST_EXT_LIBS)
endif()

add_dependencies(module-u3_test ${U3_NAME_EXTERNAL_LIB_BOOST_UTIL})

u3_link_libs_to_target(
  PAR_TARGET
  module-u3_test
  PAR_GROUP_LIBS
  ${U3_LOCAL_MODULE_TEST_EXT_LIBS}
  ${U3_LIBS_SYSTEM_STATIC_LIST}
  PAR_LIBS
  ${U3_LIBS_3RD_STATIC_LIST}
  ${U3_LOCAL_MODULE_TEST_EXT_LIBS}
  ${U3_SHARED_LINK_OPTIONS_CPP}
)
