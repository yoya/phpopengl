dnl $Id: config.m4,v 1.7 2001/09/29 14:57:24 drbrain Exp $
dnl config.m4 for extension glut
dnl Markus Fischer <mfischer@guru.josfine.at>
dnl don't forget to call PHP_EXTENSION(glut)

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(glut, for glut support,
[  --with-glut             Include GLUT support])

if test "$PHP_GLUT" != "no"; then
  dnl If you will not be testing anything external, like existence of
  dnl headers, libraries or functions in them, just uncomment the 
  dnl following line and you are ready to go.
  dnl Write more examples of tests here...

  if test -r $PHP_GLUT/include/GL/glut.h; then
    GLUT_DIR=$PHP_GLUT
  else
    AC_MSG_CHECKING(for GLUT development files in default path)
    for i in /usr/X11R6 /usr/local /usr; do
      if test -r $i/include/GL/glut.h; then
        GLUT_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi

  if test -z "$GLUT_DIR"; then
    AC_MSG_RESULT(not found)
	AC_MSG_ERROR(Please make sure GLUT is properly installed - glut.h should be in <glut-dir>/include/GL/)
  fi

  saved_LIBS="$LIBS"
  AC_MSG_CHECKING(if  GLUT links properly)
  failed=yes
  for additional_libs in "" "-lGL" "-lGL -lGLU" "-lGL -lGLU -lm"; do
    if test ! -z "$additional_libs"; then
      AC_MSG_CHECKING(checking with additional library $additional_libs)
    fi
    LIBS="$saved_LIBS -L$GLUT_DIR/lib -lglut $additional_libs"
    AC_TRY_LINK( ,[glutMainLoop();], have_glut=yes, have_glut=no)
    AC_MSG_RESULT($have_glut)
    LIBS="$saved_LIBS"

    if test "$have_glut" != "no"; then
      PHP_ADD_LIBRARY_WITH_PATH(glut, $GLUT_DIR/lib, GLUT_SHARED_LIBADD)
      if test ! -z "$additional_libs"; then
        PHP_EVAL_LIBLINE($additional_libs, GLUT_SHARED_LIBADD)
      fi
      failed=no
      break
    fi
  done
  if test "$failed" = "yes"; then
    AC_MSG_ERROR(Something went wrong - Please check config.log.)
  fi
  unset additional_libs

  PHP_ADD_INCLUDE($GLUT_DIR/include)

  PHP_SUBST(GLUT_SHARED_LIBADD)
  PHP_EXTENSION(glut,$ext_shared)
fi
