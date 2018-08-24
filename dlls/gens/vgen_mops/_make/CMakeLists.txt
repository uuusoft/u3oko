#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/gens/vgen_mops" path-vgen_mops-vgd )
file( GLOB files-vgen_mops-vgd "${path-vgen_mops-vgd}" "${path-vgen_mops-vgd}/*.cpp" )

add_library( vgen_mops-vgd SHARED ${files-vgen_mops-vgd} )

set_target_properties(      vgen_mops-vgd   PROPERTIES  OUTPUT_NAME "vgd_vgen_mops" )
target_compile_definitions( vgen_mops-vgd   PUBLIC      ${shared_compile_def} )
target_compile_options(     vgen_mops-vgd   PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( vgen_mops-vgd
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  vgen_mops-vgd-lib
  ${shared_link_flags} )
