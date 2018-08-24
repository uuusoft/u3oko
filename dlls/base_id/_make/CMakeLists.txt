#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/base_id" path-base_id-vdd )
file( GLOB_RECURSE files-base_id-vdd "${path-base_id-vdd}" "${path-base_id-vdd}/*.cpp" )

add_library( base_id-vdd SHARED ${files-base_id-vdd} )

set_target_properties(      base_id-vdd PROPERTIES  OUTPUT_NAME "vdd_base_id" )
target_compile_definitions( base_id-vdd PUBLIC      ${shared_compile_def} )
target_compile_options(     base_id-vdd PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( base_id-vdd
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  ${shared_link_flags} )
