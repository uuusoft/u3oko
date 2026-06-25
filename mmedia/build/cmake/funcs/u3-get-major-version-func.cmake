# author      Erashov Anton erashov2026@proton.me
# date        12.09.2024
# copyright   Erashov A.I.
# file        u3-get-major-version-func.cmake

function(u3_get_major_version U3_ARG_SRC U3_ARG_RESULT)
    set(${U3_ARG_RESULT} "" PARENT_SCOPE)
    string(REPLACE "." ";" U3_FUNC_TEMP_VAR1 "${${U3_ARG_SRC}}")
    list(GET U3_FUNC_TEMP_VAR1 0 U3_FUNC_TEMP_VAR2)
    set(${U3_ARG_RESULT} ${U3_FUNC_TEMP_VAR2} PARENT_SCOPE)
endfunction()
