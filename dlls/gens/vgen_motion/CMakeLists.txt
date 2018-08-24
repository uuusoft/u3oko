#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/gens/vgen_motion/source" path-vgen_motion-vgd )
file( GLOB_RECURSE files-vgen_motion-vgd "${path-vgen_motion-vgd}" "${path-vgen_motion-vgd}/*.cpp" )

add_library( vgen_motion-vgd SHARED ${files-vgen_motion-vgd} )

set_target_properties(      vgen_motion-vgd PROPERTIES  OUTPUT_NAME "vgd_vgen_motion" )
target_compile_definitions( vgen_motion-vgd PUBLIC      ${shared_compile_def} )
target_compile_options(     vgen_motion-vgd PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( vgen_motion-vgd
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  vgen_diff-vgd-lib
  vgen_mops-vgd-lib
  ${shared_link_flags} )
