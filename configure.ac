#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])

m4_define([gimo_major_version], [1])
m4_define([gimo_minor_version], [0])
m4_define([gimo_micro_version], [0])
m4_define([gimo_interface_age], [0])
m4_define([gimo_binary_age], [0])
m4_define([gimo_version],
        [gimo_major_version.gimo_minor_version.gimo_micro_version])

dnl libtool version related macros
m4_define([gimo_lt_release], [gimo_major_version.gimo_minor_version])
m4_define([gimo_lt_current],
        [m4_eval(100 * gimo_minor_version + gimo_micro_version - gimo_interface_age)])
m4_define([gimo_lt_revision], [gimo_interface_age])
m4_define([gimo_lt_age], [m4_eval(gimo_binary_age - gimo_interface_age)])
m4_define([gimo_lt_current_minus_age],
        [m4_eval(gimo_lt_current - gimo_lt_age)])

AC_INIT([gimo], [gimo_version], [email@email.com])
AC_CONFIG_SRCDIR([src/test-gtk.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror])

GIMO_MAJOR_VERSION=gimo_major_version
GIMO_MINOR_VERSION=gimo_minor_version
GIMO_MICRO_VERSION=gimo_micro_version
GIMO_INTERFACE_AGE=gimo_interface_age
GIMO_BINARY_AGE=gimo_binary_age
GIMO_VERSION=gimo_version
AC_SUBST(GIMO_MAJOR_VERSION)
AC_SUBST(GIMO_MINOR_VERSION)
AC_SUBST(GIMO_MICRO_VERSION)
AC_SUBST(GIMO_INTERFACE_AGE)
AC_SUBST(GIMO_BINARY_AGE)
AC_SUBST(GIMO_VERSION)

dnl libtool versioning
LT_RELEASE=gimo_lt_release
LT_CURRENT=gimo_lt_current
LT_REVISION=gimo_lt_revision
LT_AGE=gimo_lt_age
LT_CURRENT_MINUS_AGE=gimo_lt_current_minus_age
LT_VERSION_INFO=${LT_CURRENT}:${LT_REVISION}:${LT_AGE}
AC_SUBST(LT_RELEASE)
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)
AC_SUBST(LT_CURRENT_MINUS_AGE)
AC_SUBST(LT_VERSION_INFO)

dnl Initialize libtool
LT_PREREQ([2.2])
LT_INIT([disable-static])

dnl ================================================================
dnl Checks for programs.
dnl ================================================================

AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AM_PROG_CC_C_O

dnl give error and exit if we don't have pkgconfig
AC_CHECK_PROG(HAVE_PKGCONFIG, pkg-config, [ ],
    [AC_MSG_ERROR([You need to have pkg-config installed!])])

dnl ================================================================
dnl Checks for GLib
dnl ================================================================

GLIB_REQUIRED_VERSION=2.32.0
GLIB_MODULES="glib-2.0 >= $GLIB_REQUIRED_VERSION gobject-2.0 gthread-2.0 gmodule-no-export-2.0 gio-2.0"

PKG_CHECK_MODULES(GLIB, $GLIB_MODULES, :,
    AC_MSG_ERROR([
*** Glib $GLIB_REQUIRED_VERSION or better is required. The latest version of
*** Glib is always available from ftp://ftp.gtk.org/.]))

# Setup GLIB_MKENUMS to use glib-mkenums even if GLib is uninstalled.
GLIB_MKENUMS=`$PKG_CONFIG --variable=glib_mkenums glib-2.0`
AC_SUBST(GLIB_MKENUMS)

# Add in gthread-2.0 to CFLAGS but not to LIBS so we get any
# necesary defines for thread-safety.
GLIB_CFLAGS=`$PKG_CONFIG --cflags $GLIB_MODULES gthread-2.0`

dnl ================================================================
dnl Checks for Gtk
dnl ================================================================

GTK_REQUIRED=3.0
PKG_CHECK_MODULES(GTK, gtk+-3.0 >= $GTK_REQUIRED, :,
    AC_MSG_ERROR([Gtk+-3.0 not found]))

dnl ================================================================
dnl i18n stuff.
dnl ================================================================

GETTEXT_PACKAGE=gimo10
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE",
                   [The prefix for our gettext translation domains.])

# Configure options: --enable-debug[=no].
AC_ARG_ENABLE([debug],
        [AS_HELP_STRING([--enable-debug],
                [enable debug mode (default is no)])],
        [debug=yes], [debug=no])

AM_CONDITIONAL([DEBUG], [test x$debug = xyes])

if test "x${debug}" != "xno"; then
   AC_DEFINE([GIMO_DEBUG], [1], [Debugging mode])
   AC_CHECK_PROG([VALGRIND], [valgrind], [valgrind])
   CFLAGS="${CFLAGS} -g3 -gdwarf-2 -O0"
fi

RUN_ENVIRONMENT="GI_TYPELIB_PATH=\$(top_builddir)/src \
   LD_LIBRARY_PATH=/usr/local/lib:\$(top_builddir)/src/.libs"

TESTS_ENVIRONMENT="${RUN_ENVIRONMENT}"

if test -n "${VALGRIND}"; then
   TESTS_ENVIRONMENT+=" G_SLICE=always-malloc G_DEBUG=gc-friendly libtool --mode=execute \
${VALGRIND} -q --tool=memcheck --leak-check=full --num-callers=40 \
--show-possibly-lost=yes --malloc-fill=4 --free-fill=5 \
--suppressions=\$(top_srcdir)/src/gtk.supp --error-exitcode=1"
fi

AC_SUBST([RUN_ENVIRONMENT])
AC_SUBST([TESTS_ENVIRONMENT])

STRICT_CFLAGS="-Werror -Wstrict-prototypes"
AC_SUBST([STRICT_CFLAGS])

CFLAGS="${CFLAGS} -pedantic -Wall -Wno-long-long"

AC_CONFIG_FILES([Makefile
        src/Makefile])

AC_OUTPUT

echo \
"-------------------------------------------------
${PACKAGE_NAME} ${GIMO_VERSION}
Prefix: '${prefix}'.
Compiler: '${CC} ${CFLAGS} ${CPPFLAGS}'
Libraries: '${LIBS}'
Debug: '${debug}'
TESTS_ENVIRONMENT: '${TESTS_ENVIRONMENT}'
-------------------------------------------------"
