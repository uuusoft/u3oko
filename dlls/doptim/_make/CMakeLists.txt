#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/doptim" path-doptim-dll )
file( GLOB_RECURSE files-doptim-dll "${path-doptim-dll}" "${path-doptim-dll}/*.cpp" )

add_library( doptim-dll SHARED ${files-doptim-dll} )

set_target_properties(          doptim-dll  PROPERTIES  OUTPUT_NAME "vdd_doptim" )
target_compile_definitions (    doptim-dll  PUBLIC      ${shared_compile_def} )
target_compile_options(         doptim-dll  PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( doptim-dll       
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
