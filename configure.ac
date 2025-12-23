AC_INIT([lib7zip], [4.0.0], [lib7zip-users@googlegroups.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB
AM_PROG_AR
LT_INIT

# Check for C++17 support
AX_CXX_COMPILE_STDCXX([17], [noext], [mandatory])

# Check for required headers
AC_CHECK_HEADERS([stdlib.h string.h errno.h])

# Check for dl library (for dynamic loading)
AC_CHECK_LIB([dl], [dlopen], [DL_LIBS="-ldl"], [DL_LIBS=""])
AC_SUBST([DL_LIBS])

# Windows OLE/COM libraries (needed for BSTR/Variant helpers)
WIN_OLE_LIBS=""
case "$host_os" in
  *mingw* | *msys*)
    WIN_OLE_LIBS="-lole32 -loleaut32 -luuid"
    ;;
esac
AC_SUBST([WIN_OLE_LIBS])

# Check for Windows-specific functions
AC_CHECK_DECLS([MultiByteToWideChar, WideCharToMultiByte], [], [], [#include <windows.h>])

# Define platform-specific variables
case "$host_os" in
  *mingw*)
    AC_DEFINE([UNICODE], [1], [Define UNICODE for MinGW])
    AC_DEFINE([_UNICODE], [1], [Define _UNICODE for MinGW])
    ;;
  *darwin*)
    AC_DEFINE([CMAKE_MACOSX_RPATH], [1], [Define CMAKE_MACOSX_RPATH for macOS])
    ;;
esac

AM_CONDITIONAL([MINGW], [case "$host_os" in *mingw*|*msys*) true;; *) false;; esac])

# Check for 7zip source directory
AC_ARG_WITH([7zip-source],
  [AS_HELP_STRING([--with-7zip-source=DIR],
    [location of 7zip source directory @<:@default=third_party/7zip@:>@])],
  [SEVENZIP_SOURCE_DIR="$withval"],
  [SEVENZIP_SOURCE_DIR="third_party/7zip"])

AC_CHECK_FILE([$srcdir/$SEVENZIP_SOURCE_DIR/CPP/7zip/Archive/IArchive.h],
  [AC_MSG_RESULT([7zip source found at $SEVENZIP_SOURCE_DIR])],
  [AC_MSG_ERROR([7zip source not found at $SEVENZIP_SOURCE_DIR. Please ensure git submodule is initialized: git submodule update --init --recursive])])

AC_SUBST([SEVENZIP_SOURCE_DIR])

# Build options
AC_ARG_ENABLE([shared],
  [AS_HELP_STRING([--enable-shared],
    [build shared library @<:@default=no@:>@])],
  [build_shared=$enableval],
  [build_shared=no])

AC_ARG_ENABLE([tests],
  [AS_HELP_STRING([--enable-tests],
    [build test programs @<:@default=no@:>@])],
  [build_tests=$enableval],
  [build_tests=no])

AM_CONDITIONAL([BUILD_SHARED_LIB], [test "x$build_shared" = "xyes"])
AM_CONDITIONAL([BUILD_TESTS], [test "x$build_tests" = "xyes"])

# Output files
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 test/Makefile
 lib7zip.pc
])
AC_OUTPUT

echo "
lib7zip $VERSION configuration:
===============================

  Source code location:  ${srcdir}
  7zip source location:  ${SEVENZIP_SOURCE_DIR}
  Compiler:              ${CXX}
  Build shared library:  ${build_shared}
  C++ standard:          C++17

  Now type 'make' to compile lib7zip
"
