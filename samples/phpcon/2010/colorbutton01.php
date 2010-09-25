<?php

// 球体を表示してみた

require_once('HSVtoRGB.php');

$button_list = array();

function display() {
    global $button_list;

    glClear(GL_COLOR_BUFFER_BIT);

    foreach ($button_list as $button) {
        glPushMatrix();
	glColor4f($button['red'], $button['green'], $button['blue'], 1);
        glTranslatef($button['x'], $button['y'] , 0); // 位置指定
        glutSolidSphere(0.1, 16, 10); // 球体を表示するAPI
        glPopMatrix();
    }

    glFlush();
}

// ESC キーで終了できるように
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
}

for ($i = 0 ; $i < 12 ; $i++) {
    $button_list[] = array();
}

foreach ($button_list as $idx => &$button) {
    // テンキーの配置を作る
    $button['x'] = -0.25 + 0.22 * ($idx % 3);
    $button['y'] = -0.35 + 0.22 * floor(($idx / 3));
    // 色相を12分割して割当
    $hsv = array((360 / 12) * $idx, 160, 255);
    $rgb = HSVtoRGB($hsv);
    $button['red']   = $rgb[0] / 256;
    $button['green'] = $rgb[1] / 256;
    $button['blue']  = $rgb[2] / 256;
}

init();

glutDisplayFunc('display'); // ウィンドウが現れた時の処理
glutKeyboardFunc('keyboard'); // キーボードが押された時の処理

// 後は OpenGL に身を委ねる。もう処理は戻ってこない。。。
// イベントハンドリングの王道ですね。

glutMainLoop();
