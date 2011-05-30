<?php

//光源(環境光､拡散光､鏡面光､位置)
$lightAmb = array(0.0, 0.0, 0.0, 1.0);
$lightDiff = array(1.0, 1.0, 1.0, 1.0);
$lightSpec = array(1.0, 1.0, 1.0, 1.0);
$lightPos = array(1.0, 1.0, 1.0, 0.0);//平行光源

//材質(環境光､拡散光､鏡面光､鏡面指数)
$pearlAmb = array(0.25,0.20725,0.20725,1.0);
$pearlDiff = array(1.0,0.829,0.829,1.0);
$pearlSpec = array(0.296648,0.296648,0.296648,1.0);
$pearlShin =  10.24;

//gluオブジェクト
$quadric = null;

//--------- GLUquadricオブジェクトの描画----------------//
function DrawQuadricObj()
{
    global $quadric;
	//シリンダ
	gluQuadricOrientation($quadric,GLU_OUTSIDE);
	gluCylinder($quadric, 0.5, 0.3, 1.0, 20, 15);

	//上面
	glPushMatrix();
		glTranslatef(0.0,0.0,1.0);//高さ分平行移動
		gluDisk($quadric, 0, 0.3, 20,10);
	glPopMatrix();

	//底面(法線の向きを逆にする)
	gluQuadricOrientation($quadric,GLU_INSIDE);
	gluDisk($quadric, 0, 0.5, 20,10);
}


//--------- 各種コールバック関数-------//
function display()
{
    global $lightPos;
    global $pearlAmb, $pearlDiff, $pearlSpec, $pearlShin;
    
	static $angle = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	gluLookAt(0.0, 1.5, 4,0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	//光源の位置設定
	glLightfv(GL_LIGHT0,GL_POSITION,$lightPos);

	//材質設定
	glPushMatrix();
	glRotatef($angle, 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,$pearlAmb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,$pearlDiff);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,$pearlSpec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,$pearlShin);
	DrawQuadricObj();//描画
	glPopMatrix();

	glutSwapBuffers();
	if (++$angle >= 360) { $angle = 0; }
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
    global $lightAmb, $lightDiff, $lightSpec;
    global $quadric;

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
	glEnable(GL_NORMALIZE);

	//GLUquadricオブジェクトの設定
	$quadric =  gluNewQuadric(); //オブジェクト生成
	gluQuadricDrawStyle($quadric, GLU_FILL); //ポリゴン描画
	gluQuadricNormals($quadric, GLU_SMOOTH); //シェーディング
}

//---------- メイン関数-------------//
glutInit($argv);
glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
glutInitWindowSize(640,480);
glutCreateWindow('GLUquadric Object');

//コールバック関数登録
glutDisplayFunc('display');
glutReshapeFunc('reshape');
glutIdleFunc('idle');

otherInit();//その他設定

glutMainLoop();
	
//不要になったら破棄
gluDeleteQuadric($quadric);//本来は終了処理部分で記述する
exit (0);
