<?php

$spin = 0.0;

function init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

function display() {
    global $spin;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotatef($spin, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glRectf(-25.0, -25.0, 25.0, 25.0);
    glPopMatrix();
    glutSwapBuffers();
}

function spinDisplay() {
    global $spin;
    $spin = $spin + 2.0;
    if ($spin > 360.0) {
        $spin = $spin - 360.0;
    }
    glutPostRedisplay();
}

function reshape ($w, $h) {
    glViewport(0, 0, $w, $h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

function mouse($button, $state, $x, $y) {
    switch ($button){
    case GLUT_LEFT_BUTTON:
        if ($state == GLUT_DOWN) {
            glutIdleFunc('spinDisplay');
        }
        break;
    case GLUT_MIDDLE_BUTTON:
        if ($state == GLUT_DOWN) {
            glutIdleFunc(NULL);
        }
        break;
    default:
        break;
    }
}

// main

glutInit($argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(250, 250);
glutInitWindowPosition(100, 100);
glutCreateWindow($argv[0]);
init();
glutDisplayFunc('display');
glutReshapeFunc('reshape');
glutMouseFunc('mouse');
glutMainLoop();

exit (0);
