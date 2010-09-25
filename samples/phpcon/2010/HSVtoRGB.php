<?php

/**
 * HSV配列 を RGB配列 へ変換します
 *
 * @param   array   $arr            array(h, s, v) ※h は 0～360の数値、s/v は 0～255 の数値
 * @return  array   array(r, g, b) ※ r/g/b は 0～255 の数値
 http://d.hatena.ne.jp/ja9/20100831/1283181870
 */

function HSVtoRGB($arr)
{
    $r = 0; // 0..255
    $g = 0; // 0..255
    $b = 0; // 0..255

    while ($arr[0] < 0) {
      $arr[0] += 360;
    }

    $arr[0] = $arr[0] % 360;

    // 特別な場合
    if ($arr[1] == 0) {
        // S = 0.0
        // → RGB は V に等しい
        return array(
            round($arr[2]),
            round($arr[2]),
            round($arr[2]),
        );
    }

    $arr[1] = $arr[1] / 255;


    // Hi = floor(H/60) mod 6
    $i = floor($arr[0] / 60) % 6;
    // f = H/60 - Hi
    $f = ($arr[0] / 60) - $i;

    // p = V (1 - S)
    $p = $arr[2] * (1 - $arr[1]);
    // q = V (1 - fS)
    $q = $arr[2] * (1 - $f * $arr[1]);
    // t = V (1 - (1 - f) S)
    $t = $arr[2] * (1 - (1 - $f) * $arr[1]);

    switch ($i) {
        case 0 :
            // R = V, G = t, B = p
            $r = $arr[2];
            $g = $t;
            $b = $p;
            break;
        case 1 :
            // R = q, G = V, B = p
            $r = $q;
            $g = $arr[2];
            $b = $p;
            break;
        case 2 :
            // R = p, G = V, B = t
            $r = $p;
            $g = $arr[2];
            $b = $t;
            break;
        case 3 :
            // R = p, G = q, B = V
            $r = $p;
            $g = $q;
            $b = $arr[2];
            break;
        case 4 :
            // R = t, G = p, B = V
            $r = $t;
            $g = $p;
            $b = $arr[2];
            break;
        case 5 :
            // R = V, G = p, B = q
            $r = $arr[2];
            $g = $p;
            $b = $q;
            break;
    }

    return array(
        round($r), // r
        round($g), // g
        round($b), // b
    );
}
