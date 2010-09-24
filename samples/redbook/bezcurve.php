<?php
$ctrlpoints = array(-4.0, -4.0, 0.0 ,-2.0, 4.0, 0.0,2.0, -4.0, 0.0,4.0, 4.0, 0.0);

function init()
{
   global $ctrlpoints;
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, $ctrlpoints);
   glEnable(GL_MAP1_VERTEX_3);
}

function display()
{
   global $ctrlpoints;
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_LINE_STRIP);
      for ($i = 0; $i <= 30; $i++) 
         glEvalCoord1f($i/30.0);
   glEnd();
   glPointSize(5.0);
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POINTS);
      for ($i = 0; $i < 4; $i++)
      {
      	 $array = array_slice($ctrlpoints,$i * 3,3);
         glVertex3fv($array);
      }
   glEnd();
   glFlush();
}

function reshape($w,$h)
{
   glViewport(0, 0, $w, $h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if ($w <= $h)
      glOrtho(-5.0, 5.0, -5.0*$h/$w, 
               5.0*$h/$w, -5.0, 5.0);
   else
      glOrtho(-5.0*$w/$h, 
               5.0*$w/$h, -5.0, 5.0, -5.0, 5.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

function keyboard($key, $x, $y)
{
   switch (ord($key)) {
      case 27:
         exit(0);
         break;
   }
}

glutInit($argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (500, 500);
glutInitWindowPosition (100, 100);
glutCreateWindow($argv[0]);
init ();
glutDisplayFunc('display');
glutReshapeFunc('reshape');
glutKeyboardFunc('keyboard');
glutMainLoop();
