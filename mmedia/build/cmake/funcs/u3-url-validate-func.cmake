# author      Erashov Anton erashov2026@proton.me
# date        27.08.2024
# copyright   Erashov A.I.
# file        u3-url-validate-func.cmake

function(u3_validate_url)
  if(NOT DEFINED U3_ENV_GEN_FOLDER_EXT_LIBS)
    message(FATAL_ERROR "U3_ENV_GEN_FOLDER_EXT_LIBS=${U3_ENV_GEN_FOLDER_EXT_LIBS} not defined")
  endif()

  cmake_parse_arguments(U3_GVXX_VALIDATE_URL "" "URL" "" ${ARGN})

  set(U3_GVXX_VALIDATE_URL_OUTPUT_FILE "${U3_ENV_GEN_FOLDER_EXT_LIBS}/temp-output-validate_url.bin")
  set(U3_GVXX_VALIDATE_URL_ERROR_FILE "${U3_ENV_GEN_FOLDER_EXT_LIBS}/temp-error-validate_url.bin")
  set(U3_GVXX_VALIDATE_URL_RESULT -1)

  message(VERBOSE "WGET_EXECUTABLE=${WGET_EXECUTABLE}")
  message(VERBOSE "U3_GVXX_VALIDATE_URL_URL=${U3_GVXX_VALIDATE_URL_URL}")
  message(VERBOSE "u3_validate_url::begin call WGET_EXECUTABLE=${WGET_EXECUTABLE}")

  # --debug -S for debug
  execute_process(COMMAND ${WGET_EXECUTABLE} --timeout=5 --tries=1 -S --spider ${U3_GVXX_VALIDATE_URL_URL} RESULT_VARIABLE U3_GVXX_VALIDATE_URL_RESULT
                  OUTPUT_FILE ${U3_GVXX_VALIDATE_URL_OUTPUT_FILE} ERROR_FILE ${U3_GVXX_VALIDATE_URL_ERROR_FILE})

  message(VERBOSE "u3_validate_url::end call WGET_EXECUTABLE=${WGET_EXECUTABLE}")
  message(VERBOSE "U3_GVXX_VALIDATE_URL_RESULT=${U3_GVXX_VALIDATE_URL_RESULT}")
  message(VERBOSE "U3_GVXX_VALIDATE_URL_ECHO_OUTPUT=${U3_GVXX_VALIDATE_URL_ECHO_OUTPUT}")
  message(VERBOSE "U3_GVXX_VALIDATE_URL_OUTPUT_FILE=${U3_GVXX_VALIDATE_URL_OUTPUT_FILE}")

  if(U3_GVXX_VALIDATE_URL_RESULT EQUAL 0)
    set(U3_FUNCT_RESULT TRUE PARENT_SCOPE)
  endif()
endfunction(u3_validate_url)
