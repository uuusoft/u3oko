# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2022
# copyright   Erashov A.I.
# file        u3-googletests.cmake

if(NOT U3_BUILD_TESTING)
    return()
endif()

enable_testing()

# Include GoogleTest via FetchContent, find_package, or add_subdirectory
#include(FetchContent)
#FetchContent_Declare(
#    googletest
#    URL https://github.com
#  )
#  FetchContent_MakeAvailable(googletest)

set(U3_TESTS_NAME ${U3_APPL_NAME}-tests)

# Define your isolated test executable
add_executable(${U3_TESTS_NAME}  
    /home/erashov/Documents/u3media/mmedia/libs/helpers/mem/ut/ut-libs-helpers-mem.cxx
)

target_compile_definitions(${U3_TESTS_NAME}  PUBLIC ${U3_SHARED_COMPILE_DEF_CPP})
target_compile_options(${U3_TESTS_NAME}  PUBLIC ${U3_SHARED_COMPILE_OPTIONS_CPP} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)
add_dependencies(${U3_TESTS_NAME}  ${U3_DEPENDENCY_TARGETS_LIST} ${U3_LIBS_3RD_STATIC_LIST})
target_include_directories(${U3_TESTS_NAME} SYSTEM PRIVATE "${U3_INCLUDE_DIR_EXTERNAL_LIB_GOOGLETEST}")
#message(FATAL_ERROR "U3_LIBS_3RD_STATIC_LIST=${U3_LIBS_3RD_STATIC_LIST}")
#message(FATAL_ERROR "U3_INCLUDE_DIR_EXTERNAL_LIB_GOOGLETEST=${U3_INCLUDE_DIR_EXTERNAL_LIB_GOOGLETEST}")
#if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
#  set_property(TARGET module-uuu_appl PROPERTY MSVC_RUNTIME_LIBRARY ${U3_TARGET_PROPERTY_MSVC_RUNTIME_LIBRARY})
#endif()

#if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
#  target_link_libraries(module-uuu_appl ${log-lib})
#endif()

#set(U3_LOCAL_MODULE_APPL_EXT_LIBS)

#if(U3_BUILD_MODULES_AS_LIBS)
#  set(U3_LOCAL_MODULE_APPL_EXT_LIBS
  #      ${U3_LOCAL_MODULE_APPL_EXT_LIBS}
  #      optim_scale-lib
  #      codec_gen-lib
  #      codec_funcs-lib
  #      ${U3_LIBS_OUR_VARIABLE_LIST}
  #      ${U3_LIBS_OUR_STATIC_LIST}
  #      turbo_jpeg-lib
  #      ${U3_LIBS_3RD_STATIC_LIST}
  #  )
  #endif()

u3_link_libs_to_target(
  PAR_TARGET
  ${U3_TESTS_NAME} 
  PAR_GROUP_LIBS
  #${U3_LOCAL_MODULE_APPL_EXT_LIBS}
  #${U3_LINK_ALL_IGENERIC_LIBS}
  #${U3_LINK_ALL_GENERIC_LIBS}
  #devents-dll
  #doptim-dll
  #${all-ievent-libs}
  #${U3_LINK_ALL_EVENTS_LIBS}
  #optim_gen_convert-lib
  #${U3_LIBS_SYSTEM_STATIC_LIST}
  PAR_LIBS
  #${U3_LIBS_3RD_STATIC_LIST}
  ${U3_SHARED_LINK_OPTIONS_CPP}
  #proxy-lib
  #${U3_LOCAL_MODULE_APPL_EXT_LIBS}
  helpers-lib
  googletest-lib
  googletest-lib2
)

#target_link_libraries(${U3_TESTS_NAME} PRIVATE gtest_main)
    
include(GoogleTest)
gtest_discover_tests(${U3_TESTS_NAME})
