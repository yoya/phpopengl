<?php

// 光源、質感、光沢を入れて陰をつけてみた。

require_once('HSVtoRGB.php');

$button_list = array();

function display() {
    global $button_list;
    glClear(GL_COLOR_BUFFER_BIT);

    foreach ($button_list as $button) {
        glPushMatrix();
	// 球の色
        $color = array($button['red'], $button['green'], $button['blue'], 0.9);
	// (環境光とか光源の種類には色々あるけどその内の)
	// 拡散光の色を指定する。
        glMaterialfv(GL_FRONT, GL_DIFFUSE, $color);
        glTranslatef($button['x'], $button['y'] , 1.0);
        glutSolidSphere(0.1, 16, 10);
        glPopMatrix();
    }

    glFlush();
}

function keyboard($key, $x, $y) {
    if ($key == chr(0x1b)) { // Esc key
        exit(0);
    }
}

function init() {
    global $argv;
    glutInit($argv);
    
    glutInitWindowSize(400, 400);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
        
    glutCreateWindow("Color Button");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    $lit_amb = array(1.0, 1.0, 1.0, 0.0); /* 環境光の強さ */
    $lit_dif = array(1.0, 1.0, 1.0, 0.0); /* 拡散光の強さ */
    $lit_spc = array(1.0, 1.0, 1.0, 0.0); /* 鏡面反射光の強さ */
    $lit_pos = array(-5.0, 5.0, -8.0, 1.0); /* 光源の位置 左上後 */
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, $lit_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, $lit_dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, $lit_spc);
    glLightfv(GL_LIGHT0, GL_POSITION, $lit_pos);
    
    /* ライトを有効にする */
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

}

for ($i = 0 ; $i < 12 ; $i++) {
    $button_list[] = array();
}

foreach ($button_list as $idx => &$button) {
    $button['x'] = -0.25 + 0.22 * ($idx % 3);
    $button['y'] = -0.35 + 0.22 * floor(($idx / 3));
    $hsv = array((360 / 12) * $idx, 160, 255);
    $rgb = HSVtoRGB($hsv);
    $button['red']   = $rgb[0] / 256;
    $button['green'] = $rgb[1] / 256;
    $button['blue']  = $rgb[2] / 256;
}

init();

glutDisplayFunc('display');
glutKeyboardFunc('keyboard');
glutMainLoop();
