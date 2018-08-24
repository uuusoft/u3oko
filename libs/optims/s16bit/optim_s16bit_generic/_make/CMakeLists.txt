#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/libs/optims/s16bit/optim_s16bit_generic" path-lib-optim_s16bit_generic )
file( GLOB_RECURSE files-lib-optim_s16bit_generic "${path-lib-optim_s16bit_generic}" "${path-lib-optim_s16bit_generic}/*.cpp" "${path-lib-optim_s16bit_generic}/*.hpp" )

add_library( optim_s16bit_generic-lib STATIC ${files-lib-optim_s16bit_generic} )

target_compile_definitions( optim_s16bit_generic-lib   PUBLIC  ${shared_compile_def} )
target_compile_options(     optim_s16bit_generic-lib   PUBLIC  ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( optim_s16bit_generic-lib       
  ${all-boost-libs}
  ${shared_link_flags}
  optim-lib
  core-lib
  properties-lib )
