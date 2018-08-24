#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/filter_noise/space" path-vcleaner_space_vdd )
file( GLOB_RECURSE files-vcleaner_space_vdd "${path-vcleaner_space_vdd}" "${path-vcleaner_space_vdd}/*.cpp" )

add_library( vcleaner_space_vdd SHARED ${files-vcleaner_space_vdd} )

set_target_properties(      vcleaner_space_vdd  PROPERTIES  OUTPUT_NAME "vfn_space" )
target_compile_definitions( vcleaner_space_vdd  PUBLIC      ${shared_compile_def} )
target_compile_options(     vcleaner_space_vdd  PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( vcleaner_space_vdd   
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  ${shared_link_flags} )
