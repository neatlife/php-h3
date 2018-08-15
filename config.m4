dnl $Id$
dnl config.m4 for extension h3

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(h3, for h3 support,
dnl Make sure that the comment is aligned:
dnl [  --with-h3             Include h3 support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(h3, whether to enable h3 support,
dnl Make sure that the comment is aligned:
[  --enable-h3           Enable h3 support])

if test "$PHP_H3" != "no"; then
  dnl  EXTRA_FLAGS=" -lh3 -std=c++0x -stdlib=libstdc++"
  dnl  C_FLAGS=" -lh3 -std=c99"
  dnl  CXX_FLAGS=" -lh3 -std=c++0x -stdlib=libstdc++"
  dnl  PHP_REQUIRE_CXX()
  dnl EXTRA_FLAGS="-std=c++0x -stdlib=libstdc++"
  dnl  PHP_SUBST(H3_SHARED_LIBADD)
  dnl  PHP_ADD_LIBRARY(stdc++, 1, H3_SHARED_LIBADD)
  dnl Write more examples of tests here...

  dnl # --with-h3 -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/h3.h"  # you most likely want to change this
  dnl if test -r $PHP_H3/$SEARCH_FOR; then # path given as parameter
  dnl   H3_DIR=$PHP_H3
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for h3 files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       H3_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$H3_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the h3 distribution])
  dnl fi

  dnl # --with-h3 -> add include path
  dnl PHP_ADD_INCLUDE($H3_DIR/include)

  dnl # --with-h3 -> check for lib and symbol presence
  dnl LIBNAME=h3 # you may want to change this
  dnl LIBSYMBOL=h3 # you most likely want to change this

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $H3_DIR/$PHP_LIBDIR, H3_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_H3LIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong h3 lib version or lib not found])
  dnl ],[
  dnl   -L$H3_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(H3_SHARED_LIBADD)
  EXTRA_CFLAGS="-lh3 -std=c99"
  PHP_SUBST(EXTRA_CFLAGS)

  LIBNAME=h3
  LIBSYMBOL=degsToRads
  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY($LIBNAME)
  ],[
    AC_MSG_ERROR([wrong libh3 is required or lib not found])
  ],[
    -l$LIBNAME
  ])

  PHP_SUBST(H3_SHARED_LIBADD)

  LIBS="-lh3 $LIBS"
  PHP_NEW_EXTENSION(h3, h3.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
