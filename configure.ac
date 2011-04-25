AC_INIT([tail.io client], [0.1], [bug-report@tail.io], [tailio], [http://tail.io/])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 no-define foreign])
AC_CONFIG_HEADERS([config.h])
AC_PROG_CC
AC_PROG_CXX
AC_CONFIG_FILES([Makefile])
AC_ARG_ENABLE(debug,
	AS_HELP_STRING([--enable-debug],[enable debugging, default: no]),
	[case "${enableval}" in
           yes) debug=true ;;
           no)  debug=false ;;
           *)  AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
	esac],
	[debug=false]
)
AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")
AC_OUTPUT