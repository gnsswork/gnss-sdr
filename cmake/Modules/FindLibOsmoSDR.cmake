# Tries to find libosmosdr.
#
# Usage of this module as follows:
#
# find_package(LibOsmoSDR)
#
#
# Variables defined by this module:
#
# LIBOSMOSDR_FOUND System has libosmosdr libs/headers
# LIBOSMOSDR_LIBRARIES The libosmosdr libraries 
# LIBOSMOSDR_INCLUDE_DIR The location of libosmosdr headers


if(NOT LIBOSMOSDR_FOUND)
  pkg_check_modules (LIBOSMOSDR_PKG libosmosdr)
  find_path(LIBOSMOSDR_INCLUDE_DIR NAMES osmosdr.h
    PATHS
    ${LIBOSMOSDR_PKG_INCLUDE_DIRS}
    /usr/include
    /usr/local/include
  )

 find_library(LIBOSMOSDR_LIBRARIES NAMES osmosdr
    PATHS
    ${LIBOSMOSDR_PKG_LIBRARY_DIRS}
    /usr/lib
    /usr/local/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
    /usr/lib/arm-linux-gnueabihf
    /usr/lib/arm-linux-gnueabi
    /usr/lib/aarch64-linux-gnu
    /usr/lib/mipsel-linux-gnu
    /usr/lib/mips-linux-gnu
    /usr/lib/mips64el-linux-gnuabi64
    /usr/lib/powerpc-linux-gnu
    /usr/lib/powerpc64-linux-gnu
    /usr/lib/powerpc64le-linux-gnu
    /usr/lib/powerpc-linux-gnuspe
    /usr/lib/hppa-linux-gnu
    /usr/lib/s390x-linux-gnu
    /usr/lib/i386-gnu
    /usr/lib/hppa-linux-gnu
    /usr/lib/x86_64-kfreebsd-gnu
    /usr/lib/i386-kfreebsd-gnu
    /usr/lib/m68k-linux-gnu
    /usr/lib/sh4-linux-gnu
    /usr/lib/sparc64-linux-gnu
    /usr/lib/x86_64-linux-gnux32
    /usr/lib/alpha-linux-gnu
    /usr/lib64
  )

  if(LIBOSMOSDR_INCLUDE_DIR AND LIBOSMOSDR_LIBRARIES)
    set(LIBOSMOSDR_FOUND TRUE CACHE INTERNAL "libosmosdr found")
    message(STATUS "Found libosmosdr: ${LIBOSMOSDR_INCLUDE_DIR}, ${LIBOSMOSDR_LIBRARIES}")
  else(LIBOSMOSDR_INCLUDE_DIR AND LIBOSMOSDR_LIBRARIES)
    set(LIBOSMOSDR_FOUND FALSE CACHE INTERNAL "libosmosdr found")
    message(STATUS "libosmosdr not found.")
  endif(LIBOSMOSDR_INCLUDE_DIR AND LIBOSMOSDR_LIBRARIES)

mark_as_advanced(LIBOSMOSDR_INCLUDE_DIR LIBOSMOSDR_LIBRARIES)

endif(NOT LIBOSMOSDR_FOUND)
