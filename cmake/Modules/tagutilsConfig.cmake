INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_TAGUTILS tagutils)

FIND_PATH(
    TAGUTILS_INCLUDE_DIRS
    NAMES tagutils/api.h
    HINTS $ENV{TAGUTILS_DIR}/include
        ${PC_TAGUTILS_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREEFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    TAGUTILS_LIBRARIES
    NAMES gnuradio-tagutils
    HINTS $ENV{TAGUTILS_DIR}/lib
        ${PC_TAGUTILS_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TAGUTILS DEFAULT_MSG TAGUTILS_LIBRARIES TAGUTILS_INCLUDE_DIRS)
MARK_AS_ADVANCED(TAGUTILS_LIBRARIES TAGUTILS_INCLUDE_DIRS)

