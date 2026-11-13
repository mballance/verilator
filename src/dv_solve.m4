# DESCRIPTION: Verilator: configure check for the dv-solve constraint solver
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of either the GNU Lesser General Public License Version 3
# or the Perl Artistic License Version 2.0.
# SPDX-FileCopyrightText: 2026 Wilson Snyder
# SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0

# VL_CHECK_DV_SOLVE: handle --with-dv-solve[=no|yes|PREFIX]
#
# Finds dv-solve with pkg-config (searching PREFIX first, if given), or
# without pkg-config in PREFIX. On success, defines HAVE_DV_SOLVE, with
# pkg-config also DV_SOLVE_RUNTIME_LDLIBS (the
# libraries a model links, relative to $(DV_SOLVE_ROOT)), and sets
# CFG_CXXFLAGS_DVS and CFG_LIBS_DVS (the problem writer, linked into
# verilator_bin) and CFG_DV_SOLVE_ROOT (the default of $DV_SOLVE_ROOT).
AC_DEFUN([VL_CHECK_DV_SOLVE], [
AC_ARG_WITH([dv-solve],
            [AS_HELP_STRING([--with-dv-solve@<:@=PREFIX@:>@],
                            [build the dv-solve constraint solver back-end
                             (--solver-dvs), finding dv-solve with
                             pkg-config or in PREFIX (default is no)])],
            [], [with_dv_solve=no])
CFG_CXXFLAGS_DVS=
CFG_LIBS_DVS=
CFG_DV_SOLVE_ROOT=
_vl_dvs_ldlibs=
AS_IF([test "x$with_dv_solve" != xno], [
  AS_IF([test "x$with_dv_solve" != xyes], [
    PKG_CONFIG_PATH="$with_dv_solve/lib/pkgconfig:$with_dv_solve/lib64/pkgconfig${PKG_CONFIG_PATH:+:$PKG_CONFIG_PATH}"
    export PKG_CONFIG_PATH
  ])
  AC_PATH_PROG([PKG_CONFIG], [pkg-config])
  AC_MSG_CHECKING([for dv-solve])
  AS_IF([test -n "$PKG_CONFIG" && $PKG_CONFIG --exists dv-solve dv-solve-writer], [
    CFG_CXXFLAGS_DVS=`$PKG_CONFIG --cflags dv-solve-writer`
    CFG_LIBS_DVS=`$PKG_CONFIG --libs dv-solve-writer`
    CFG_DV_SOLVE_ROOT=`$PKG_CONFIG --variable=prefix dv-solve`
    _vl_dvs_ldlibs=`$PKG_CONFIG --define-variable=prefix='$(DV_SOLVE_ROOT)' --static --libs dv-solve`
    _vl_dvs_ldlibs=`echo $_vl_dvs_ldlibs`
  ], [test "x$with_dv_solve" != xyes], [
    CFG_CXXFLAGS_DVS="-I$with_dv_solve/include -DDVS_STATIC"
    CFG_LIBS_DVS="-L$with_dv_solve/lib -ldv_solve_writer"
    CFG_DV_SOLVE_ROOT=$with_dv_solve
  ], [
    AC_MSG_ERROR([dv-solve not found by pkg-config; use --with-dv-solve=PREFIX])
  ])
  _vl_dvs_save_CPPFLAGS=$CPPFLAGS
  _vl_dvs_save_LIBS=$LIBS
  CPPFLAGS="$CPPFLAGS $CFG_CXXFLAGS_DVS"
  LIBS="$CFG_LIBS_DVS $LIBS"
  AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <dv_solve/dvs_writer.h>]],
                                  [[return dvs_problem_format_version() != DVS_PROBLEM_FORMAT_VERSION;]])],
                 [AC_COMPUTE_INT([_vl_dvs_version], [DVS_PROBLEM_FORMAT_VERSION],
                                 [[#include <dv_solve/dvs_writer.h>]])])
  CPPFLAGS=$_vl_dvs_save_CPPFLAGS
  LIBS=$_vl_dvs_save_LIBS
  AS_IF([test -z "$_vl_dvs_version"], [
    AC_MSG_ERROR([cannot link the dv-solve problem writer with: $CFG_CXXFLAGS_DVS $CFG_LIBS_DVS])
  ])
  CFG_DV_SOLVE_ROOT=`cd "$CFG_DV_SOLVE_ROOT" && pwd`
  AC_MSG_RESULT([yes, problem format $_vl_dvs_version, DV_SOLVE_ROOT=$CFG_DV_SOLVE_ROOT])
  AC_DEFINE([HAVE_DV_SOLVE], [1], [Defined if built with the dv-solve back-end])
  AS_IF([test -n "$_vl_dvs_ldlibs"], [
    AC_DEFINE_UNQUOTED([DV_SOLVE_RUNTIME_LDLIBS], ["$_vl_dvs_ldlibs"],
                       [Libraries of the dv-solve runtime, for models])
  ])
])
AC_SUBST(CFG_CXXFLAGS_DVS)
AC_SUBST(CFG_LIBS_DVS)
AC_SUBST(CFG_DV_SOLVE_ROOT)
])
