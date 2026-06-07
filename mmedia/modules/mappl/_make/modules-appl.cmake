# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2017
# copyright   Erashov A.I.
# file        module-appl.cmake

file(TO_CMAKE_PATH "${U3_BUILD_PATH_TO_LIBS}/modules/mappl" graph-module-mappl)
file(GLOB_RECURSE files-module-mappl "${graph-module-mappl}" "${graph-module-mappl}/*.cpp" "${graph-module-mappl}/*.c")

set(U3_BUILD_LOCAL_MODULE_APPL_AS_LIB 0)

if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
  if(U3_BUILD_MODULES_AS_LIBS)
    add_library(module-mappl STATIC ${files-module-mappl})
    set(U3_BUILD_LOCAL_MODULE_APPL_AS_LIB 1)
  else()
    add_library(module-mappl SHARED ${files-module-mappl})
  endif()
else()
  add_executable(module-mappl ${files-module-mappl})
endif()

set_target_properties(module-mappl PROPERTIES OUTPUT_NAME "mpl_mappl")
target_compile_definitions(module-mappl PUBLIC ${U3_SHARED_COMPILE_DEF_CPP})
target_compile_options(module-mappl PUBLIC ${U3_SHARED_COMPILE_OPTIONS_CPP} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)
add_dependencies(module-mappl ${U3_DEPENDENCY_TARGETS_LIST} ${U3_LIBS_3RD_STATIC_LIST})

if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
  set_property(TARGET module-mappl PROPERTY MSVC_RUNTIME_LIBRARY ${U3_TARGET_PROPERTY_MSVC_RUNTIME_LIBRARY})
endif()

if(NOT U3_BUILD_LOCAL_MODULE_APPL_AS_LIB EQUAL 1)
  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
    target_link_libraries(module-mappl ${log-lib})
  endif()

  set(U3_LOCAL_MODULE_APPL_EXT_LIBS)

  if(U3_BUILD_MODULES_AS_LIBS)
    set(U3_LOCAL_MODULE_APPL_EXT_LIBS
        ${U3_LOCAL_MODULE_APPL_EXT_LIBS}
        optim_scale-lib
        codec_gen-lib
        codec_funcs-lib
        ${U3_LIBS_OUR_VARIABLE_LIST}
        ${U3_LIBS_OUR_STATIC_LIST}
        turbo_jpeg-lib
        ${U3_LIBS_3RD_STATIC_LIST}
    )
  endif()

  # ulimit env ARG_MAX
  #list( REMOVE_DUPLICATES U3_LOCAL_MODULE_APPL_EXT_LIBS )

  u3_link_libs_to_target(
    PAR_TARGET
    module-mappl
    PAR_GROUP_LIBS
    ${U3_LOCAL_MODULE_APPL_EXT_LIBS}
    ${U3_LINK_ALL_IGENERIC_LIBS}
    ${U3_LINK_ALL_GENERIC_LIBS}
    devents-dll
    doptim-dll
    #${all-ievent-libs}
    ${U3_LINK_ALL_EVENTS_LIBS}
    optim_gen_convert-lib
    ${U3_LIBS_SYSTEM_STATIC_LIST}
    PAR_LIBS
    ${U3_LIBS_3RD_STATIC_LIST}
    ${U3_SHARED_LINK_OPTIONS_CPP}
    proxy-lib
    ${U3_LOCAL_MODULE_APPL_EXT_LIBS}
    helpers-lib
  )

endif()
