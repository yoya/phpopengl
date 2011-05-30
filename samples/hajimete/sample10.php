<?php

//--------- コールバック関数--------------//
function display()
{
	glClear(GL_COLOR_BUFFER_BIT);//カラー・バッファをクリア
	glColor3f(1.0, 0.0, 0.0);

	glutWireTeapot(1.0);//ティーポットを描画

	glFlush();//命令の実行
}

function reshape($w, $h)
{
	glViewport(0, 0, $w, $h);  //ビューポートの設定

	glMatrixMode(GL_PROJECTION);//射影行列の設定
	glLoadIdentity();
	gluPerspective(30.0, $w / $h, 1.0, 100.0); 

	glMatrixMode(GL_MODELVIEW);//モデルビュー行列の設定
	glLoadIdentity();
	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


//---------- メイン関数-------------//
glutInit($argv);

glutInitWindowSize(640,480);
glutInitDisplayMode(GLUT_RGBA); //ディスプレイ・モード
glutCreateWindow('Hello 3D Graphics');
		
glutDisplayFunc('display');//コールバック関数登録
glutReshapeFunc('reshape');

/* カラー・バッファの初期値*/
glClearColor(1.0, 1.0, 1.0, 1.0);

glutMainLoop();

exit (0);

