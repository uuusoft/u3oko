# author      Erashov Anton erashov2026@proton.me
# date        15.08.2024
# copyright   Erashov A.I.
# file        u3-link-libs-to-target-func.cmake

function(u3_link_libs_to_target)
  cmake_parse_arguments(U3_GVXX "OPTIONAL" "PAR_TARGET" "PAR_GROUP_LIBS;PAR_LIBS" ${ARGN})

  #message(FATAL_ERROR "CMAKE_LINK_GROUP_USING_RESCAN_SUPPORTED=${CMAKE_LINK_GROUP_USING_RESCAN_SUPPORTED}")
  if (U3_PLATFORM_NAME STREQUAL U3_PLATFORM_NAME_RASPBERRY OR
      U3_PLATFORM_NAME STREQUAL U3_PLATFORM_NAME_ORANGE_PI)
    # debug
    target_link_libraries(
        ${U3_GVXX_PAR_TARGET}
        ${U3_GVXX_PAR_GROUP_LIBS}
        ${U3_GVXX_PAR_LIBS}
        ${U3_GVXX_PAR_GROUP_LIBS}
        ${U3_GVXX_PAR_LIBS}
        ${U3_GVXX_PAR_GROUP_LIBS}
        ${U3_GVXX_PAR_LIBS}
        ${U3_GVXX_PAR_GROUP_LIBS}
        ${U3_GVXX_PAR_LIBS}
        ${U3_GVXX_PAR_GROUP_LIBS}
        ${U3_GVXX_PAR_LIBS}
        ${U3_GVXX_PAR_GROUP_LIBS}
        ${U3_GVXX_PAR_LIBS}
    )
  else ()
    # EAI-REFACT
    #if (CMAKE_LINK_GROUP_USING_RESCAN_SUPPORTED)
    if (0)

      target_link_libraries(${U3_GVXX_PAR_TARGET}
          $<LINK_GROUP:RESCAN, ${U3_GVXX_PAR_GROUP_LIBS} > ${U3_GVXX_PAR_LIBS}
      )

    else ()

      target_link_libraries(${U3_GVXX_PAR_TARGET}
          ${U3_GVXX_PAR_GROUP_LIBS}
          ${U3_GVXX_PAR_LIBS}
          ${U3_GVXX_PAR_GROUP_LIBS}
          ${U3_GVXX_PAR_LIBS}
          ${U3_GVXX_PAR_GROUP_LIBS}
      )

    endif ()
  endif ()

endfunction(u3_link_libs_to_target)
