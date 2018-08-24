#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/sources/gen_vgen/source" path-gen_vgen-vsd )
file( GLOB_RECURSE files-gen_vgen-vsd "${path-gen_vgen-vsd}" "${path-gen_vgen-vsd}/*.cpp" )

add_library( gen_vgen-vsd SHARED ${files-gen_vgen-vsd} )

set_target_properties(      gen_vgen-vsd    PROPERTIES  OUTPUT_NAME "vsd_gen_vgen" )
target_compile_definitions( gen_vgen-vsd    PUBLIC      ${shared_compile_def} )
target_compile_options(     gen_vgen-vsd    PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( gen_vgen-vsd     
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  gen_lib-lib
  ${shared_link_flags} )
