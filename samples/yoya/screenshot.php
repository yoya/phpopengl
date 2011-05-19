<?php

function screenshot($output_file) {
    $width = glutGet(GLUT_WINDOW_WIDTH);
    $height = glutGet(GLUT_WINDOW_HEIGHT);
    // OpenGL がレンダリングした画像pixel を吸い出す
    // red green blue alpha の順で並ぶ > GL_RGBA
    
    $pixels = array(); // 空配列を渡す
    glReadPixels(0, 0, $width, $height, GL_RGBA, GL_UNSIGNED_BYTE, $pixels);

    // GD でキャンバスを作る
    $im = imagecreatetruecolor($width, $height);
    $i = 0;
    // pixels 配列を R, G, B, A(無視) の順で解釈してイメージを作成
    for ($y = $height ; $y >= 0; $y--) {
    	for ($x = 0; $x < $width ; $x++) {
            $rgb = $pixels[$i];
            if ($rgb < 0) {
                $rgb += 4294967296; // integer => float
            }
            $blue  = $rgb % 0x100 ; $rgb /= 0x100;
            $green = $rgb % 0x100 ; $rgb /= 0x100;
            $red   = $rgb % 0x100 ; $rgb /= 0x100;
            $color = imagecolorallocate($im, $red, $green, $blue);
            imagesetpixel($im, $x, $y, $color); // pixel を埋めていく
            $i ++;
        }
    }
    imagepng($im, $output_file); // PNG ファイルとして保存
    imagedestroy($im);
}
