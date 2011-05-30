<?php

//三角形の描画
function drawTriangle()
{
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.5, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glEnd();
}

//-------- XYZ軸の描画 -------------//
function drawXYZ()
{
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);//X軸:赤
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(200.0, 0.0, 0.0);

		glColor3f(0.0, 1.0, 0.0);//Y軸:緑
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 200.0, 0.0);

		glColor3f(0.0, 0.0, 1.0);//Z軸:青
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 200.0);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);//色のリセット
}


//-------- 各種コールバック関数------------//
function display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glPushMatrix();
		glTranslatef(1.0, 0.0, 0.0);
		glRotatef(45.0, 0.0, 1.0, 0.0);
		glColor3f(1.0, 1.0, 0.0);//黄色
		drawTriangle();
	glPopMatrix();

	glPushMatrix();
		glRotatef(45.0, 0.0, 1.0, 0.0);
		glTranslatef(1.0, 0.0, 0.0);
		glColor3f(0.7, 0.7, 0.7);//灰色
		drawTriangle();
	glPopMatrix();

	drawXYZ();//XYZ軸の描画
	glFinish();
}

function reshape($w, $h)
{
	glViewport(0,0,$w,$h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0,$w/$h, 0.1, 200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0, 2.5, 4,0, 0.0, 0.0, 0.0, 1.0, 0.0);	
}

//-------- その他各種設定-----------------//
function otherInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
}

//--------- メイン関数------------//
glutInit($argv);
glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
glutInitWindowSize(640,480);
glutCreateWindow('Depth and Affine');
	
//コールバック関数登録
glutDisplayFunc('display');
glutReshapeFunc('reshape');

otherInit();//その他設定

glutMainLoop();

exit (0);


