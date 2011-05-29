<?php

function display()
{
	glClear(GL_COLOR_BUFFER_BIT);//カラー・バッファを初期化
	
	glFlush();//命令の実行
}


glutInit($argv);

glutInitWindowSize(640,480);
glutInitDisplayMode(GLUT_RGBA); //ディスプレイ・モード
glutCreateWindow('Color Buffer');
		
glutDisplayFunc('display');//コールバック関数登録

/* カラー・バッファの初期値*/
glClearColor(1.0, 1.0, 1.0, 1.0);

glutMainLoop();

exit (0);
