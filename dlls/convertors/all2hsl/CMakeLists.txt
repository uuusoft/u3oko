#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/convertors/all2hsl/source" path-hsl-vcd )
file( GLOB_RECURSE files-hsl-vcd "${path-hsl-vcd}" "${path-hsl-vcd}/*.cpp" )

add_library( hsl-vcd SHARED ${files-hsl-vcd} )

set_target_properties(      hsl-vcd PROPERTIES  OUTPUT_NAME "vcd_all2hsl" )
target_compile_definitions( hsl-vcd PUBLIC      ${shared_compile_def} )
target_compile_options(     hsl-vcd PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( hsl-vcd
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  ${shared_link_flags} )
