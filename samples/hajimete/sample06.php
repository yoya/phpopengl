<?php

function display()
{
	glClear(GL_COLOR_BUFFER_BIT);//カラー・バッファをクリア

	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);//赤色
		glVertex2f(0.0, 0.5);

		glColor3f(0.0, 1.0, 0.0);//緑色
		glVertex2f(-0.5, -0.5);	

		glColor3f(0.0, 0.0, 1.0);//青色
		glVertex2f(0.5, -0.5);
	glEnd();

	glFlush();//命令の実行
}

glutInit($argv);

glutInitWindowSize(400,400);
glutInitDisplayMode(GLUT_RGBA); //ディスプレイモード
glutCreateWindow('Draw Triangle');
	
glutDisplayFunc('display');//コールバック関数登録

/* カラー・バッファの初期値*/
glClearColor(1.0, 1.0, 1.0, 1.0);

glutMainLoop();

exit (0);
