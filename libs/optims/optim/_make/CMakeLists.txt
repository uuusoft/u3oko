#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/libs/optims/optim" path-lib-optim )
file( GLOB_RECURSE files-lib-optim "${path-lib-optim}" "${path-lib-optim}/*.cpp" "${path-lib-optim}/*.hpp" )

add_library( optim-lib STATIC ${files-lib-optim} )

target_compile_definitions( optim-lib   PUBLIC  ${shared_compile_def} )
target_compile_options(     optim-lib   PUBLIC  ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( optim-lib       
  ${all-boost-libs}
  ${shared_link_flags}
  core-lib
  properties-lib
  ilog_events-lib )
