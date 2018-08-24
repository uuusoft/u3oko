#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/detectors/detect_move" path-vdetect1-vdd )
file( GLOB_RECURSE files-vdetect1-vdd "${path-vdetect1-vdd}" "${path-vdetect1-vdd}/*.cpp" )

add_library( vdetect1-vdd SHARED ${files-vdetect1-vdd} )

set_target_properties(      vdetect1-vdd    PROPERTIES  OUTPUT_NAME "vdd_detect_move" )
target_compile_definitions( vdetect1-vdd    PUBLIC      ${shared_compile_def} )
target_compile_options(     vdetect1-vdd    PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( vdetect1-vdd     
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  vgen_diff-vgd-lib
  vgen_mops-vgd-lib
  ${shared_link_flags} )
