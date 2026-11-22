# author      Erashov Anton erashov2026@proton.me
# date        12.09.2024
# copyright   Erashov A.I.
# file        u3-add-targert-dylib-func.cmake

include("./.ci/cmake/funcs/u3-link-libs-to-target-func.cmake")

function(u3_add_target_dylib)
  cmake_parse_arguments(
      U3_GVXX
      ""
      "TARGET_NAME;SOURCE_PATH;OUTPUT_NAME;FORCE_TO_DYLIB;USE_EXACTLY_SOURCE_FILES" "EXTENDED_LIBS;DEPEND_TARGETS;SOURCE_FILES"
      ${ARGN})

  file(TO_CMAKE_PATH "${U3_GVXX_SOURCE_PATH}" ${U3_GVXX_TARGET_NAME}-PATH)

  if (U3_GVXX_USE_EXACTLY_SOURCE_FILES)
    set(${U3_GVXX_TARGET_NAME}-FILES ${U3_GVXX_SOURCE_FILES})
  else ()
    file(GLOB_RECURSE ${U3_GVXX_TARGET_NAME}-FILES "${${U3_GVXX_TARGET_NAME}-PATH}" "${${U3_GVXX_TARGET_NAME}-PATH}/*.cpp")
  endif ()

  if (U3_BUILD_AS_MONOLITH AND
      NOT U3_GVXX_FORCE_TO_DYLIB)
    add_library(${U3_GVXX_TARGET_NAME} STATIC ${${U3_GVXX_TARGET_NAME}-FILES})
  else ()
    add_library(${U3_GVXX_TARGET_NAME} SHARED ${${U3_GVXX_TARGET_NAME}-FILES})
  endif ()

  #message(FATAL_ERROR "U3_GVXX_OUTPUT_NAME=${U3_GVXX_OUTPUT_NAME}")
  set_target_properties(
      ${U3_GVXX_TARGET_NAME}
      PROPERTIES
      #PREFIX ""
      OUTPUT_NAME ${U3_GVXX_OUTPUT_NAME}
  )

  target_compile_definitions(
      ${U3_GVXX_TARGET_NAME}
      PUBLIC
      ${U3_SHARED_COMPILE_DEF_CPP})

  target_compile_options(
      ${U3_GVXX_TARGET_NAME}
      PUBLIC
      ${U3_SHARED_COMPILE_OPTIONS_CPP} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

  add_dependencies(
      ${U3_GVXX_TARGET_NAME}
      ${U3_SELECTED_3RDLIBS_LIST}
      ${U3_DEPENDENCY_TARGETS_LIST}
      ${U3_GVXX_DEPEND_TARGETS})

  if (U3_BUILD_AS_MONOLITH AND
      NOT U3_GVXX_FORCE_TO_DYLIB)

    set(U3_DEPENDENCY_TARGETS_LIST
        ${U3_DEPENDENCY_TARGETS_LIST}
        ${U3_GVXX_DEPEND_TARGETS})

    set(U3_SELECTED_LIBS_VARIABLE_LIST
        ${U3_SELECTED_LIBS_VARIABLE_LIST}
        ${U3_GVXX_TARGET_NAME}
        ${U3_GVXX_EXTENDED_LIBS})

    # ulimit env ARG_MAX
    list(REMOVE_DUPLICATES U3_SELECTED_LIBS_VARIABLE_LIST)
    list(REMOVE_DUPLICATES U3_DEPENDENCY_TARGETS_LIST)

  else ()

    u3_link_libs_to_target(
        PAR_TARGET
        ${U3_GVXX_TARGET_NAME}
        PAR_GROUP_LIBS
        ${U3_GVXX_EXTENDED_LIBS}
        ${U3_LINK_EVENTS_LIBS}
        ${U3_LINK_IBASE_LIBS}
        ${U3_LINK_BASE_LIBS}
        proxy-lib
        utility-lib
        ${U3_SELECTED_3RDLIBS_LIST}
        PAR_LIBS
        ${U3_SHARED_LINK_OPTIONS_CPP})

  endif ()

  set(U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} PARENT_SCOPE)
  set(U3_SELECTED_LIBS_VARIABLE_LIST ${U3_SELECTED_LIBS_VARIABLE_LIST} PARENT_SCOPE)
endfunction(u3_add_target_dylib)
