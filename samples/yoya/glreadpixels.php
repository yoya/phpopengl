<?php

// glReadPixels のサンプル。

require_once('HSVtoRGB.php');
require_once('screenshot.php');

$width = 300;
$height = 300;
$button_list = array();


function display() {
    global $button_list;

    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
        
    foreach ($button_list as $button) {
        glPushMatrix();
        $color = array($button['red'], $button['green'], $button['blue'], 0.9);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, $color);
        glTranslatef($button['x'], $button['y'] , 1.0);
        glutSolidSphere(0.15, 16, 10);
        glPopMatrix();
    }
    glDisable(GL_BLEND);
    glFlush();

    screenshot("output.png");
}

function init() {
    global $argv;
    global $width, $height;
    glutInit($argv);
    glutInitWindowSize($width, $height);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
        
    glutCreateWindow("Color Button");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    $lit_amb = array(1.0, 1.0, 1.0, 0.0); /* 環境光の強さ */
    $lit_dif = array(1.0, 1.0, 1.0, 0.0); /* 拡散光の強さ */
    $lit_spc = array(1.0, 1.0, 1.0, 0.0); /* 鏡面反射光の強さ */
    $lit_pos = array(-5.0, 5.0, -8.0, 1.0);  /* 光源の位置 */
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, $lit_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, $lit_dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, $lit_spc);
    glLightfv(GL_LIGHT0, GL_POSITION, $lit_pos);
    
    /* ライトを有効にする */
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    glDisable(GL_DEPTH_TEST);

    glBlendFunc(GL_ONE, GL_ONE);
}

$button_list = array();
for ($idx = 0; $idx < 12 ; $idx++) {
    $button['x'] = -0.25 + 0.22 * ($idx % 3);
    $button['y'] = -0.35 + 0.22 * floor(($idx / 3));
    $hsv = array((360 / 12) * $idx, 160, 255);
    $rgb = HSVtoRGB($hsv);
    $button['red']   = $rgb[0] / 256;
    $button['green'] = $rgb[1] / 256;
    $button['blue']  = $rgb[2] / 256;
    $button_list[] = $button;
}

init();

display();

exit(0);
