<?php

//------------ 各種材質パラメータ--------------//
//光源(環境光､拡散光､鏡面光､位置)
$lightAmb = array(0.0, 0.0, 0.0, 1.0 );
$lightDiff = array(1.0, 1.0, 1.0, 1.0);
$lightSpec = array(1.0, 1.0, 1.0, 1.0);
$lightPos = array(1.0, 1.0, 1.0, 0.0);//平行光源

//材質(環境光､拡散光､鏡面光､鏡面指数)
$goldAmb = array( 0.24725, 0.1995, 0.0745, 1.0 );
$goldDiff = array( 0.75164, 0.60648, 0.22648, 1.0 );
$goldSpec = array( 0.628281, 0.555802, 0.366065, 1.0 );
$goldShin =  51.2 ;

//--------- 各種コールバック関数-------//
function display()
{
    global $lightPos;
	global $goldAmb;
	global $goldDiff;
	global $goldSpec;
	global $goldShin;
	static $angle = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	gluLookAt(0.0, 3.0, 5,0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	//光源の位置設定
	glLightfv(GL_LIGHT0,GL_POSITION,$lightPos);

	//材質設定と描画
	glPushMatrix();
	glRotatef($angle, 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,$goldAmb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,$goldDiff);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,$goldSpec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,$goldShin);
	glutSolidTeapot(1.0);//描画
	glPopMatrix();

	glutSwapBuffers();
	if(++$angle >= 360){ $angle = 0;}
}

function reshape($w, $h)
{
	glViewport(0,0,$w,$h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0,$w/$h, 0.1, 200.0);

	glMatrixMode(GL_MODELVIEW);
}

function idle()
{
	glutPostRedisplay();
}

//--------- その他各種設定-----------//
function otherInit()
{
	global $lightAmb;
	global $lightDiff;
	global $lightSpec;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);

	//光源設定(環境､拡散､鏡面のみ)
	glLightfv(GL_LIGHT0,GL_AMBIENT,$lightAmb);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,$lightDiff);
	glLightfv(GL_LIGHT0,GL_SPECULAR,$lightSpec);

	//光源とライティング有効化
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

//---------- メイン関数-------------//
glutInit($argv);
glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
glutInitWindowSize(640,480);
glutCreateWindow('Light and Material');

//コールバック関数登録
glutDisplayFunc('display');
glutReshapeFunc('reshape');
glutIdleFunc('idle');

otherInit();//その他設定

glutMainLoop();

exit (0);

