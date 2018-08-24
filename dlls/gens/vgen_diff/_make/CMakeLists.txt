#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/gens/vgen_diff" path-vgen_diff-vgd )
file( GLOB files-vgen_diff-vgd "${path-vgen_diff-vgd}" "${path-vgen_diff-vgd}/*.cpp" )

add_library( vgen_diff-vgd SHARED ${files-vgen_diff-vgd} )

set_target_properties(      vgen_diff-vgd   PROPERTIES  OUTPUT_NAME "vgd_vgen_diff" )
target_compile_definitions( vgen_diff-vgd   PUBLIC      ${shared_compile_def} )
target_compile_options(     vgen_diff-vgd   PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( vgen_diff-vgd
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  vgen_diff-vgd-lib
  ${shared_link_flags} )
