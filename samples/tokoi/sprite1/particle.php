<?php

class particle {
    static $g = -0.0001;
    static $h = -1.0;
    static $a = 0.5;
    var $p = null;
    var $v = null;

    function __construct($p = null, $v = null) {
        if (is_null($p)) {
            $p = array(0.0, 1.0, 0.0);
        }
        if (is_null($v)) {
            $v = array(
                (rand(0, 1000) / 1000 - 0.5) * 0.005,
                (rand(0, 1000) / 1000) * 0.01,
                (rand(0, 1000) / 1000 - 0.5) * 0.005,
                );
        }
        $this->p = $p;
        $this->v = $v;
    }
    function gravity($g) {
        self::$g = $g;
    }
    function height($h) {
        self::$h = $h;
    }
    function attenuation($a) {
        self::$a = $a;
    }
    function update() {
        $this->p[0] += $this->v[0];
        $this->v[1] += $this->g;
        $this->p[1] += $this->v[1];
        if ($this->p[1] < $this->h) {
            $this->p[1] = $this->h;
            $this->v[1] = - $this->a * $this->v[1];
        }
        $this->p[2] += $this->v[2];
    }
    function getPosition() {
        return $this->p;
    }
}