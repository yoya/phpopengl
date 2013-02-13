<?php

function array_flatten($a) {
   foreach($a as $k=>$v) $a[$k]=(array)$v;
   return call_user_func_array('array_merge',$a);
}

$polySmooth = true;

function init()
{
   glCullFace (GL_BACK);
   glEnable (GL_CULL_FACE);
//   glBlendFunc (GL_SRC_ALPHA_SATURATE, GL_ONE);
   glBlendFunc (GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
   glClearColor (0.0, 0.0, 0.0, 0.0);
}

define('NFACE', 6);
define('NVERT', 8);

function drawCube($x0, $x1, $y0, $y1,
        $z0, $z1)
{
   /* static */ $v = array(array(0, 0, 0), array(0, 0, 0), array(0, 0, 0), array(0, 0, 0), array(0, 0, 0), array(0, 0, 0), array(0, 0, 0), array(0, 0, 0));// [8][3];
   /* static */ $c = array( // [8][4]
      array(0.0, 0.0, 0.0, 0.5), array(1.0, 0.0, 0.0, 0.5),
      array(1.0, 1.0, 0.0, 0.5), array(0.0, 1.0, 0.0, 0.5),
      array(0.0, 0.0, 1.0, 0.5), array(1.0, 0.0, 1.0, 0.5),
      array(1.0, 1.0, 1.0, 0.5), array(0.0, 1.0, 1.0, 0.5)
   );
   $c = array_flatten($c); // convert to C memory layout

// print_r($c);

/*  indices of front, top, left, bottom, right, back faces  */
   /* static */ $indices = array( // [NFACE][4]
      array(4, 5, 6, 7), array(2, 3, 7, 6), array(0, 4, 7, 3),
//      array(0, 1, 5, 4), array(1, 5, 6, 2), array(0, 3, 2, 1)
      array(0, 1, 5, 4), array(2, 6, 5, 1), array(0, 3, 2, 1)
   );

   $indices = array_flatten($indices) ; // convert to C memory layout

// print_r($indices);

   $v[0][0] = $v[3][0] = $v[4][0] = $v[7][0] = $x0;
   $v[1][0] = $v[2][0] = $v[5][0] = $v[6][0] = $x1;
   $v[0][1] = $v[1][1] = $v[4][1] = $v[5][1] = $y0;
   $v[2][1] = $v[3][1] = $v[6][1] = $v[7][1] = $y1;
   $v[0][2] = $v[1][2] = $v[2][2] = $v[3][2] = $z0;
   $v[4][2] = $v[5][2] = $v[6][2] = $v[7][2] = $z1;

// print_r($v[0]);

   $v = array_flatten($v);  // convert to C memory layout

// print_r($v);

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

$rotate_x = 30;
$rotate_y = 60;

function display()
{
   global $polySmooth;
   global $rotate_x, $rotate_y;
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
      glRotatef ($rotate_x, 1.0, 0.0, 0.0);
      glRotatef ($rotate_y, 0.0, 1.0, 0.0); 
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

$prev_x = 0;
$prev_y = 0;

function mouse($button, $state, $x, $y) {
    global $prev_x, $prev_y;
    $prev_x = $x;
    $prev_y = $y;
}
function motion($x, $y) {
    global $prev_x, $prev_y;
    global $rotate_x,$rotate_y;

//        echo "($x, $y)\n";
    $rotate_y += $x - $prev_x;
    $rotate_x += $y - $prev_y;
    glutPostRedisplay();
    $prev_x = $x;
    $prev_y = $y;
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
glutMouseFunc('mouse');
glutMotionFunc('motion');
glutDisplayFunc ('display');
glutMainLoop();

return 0;

