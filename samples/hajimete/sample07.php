<?php

function display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	echo 'display callback'.PHP_EOL;
	glFlush();
}

function reshape($width, $height)
{
	printf("(w, h) = (%d,%d)\n",$width,$height);
}

//---------- メイン関数------------//
glutInit($argv);

glutInitWindowSize(400,400);
glutInitDisplayMode(GLUT_RGBA); 
glutCreateWindow('CallBack Test');
		
/* コールバック関数の登録*/
glutDisplayFunc('display');
glutReshapeFunc('reshape');

glClearColor(1.0, 1.0, 1.0, 1.0);

glutMainLoop();

exit (0);
