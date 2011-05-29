<?php

/*	外部変数	*/
$status = 0;//ボタンの状態

/* 各種コールバック関数*/
//ディスプレイ
function display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//マウス(クリック)
function mouse($button, $state, $x, $y)
{
    global $status;
	if($button == GLUT_LEFT_BUTTON && $state == GLUT_DOWN)
	{
		printf("左ボタンを押しました@ (%d,%d)\n",$x,$y);
		$status = 1;
	}else if($button == GLUT_LEFT_BUTTON && $state == GLUT_UP)
	{
		printf("左ボタンを離しました@ (%d,%d)\n",$x,$y);
		$status = 0;
	}
}

//ドラッグ
function dragMotion($x, $y)
{
    global $status;
	if($status == 1){
		printf("DragMotion @ (%d,%d)\n",$x,$y);
	}
}

//パッシブ
function passiveMotion($x, $y)
{
	printf("PassiveMotion @ (%d,%d)\n",$x,$y);
}

/*	メイン関数	*/
glutInit($argv);
glutCreateWindow('Mouse Callback');

//各種コールバック関数の登録
glutDisplayFunc('display');
glutMouseFunc('mouse');
glutMotionFunc('dragMotion');
glutPassiveMotionFunc('passiveMotion');

glClearColor(1.0, 1.0, 1.0, 1.0);

glutMainLoop();

exit (0);
