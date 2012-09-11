<?php

// http://www.terrence.com/opengl/ccube/ccube.html

// http://php.net/manual/ja/ref.array.php#82161
  function array_flatten($a) {
    foreach($a as $k=>$v) $a[$k]=(array)$v;
    return call_user_func_array('array_merge',$a);
  }

// Name     : OpenGL Color Cube
// Author   : Terrence Ma
// Email    : terrence@terrence.com
// Web      : http://www.terrence.com
// Date     : 10/25/2001
// Modified : Tutorial sample from Mesa3d.org (http://www.mesa3d.org)

/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED 
 * Permission to use, copy, modify, and distribute this software for 
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that 
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. 
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 *  aapoly.c
 *  This program draws filled polygons with antialiased
 *  edges.  The special GL_SRC_ALPHA_SATURATE blending 
 *  function is used.
 *  Pressing the 't' key turns the antialiasing on and off.
 */

$polySmooth = true;

function init()
{
   glCullFace (GL_BACK);
   glEnable (GL_CULL_FACE);
   glBlendFunc (GL_SRC_ALPHA_SATURATE, GL_ONE);
   glClearColor (0.0, 0.0, 0.0, 0.0);
}

define('NFACE', 6);
define('NVERT', 8);

function drawCube($x0, $x1, $y0, $y1,
        $z0, $z1)
{
   /* static */ $v = array(array(0, 0, 0), array(0, 0, 0), array(0, 0, 0), array(0, 0, 0), array(0, 0, 0), array(0, 0, 0), array(0, 0, 0), array(0, 0, 0));// [8][3];
   /* static */ $c = array( // [8][4]
      array(0.0, 0.0, 0.0, 1.0), array(1.0, 0.0, 0.0, 1.0),
      array(0.0, 1.0, 0.0, 1.0), array(1.0, 1.0, 0.0, 1.0),
      array(0.0, 0.0, 1.0, 1.0), array(1.0, 0.0, 1.0, 1.0),
      array(0.0, 1.0, 1.0, 1.0), array(1.0, 1.0, 1.0, 1.0)
   );
   $c = array_flatten($c); // convert to C array memory layout

/*  indices of front, top, left, bottom, right, back faces  */
   /* static */ $indices = array( // [NFACE][4]
      array(4, 5, 6, 7), array(2, 3, 7, 6), array(0, 4, 7, 3),
      array(0, 1, 5, 4), array(1, 5, 6, 2), array(0, 3, 2, 1)
   );

   $indices = array_flatten($indices) ; // convert to C array memory layout

   $v[0][0] = $v[3][0] = $v[4][0] = $v[7][0] = $x0;
   $v[1][0] = $v[2][0] = $v[5][0] = $v[6][0] = $x1;
   $v[0][1] = $v[1][1] = $v[4][1] = $v[5][1] = $y0;
   $v[2][1] = $v[3][1] = $v[6][1] = $v[7][1] = $y1;
   $v[0][2] = $v[1][2] = $v[2][2] = $v[3][2] = $z0;
   $v[4][2] = $v[5][2] = $v[6][2] = $v[7][2] = $z1;

   $v = array_flatten($v);  // convert to C array memory layout

   glEnableClientState (GL_VERTEX_ARRAY);
   glEnableClientState (GL_COLOR_ARRAY);

   glVertexPointer (3, GL_FLOAT, 0, $v);
   glColorPointer (4, GL_FLOAT, 0, $c);
   glDrawElements (GL_QUADS, NFACE*4, GL_UNSIGNED_BYTE, $indices);

   glDisableClientState (GL_VERTEX_ARRAY);
   glDisableClientState (GL_COLOR_ARRAY);
}

/*  Note:  polygons must be drawn from front to back
 *  for proper blending.
 */
function display()
{
   global $polySmooth;
   if ($polySmooth) {
      glClear (GL_COLOR_BUFFER_BIT);
      glEnable (GL_BLEND);
      glEnable (GL_POLYGON_SMOOTH);
      glDisable (GL_DEPTH_TEST);
   }
   else { 
      glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glDisable (GL_BLEND);
      glDisable (GL_POLYGON_SMOOTH);
      glEnable (GL_DEPTH_TEST);
   }

   glPushMatrix ();
      glTranslatef (0.0, 0.0, -8.0);    
      glRotatef (30.0, 1.0, 0.0, 0.0);
      glRotatef (60.0, 0.0, 1.0, 0.0); 
      drawCube(-0.8, 0.8, -0.8, 0.8, -0.8, 0.8);
   glPopMatrix ();
   glFlush ();
}

function reshape($w, $h)
{
   glViewport(0, 0, $w, $h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(30.0, $w/$h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

/* ARGSUSED1 */
function keyboard($key, $x, $y)
{
   global $polySmooth;
   switch ($key) {
      case 't':
      case 'T':
         $polySmooth = !$polySmooth;
         glutPostRedisplay();
         break;
      case chr(27);
         exit(0);  /*  Escape key  */
         break;
      default:
         break;
   }
}

/*  Main Loop
 */
// main(int argc, char** argv)

   glutInit($argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB 
                        | GLUT_ALPHA | GLUT_DEPTH);
   glutInitWindowSize(400, 400);
   glutCreateWindow("OpenGL Color Cube");
   init ();

   glutReshapeFunc ('reshape');
   glutKeyboardFunc ('keyboard');

   glutDisplayFunc ('display');
   glutMainLoop();

   return 0;

