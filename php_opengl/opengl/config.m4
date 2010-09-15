dnl $Id: config.m4,v 1.9 2001/10/11 12:13:57 drbrain Exp $
dnl config.m4 for extension opengl
dnl Markus Fischer <mfischer@guru.josfine.at>
dnl don't forget to call PHP_EXTENSION(opengl)

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(opengl, for opengl support,
[  --with-opengl           Include OpenGL support])

if test "$PHP_OPENGL" != "no"; then
  dnl If you will not be testing anything external, like existence of
  dnl headers, libraries or functions in them, just uncomment the 
  dnl following line and you are ready to go.
  dnl Write more examples of tests here...

  if test -r $PHP_OPENGL/include/GL/gl.h; then
    OPENGL_DIR=$PHP_OPENGL
  else
    AC_MSG_CHECKING(for OpenGL development files in default path)
    for i in /usr/X11R6 /usr/local /usr; do
      if test -r $i/include/GL/gl.h; then
        OPENGL_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi

  if test -z "$OPENGL_DIR"; then
    AC_MSG_RESULT(not found)
    AC_MSG_ERROR(Please make sure OpenGL is properly installed - gl.h should be in <opengl-dir>/include/GL/)
  fi

  saved_LIBS="$LIBS"

  failed=yes
  for additional_libs in "" -lm; do
    if test ! -z "$additional_libs"; then
      AC_MSG_RESULT(checking with additional library $additional_libs)
    fi
    AC_MSG_CHECKING(if  OpenGL links properly)
    LIBS="$saved_LIBS -L$OPENGL_DIR/lib -lGL $additional_libs"
    AC_TRY_LINK( ,[char glBegin(); glBegin(); ], have_GL=yes, have_GL=no)
    AC_MSG_RESULT($have_GL)

    if test "$have_GL" = "no"; then
      AC_MSG_CHECKING(if  MesaGL links properly)
      LIBS="$saved_LIBS -L$OPENGL_DIR/lib -lMesaGL $additional_libs"
      AC_TRY_LINK( ,[char glBegin(); glBegin(); ], have_MesaGL=yes, have_MesaGL=no)
      AC_MSG_RESULT($have_MesaGL)
  
      if test "$have_MesaGL" = "no"; then
        AC_MSG_CHECKING(if  MesaGL with pthreads links properly)
        LIBS="$saved_LIBS -L$OPENGL_DIR/lib -lMesaGL -lpthread $additional_libs"
        AC_TRY_LINK( ,[char glBegin(); glBegin(); ], have_MesaGL_pthreads=yes, have_MesaGL_pthreads=no)
        AC_MSG_RESULT($have_MesaGL_pthreads)
  
        if test "$have_MesaGL_pthreads" != "no"; then
          LIBS="$saved_LIBS"
          PHP_ADD_LIBRARY_WITH_PATH(pthread, $OPENGL_DIR/lib, OPENGL_SHARED_LIBADD)
          PHP_ADD_LIBRARY_WITH_PATH(MesaGL, $OPENGL_DIR/lib, OPENGL_SHARED_LIBADD)
          PHP_ADD_LIBRARY_WITH_PATH(MesaGLU, $OPENGL_DIR/lib, OPENGL_SHARED_LIBADD)
          failed=no
        fi
      else
        LIBS="$saved_LIBS"
        PHP_ADD_LIBRARY_WITH_PATH(MesaGL, $OPENGL_DIR/lib, OPENGL_SHARED_LIBADD)
        PHP_ADD_LIBRARY_WITH_PATH(MesaGLU, $OPENGL_DIR/lib, OPENGL_SHARED_LIBADD)
        failed=no
      fi
    else
      LIBS="$saved_LIBS"
      PHP_ADD_LIBRARY_WITH_PATH(GL, $OPENGL_DIR/lib, OPENGL_SHARED_LIBADD)
      PHP_ADD_LIBRARY_WITH_PATH(GLU, $OPENGL_DIR/lib, OPENGL_SHARED_LIBADD)
      failed=no
    fi
    if test "$failed" = "no"; then
      if test ! -z "$additional_libs"; then
        PHP_EVAL_LIBLINE($additional_libs, OPENGL_SHARED_LIBADD)
      fi
      break
    fi
  done
  if test "$failed" = "yes"; then
    AC_MSG_ERROR(Can't find OpenGL nor MesaGL)
  fi
  unset additional_libs

  dnl Check whether we have osmesa.h and enable OSMesa support
  AC_MSG_CHECKING(for OSMesa support)
  if test -r $OPENGL_DIR/include/GL/osmesa.h; then
  	AC_DEFINE(PHP_OPENGL_OSMESA, 1, [Whether we support OSMesa])
	AC_MSG_RESULT(yes)
	PHP_ADD_LIBRARY_WITH_PATH(OSMesa, $OPENGL_DIR/lib, OPENGL_SHARED_LIBADD)
  else
    AC_MSG_RESULT(no)
  fi

  dnl Check wether we have glx.h and add GLX support
  AC_MSG_CHECKING(for GLX support)
  if test -r $OPENGL_DIR/include/GL/glx.h; then
  	AC_DEFINE(PHP_OPENGL_GLX, 1, [Whether we support GLX])
	AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
  fi

  PHP_ADD_INCLUDE($OPENGL_DIR/include)

  PHP_SUBST(OPENGL_SHARED_LIBADD)
  PHP_EXTENSION(opengl,$ext_shared)
fi
