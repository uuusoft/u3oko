#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/utils/mem_functs" path-dll-mem_functs )
file( GLOB_RECURSE files-dll-mem_functs "${path-dll-mem_functs}" "${path-dll-mem_functs}/*.cpp" "${path-dll-mem_functs}/*.hpp" )

include_directories( "../../../../../boost/" )

add_library( mem_functs-dll SHARED ${files-dll-mem_functs} )

set_target_properties(      mem_functs-dll PROPERTIES OUTPUT_NAME  "mem_functs" )
target_compile_options(     mem_functs-dll PUBLIC                  ${shared_compile_options} )
target_compile_definitions( mem_functs-dll PUBLIC                  ${shared_compile_def} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( mem_functs-dll
  ${all-boost-libs}
  ${log-lib}
  helpers-lib
  ${shared_link_flags} )
