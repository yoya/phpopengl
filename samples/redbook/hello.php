<?php

function display() {
    glClear(GL_COLOR_BUFFER_BIT);
    // white polygon drawing
    glColor3d(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.25, 0.25, 0.0);
        glVertex3f(0.75, 0.25, 0.0);
        glVertex3f(0.75, 0.75, 0.0);
        glVertex3f(0.25, 0.75, 0.0);
    glEnd();
    // start buffered process;
    glFlush();
}

function init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // camera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.);
}

glutInit($argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(250, 250);
glutInitWindowPosition(100, 100);
glutCreateWindow('Hello');
init();
glutDisplayFunc('display');
glutMainLoop();

exit (0);
