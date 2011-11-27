#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([pathspell], [0.1], [h.v.raven@googlemail.com])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_HEADERS([config.h])

AC_LANG([C++])

# Checks for programs.
AC_PROG_CXX

# Checks for header files.
AC_CHECK_HEADERS([tinyxml.h tinystr.h])

# Checks for library functions.
# TODO: Find a function in tinyxml that is found by AC_SEARCH_LIBS
LIBS="${LIBS} -ltinyxml"

# Check for Libraries
PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0])

AC_CONFIG_FILES([Makefile
		 src/Makefile])
AC_OUTPUT

echo \
"----------------------------------------

 ${PACKAGE_NAME} - Version ${PACKAGE_VERSION}

 Prefix:         ${prefix}
 Compiler:       ${CC} ${CXXFLAGS} ${CPPFLAGS}
 Libraries:      ${LIBS}

----------------------------------------"
