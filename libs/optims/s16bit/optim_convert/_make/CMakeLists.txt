#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/libs/optims/s16bit/optim_convert" path-lib-optim_convert )
file( GLOB_RECURSE files-lib-optim_convert "${path-lib-optim_convert}" "${path-lib-optim_convert}/*.cpp" "${path-lib-optim_convert}/*.hpp" )

add_library( optim_convert-lib STATIC ${files-lib-optim_convert} )

target_compile_definitions( optim_convert-lib   PUBLIC  ${shared_compile_def} )
target_compile_options(     optim_convert-lib   PUBLIC  ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( optim_convert-lib       
  ${all-boost-libs}
  ${shared_link_flags}
  optim-lib
  optim_s16bit_generic-lib
  core-lib )
