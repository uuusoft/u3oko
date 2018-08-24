#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/libs/optims/s16bit/optim_motion" path-lib-optim_motion )
file( GLOB_RECURSE files-lib-optim_motion "${path-lib-optim_motion}" "${path-lib-optim_motion}/*.cpp" "${path-lib-optim_motion}/*.hpp" )

add_library( optim_motion-lib STATIC ${files-lib-optim_motion} )

target_compile_definitions( optim_motion-lib   PUBLIC  ${shared_compile_def} )
target_compile_options(     optim_motion-lib   PUBLIC  ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( optim_motion-lib       
  ${all-boost-libs}
  ${shared_link_flags}
  optim-lib
  optim_s16bit_generic-lib
  core-lib )
