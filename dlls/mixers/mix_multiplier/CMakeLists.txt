#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/mixers/mix_multiplier/source" path-mix_multiplier_vdm )
file( GLOB_RECURSE files-mix_multiplier_vdm "${path-mix_multiplier_vdm}" "${path-mix_multiplier_vdm}/*.cpp" )

add_library( mix_multiplier_vdm SHARED ${files-mix_multiplier_vdm} )

set_target_properties(      mix_multiplier_vdm   PROPERTIES  OUTPUT_NAME "vdm_mix_multiplier" )
target_compile_definitions( mix_multiplier_vdm   PUBLIC      ${shared_compile_def} )
target_compile_options(     mix_multiplier_vdm   PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( mix_multiplier_vdm
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  optim_s16bit_generic-lib
  optim_scale-lib
  ${shared_link_flags} )
