# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        modules-storage.cmake

u3_add_target_dylib(
    TARGET_NAME module-mstorage
    SOURCE_PATH ${U3_PATH_ROOT}/modules/mstorage
    OUTPUT_NAME mpl_mstorage
    FORCE_TO_DYLIB FALSE
    USE_EXACTLY_SOURCE_FILES FALSE
    SOURCE_FILES ""
    EXTENDED_LIBS
    ilink-lib
    optim-lib
    icore-lib
    iproperties-lib
    dbufs-dll
    DEPEND_TARGETS
    ${U3_NAME_SQLITE_UTIL}
    dbufs-dll
)

target_include_directories(module-mstorage PUBLIC "${U3_INCLUDE_DIR_EXTLIB_SQLITE}")
