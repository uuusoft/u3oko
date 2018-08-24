#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/convertors/all2rgb" path-all2rgb-vcd )
file( GLOB_RECURSE files-all2rgb-vcd "${path-all2rgb-vcd}" "${path-all2rgb-vcd}/*.cpp" )

add_library( all2rgb-vcd SHARED ${files-all2rgb-vcd} )

set_target_properties(      all2rgb-vcd PROPERTIES  OUTPUT_NAME "vcd_all2rgb" )
target_compile_definitions( all2rgb-vcd PUBLIC      ${shared_compile_def} )
target_compile_options(     all2rgb-vcd PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( all2rgb-vcd       
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  ${shared_link_flags} )
