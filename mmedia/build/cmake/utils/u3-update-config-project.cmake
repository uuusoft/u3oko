# author      Erashov Anton erashov2026@proton.me
# date        26.05.2026
# copyright   Erashov A.I.
# file        u3-update-config-project.cmake

# mark build
if(U3_USE_GIT_HASH_FOR_MARK_BUILD)
  configure_file("includes/project_config.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/includes/project_config.hpp")
else()
  configure_file("includes/project_config.hpp.in.develop" "${CMAKE_CURRENT_SOURCE_DIR}/includes/project_config.hpp")
endif()

#
add_custom_target(
  AlwaysCheckGit
  COMMAND
    ${CMAKE_COMMAND} -DRUN_CHECK_GIT_VERSION=1 -Dpre_configure_dir=${pre_configure_dir} -Dpost_configure_file=${post_configure_dir} -DGIT_HASH_CACHE=${GIT_HASH_CACHE} -P
    ${CURRENT_LIST_DIR}/CheckGit.cmake
  BYPRODUCTS 
    ${post_configure_file}
)
