# author      Erashov Anton erashov2026@proton.me
# date        29.08.2024
# copyright   Erashov A.I.
# file        u3-darwin-specific.cmake
# U3_THIS_COMMERCIAL_PART_SOURCE_CODE

set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -std=${U3_CPP_STANDARD} -frtti -fexceptions -pthread)
set(U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -Wl,-rpath,@executable_path -lpthread -ldl)
set(U3_SHARED_COMPILE_DEF_CPP ${U3_SHARED_COMPILE_DEF_CPP} -DU3_OS_MACX_DESKTOP=1)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(U3_PREFIX_LIB_NAME lib)
set(U3_SUFFIX_LIB_NAME a)
set(U3_SUFFIX_DLL_NAME dylib)

#set( U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -rdynamic -export-dynamic -std=c++17 -frtti -fexceptions -fvisibility=default)

if(1)
  message(NOTICE "${U3_MARK_REFACT}add support dlib for Darwin")
  set(U3_SHARED_COMPILE_DEF_CPP ${U3_SHARED_COMPILE_DEF_CPP} -DU3_SKIP_DLIB=TRUE)
  set(U3_DBG_EXTERNAL_LIB_SKIP_DLIB TRUE)
endif()
