<?php

/*
 *  http://d.hatena.ne.jp/kotsubu-chan/200510
 */

$vertices = array(
      -1,-1, 1,  -1,1, 1,  1,1, 1,  1,-1, 1,
      -1,-1,-1,  -1,1,-1,  1,1,-1,  1,-1,-1,
    );
$colors = array(
    0, 0, 0,  1, 0, 0,  1, 1, 0,  0, 1, 0,
        0, 0, 1,  1, 0, 1,  1, 1, 1,  0, 1, 1,
    );

$indices = array(
        0, 3, 2, 1,  2, 3, 7, 6,  0, 4, 7, 3,
        1, 2, 6, 5,  4, 5, 6, 7,  0, 1, 5, 4,
    );
$angle = 0.0;

## ----------------------------------------
function init() {
    glClearColor (0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
}

function display() {
    global $angle;
    global $colors;
    global $vertices;
    global $indices;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef($angle, 1, 1, 1);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, $colors);
    glVertexPointer(3, GL_FLOAT, 0, $vertices);
  
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, $indices); // OUT!!
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glutSwapBuffers();
}

function title() {
    global $argv;
    return $argv[0];
}

function keyboard($key, $x, $y) {
    global $angle;
    if ($key == "\x1b") {   # escape
        exit();
    }
    if ($key == '<') {
        $angle -= 10;
            print "<<< $angle";
        glutPostRedisplay();
    }
    if ($key == '>') {
        $angle += 10;
        print "<<< $angle";
        glutPostRedisplay();
    }
}

function ex_() {
    global $argv;
    glutInit($argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(title());
    init();
    glutDisplayFunc('display');
    glutKeyboardFunc('keyboard');
    glutMainLoop();
}

ex_();
