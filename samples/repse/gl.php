<?php

/*
  http://repse.blogspot.com/2008/07/linuxwindows_14.html
*/


function  display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3d(1.0, 0.0, 0.0); /* red */
    glVertex2d(-0.9, -0.9);
    glColor3d(0.0, 1.0, 0.0); /* green */
    glVertex2d(-0.9,  0.9);
    glColor3d(0.0, 0.0, 1.0); /* blue */
    glVertex2d( 0.9,  0.9);
    glColor3d(1.0, 1.0, 0.0); /* yellow */
    glVertex2d( 0.9, -0.9);
    glEnd();
    glFlush();
}

glutInit($argv);
glutInitDisplayMode(GLUT_RGBA);
glutCreateWindow($argv[0]);
glutDisplayFunc('display');
glClearColor(0.0, 0.0, 0.0, 0.0);
glutMainLoop();

exit (0);
