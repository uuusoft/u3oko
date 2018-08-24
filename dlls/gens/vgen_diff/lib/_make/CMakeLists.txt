#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/gens/vgen_diff/lib" path-vgen_diff-vgd-lib )
file( GLOB files-vgen_diff-vgd-lib "${path-vgen_diff-vgd-lib}" "${path-vgen_diff-vgd-lib}/*.cpp" )

add_library( vgen_diff-vgd-lib STATIC ${files-vgen_diff-vgd-lib} )

set_target_properties(      vgen_diff-vgd-lib   PROPERTIES  OUTPUT_NAME "vgd_vgen_diff_lib" )
target_compile_definitions( vgen_diff-vgd-lib   PUBLIC      ${shared_compile_def} )
target_compile_options(     vgen_diff-vgd-lib   PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( vgen_diff-vgd-lib
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  ${shared_link_flags} )
