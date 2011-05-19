<?php

function screenshot($output_file) {
    $width = glutGet(GLUT_WINDOW_WIDTH);
    $height = glutGet(GLUT_WINDOW_HEIGHT);
    // OpenGL がレンダリングした画像pixel を吸い出す
    // red green blue alpha の順で並ぶ > GL_RGBA
    glReadPixels(0, 0, $width, $height, GL_RGBA, GL_UNSIGNED_BYTE, $pixels);

    // GD でキャンバスを作る
    $im = imagecreatetruecolor($width, $height);
    $i = 0;
    // pixels 配列を R, G, B, A(無視) の順で解釈してイメージを作成
    for ($y = $height -1 ; $y >= 0; $y--) {
    	for ($x = 0; $x < $width ; $x++) {
            $p = $pixels[$i];
            $alpha = 127 - $p['alpha'] / 2;
            $color = imagecolorallocatealpha($im, $p['red'], $p['green'], $p['blue'], $alpha);
            imagesetpixel($im, $x, $y, $color); // pixel を埋めていく
            $i ++;
        }
    }
    imagepng($im, $output_file); // PNG ファイルとして保存
    imagedestroy($im);
}
