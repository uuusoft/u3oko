# author      Erashov Anton erashov2026@proton.me
# date        27.08.2024
# copyright   Erashov A.I.
# file        u3-sanity-functional.cmake

if(${U3_SANITY_BUILD_TYPE} STREQUAL "none")
  return()
endif()

if(${U3_SANITY_BUILD_TYPE} STREQUAL "ub")
  set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -fsanitize=undefined)
  set(U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -fsanitize=undefined -lubsan)
  #-lubsan
elseif(${U3_SANITY_BUILD_TYPE} STREQUAL "address")
  set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -fsanitize=address)
  set(U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -fsanitize=address -static-libasan)
elseif(${U3_SANITY_BUILD_TYPE} STREQUAL "hwaddress")
  set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -fsanitize=hwaddress)
  set(U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -fsanitize=hwaddress)
elseif(${U3_SANITY_BUILD_TYPE} STREQUAL "memory")
  if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -fsanitize=memory ASAN_OPTIONS=detect_odr_violation=0)
    set(U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -fsanitize=memory)
  endif()
elseif(${U3_SANITY_BUILD_TYPE} STREQUAL "thread")
  set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -fsanitize=thread)
  set(U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -fsanitize=thread)
else()
  message(FATAL_ERROR "unknown type U3_SANITY_BUILD_TYPE=${U3_SANITY_BUILD_TYPE}")
endif()
