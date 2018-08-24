#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/terminals/video_sender" path-msg_video-vdd )
file( GLOB_RECURSE files-msg_video-vdd "${path-msg_video-vdd}" "${path-msg_video-vdd}/*.cpp" )

add_library( msg_video-vdd SHARED ${files-msg_video-vdd} )

set_target_properties(      msg_video-vdd   PROPERTIES  OUTPUT_NAME "vts_video_sender" )
target_compile_definitions( msg_video-vdd   PUBLIC      ${shared_compile_def} )
target_compile_options(     msg_video-vdd   PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( msg_video-vdd
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  optim-lib
  ${all-event-libs}
  ${shared_link_flags} )
