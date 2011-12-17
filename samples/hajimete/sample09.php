<?php

/* 各種コールバック関数*/
//ディスプレイ
function display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//キーボード処理(押したとき)
function keyboard($key, $x, $y)
{
	if (is_string($key)) { $key = ord($key); }
	if($key == 27)//[ESC]キーのとき
	{
		echo 'Exit...'.PHP_EOL;
		exit(0);
	}

	printf("%c が押されました@ (%d, %d)\n",$key,$x,$y);
}

//キーボード処理(離したとき)
function keyboardUp($key, $x, $y)
{
	if (is_string($key)) { $key = ord($key); }
	printf("%c が離されました@ (%d, %d)\n",$key,$x,$y);
}

//特殊キーを押したとき
function specialKey($key, $x, $y)
{
	if (is_string($key)) { $key = ord($key); }
	switch($key)
	{
	case GLUT_KEY_LEFT:
		printf("[←]が押されました@ (%d, %d)\n",$x,$y);
		break;

	case GLUT_KEY_UP:
		printf("[↑]が押されました@ (%d, %d)\n",$x,$y);
		break;

	case GLUT_KEY_RIGHT:
		printf("[→]が押されました@ (%d, %d)\n",$x,$y);
		break;

	case GLUT_KEY_DOWN:
		printf("[↓]が押されました@ (%d, %d)\n",$x,$y);
		break;
	}
}

//特殊キーを離したとき
function specialUpKey($key, $x, $y)
{
	if (is_string($key)) { $key = ord($key); }
	switch($key)
	{
	case GLUT_KEY_LEFT:
		printf("[←]が離れました@ (%d, %d)\n",$x,$y);
		break;

	case GLUT_KEY_UP:
		printf("[↑]が離れました@ (%d, %d)\n",$x,$y);
		break;

	case GLUT_KEY_RIGHT:
		printf("[→]が離れました@ (%d, %d)\n",$x,$y);
		break;

	case GLUT_KEY_DOWN:
		printf("[↓]が離れました@ (%d, %d)\n",$x,$y);
		break;
	}
}

/*	メイン関数	*/
glutInit($argv);
glutCreateWindow('Key Callback');

//各種コールバック関数の登録
glutDisplayFunc('display');

//通常キー
glutKeyboardFunc('keyboard');
glutKeyboardUpFunc('keyboardUp');
//特殊キー
glutSpecialFunc('specialKey');
glutSpecialUpFunc('specialUpKey');
glutIgnoreKeyRepeat(GL_TRUE);//キー・リピート無視

glClearColor(1.0, 1.0, 1.0, 1.0);

glutMainLoop();

exit (0);

