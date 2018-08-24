#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/libs/helpers" path-lib-helpers )
file( GLOB_RECURSE files-lib-helpers "${path-lib-helpers}" "${path-lib-helpers}/*.cpp" "${path-lib-helpers}/*.hpp" )

add_library( helpers-lib STATIC ${files-lib-helpers} )

target_compile_definitions( helpers-lib     PUBLIC  ${shared_compile_def} )
target_compile_options(     helpers-lib     PUBLIC  ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Android" )
 target_link_libraries( helpers-lib          cpufeatures-lib )
endif()

target_link_libraries( helpers-lib          
  ${all-boost-libs}
  ${shared_link_flags} )
