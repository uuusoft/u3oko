#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/gens/vgen_conv3_11/source" path-vgen_conv3_11-vgd )
file( GLOB_RECURSE files-vgen_conv3_11-vgd "${path-vgen_conv3_11-vgd}" "${path-vgen_conv3_11-vgd}/*.cpp" )

add_library( vgen_conv3_11-vgd SHARED ${files-vgen_conv3_11-vgd} )

set_target_properties(      vgen_conv3_11-vgd   PROPERTIES  OUTPUT_NAME "vgd_vgen_conv3_11" )
target_compile_definitions( vgen_conv3_11-vgd   PUBLIC      ${shared_compile_def} )
target_compile_options(     vgen_conv3_11-vgd   PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( vgen_conv3_11-vgd
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  ${shared_link_flags} )
