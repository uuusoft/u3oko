#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/devents" path-devents-dll )
file( GLOB_RECURSE files-devents-dll "${path-devents-dll}" "${path-devents-dll}/*.cpp" )

add_library( devents-dll SHARED ${files-devents-dll} )

set_target_properties(          devents-dll  PROPERTIES  OUTPUT_NAME "vdd_devents" )
target_compile_definitions (    devents-dll  PUBLIC      ${shared_compile_def} )
target_compile_options(         devents-dll  PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( devents-dll       
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  optim-lib
  optim_gen_convert-lib
  optim_s16bit_generic-lib
  optim_convert-lib
  optim_bits-lib
  optim_block-lib
  optim_conv-lib
  optim_filter-lib
  optim_freq-lib
  optim_gen-lib
  optim_statistics-lib
  optim_motion-lib
  optim_ops-lib
  optim_scale-lib
  ${all-event-libs}
  ${shared_link_flags} )
