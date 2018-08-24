#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/sources/fake_vgen/source" path-fake_vgen-vss )
file( GLOB_RECURSE files-fake_vgen-vss "${path-fake_vgen-vss}" "${path-fake_vgen-vss}/*.cpp" )

add_library( fake_vgen-vss SHARED ${files-fake_vgen-vss} )

set_target_properties(      fake_vgen-vss   PROPERTIES  OUTPUT_NAME "vss_fake_vgen" )
target_compile_definitions( fake_vgen-vss   PUBLIC      ${shared_compile_def} )
target_compile_options(     fake_vgen-vss   PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( fake_vgen-vss
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  gen_lib-lib
  ${shared_link_flags} )
