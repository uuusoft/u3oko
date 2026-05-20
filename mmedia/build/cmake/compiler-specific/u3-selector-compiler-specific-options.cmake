# author      Erashov Anton erashov2026@proton.me
# date        12.09.2024
# copyright   Erashov A.I.
# file        u3-selector-compiler-specific-options.cmake

if((CMAKE_C_COMPILER_ID STREQUAL "MSVC") OR (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC"))

  set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} /W4)
  set(CMAKE_CXX_FLAGS_DEBUG "/Od /ZI")
  set(CMAKE_CXX_FLAGS_RELEASE "/O2 /ZI")
  #set(U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} /WHOLEARCHIVE)
  #executable PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,my_static_lib>")

elseif((${CMAKE_C_COMPILER_ID} STREQUAL "GNU") OR (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"))

  set( U3_SHARED_COMPILE_OPTIONS_CPP  ${U3_SHARED_COMPILE_OPTIONS_CPP} -w -fPIC )
  set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -Wall -Wextra -Wpedantic)
  set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -Wno-invalid-utf8 -Wno-unused-parameter -Wno-reorder-ctor -Wno-reorder)
  set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -Wno-deprecated-declarations)
  set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 -flto=auto")

  # thread sanitizer false negative results
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "12.0")
    #message(FATAL_ERROR "${U3_MARK_FATAL}C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")
  endif()

elseif((${CMAKE_C_COMPILER_ID} STREQUAL "Clang") OR (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"))

  set( U3_SHARED_COMPILE_OPTIONS_CPP  ${U3_SHARED_COMPILE_OPTIONS_CPP} -w -fPIC)
  set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -Wall -Wextra -Wpedantic)
  set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -Wno-invalid-utf8 -Wno-unused-parameter -Wno-reorder-ctor -Wno-reorder)
  set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -Wno-deprecated-declarations)
  set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "-g -O3")

  if(NOT ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
    # sudo apt update && sudo apt install lld
    set(CMAKE_LINKER_TYPE LLD)

    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "20.0")
      message(AUTHOR_WARNING "ubuntu")
      message(AUTHOR_WARNING "wget https://apt.llvm.org/llvm.sh")
      message(AUTHOR_WARNING "chmod +x llvm.sh")
      message(AUTHOR_WARNING "sudo apt install lsb-release wget software-properties-common gnupg")
      message(AUTHOR_WARNING "sudo ./llvm.sh 20")
      message(AUTHOR_WARNING "sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-20 100")
      message(AUTHOR_WARNING "sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-20 100")
      message(FATAL_ERROR "${U3_MARK_FATAL}C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION} requared 20.0")
    endif()
  endif()

elseif(${CMAKE_C_COMPILER_ID} STREQUAL "AppleClang")

  #set( U3_SHARED_COMPILE_OPTIONS_CPP  ${U3_SHARED_COMPILE_OPTIONS_CPP} -w -fPIC )
  set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "-g -O3")

else()
  message(FATAL_ERROR "unknown compiler CMAKE_C_COMPILER_ID=" ${CMAKE_C_COMPILER_ID} ", CMAKE_CXX_COMPILER_ID=" ${CMAKE_CXX_COMPILER_ID})
endif()
