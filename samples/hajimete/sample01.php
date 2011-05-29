<?php


glutInit($argv);
glutCreateWindow("Check OpenGL");

//o—Í‚·‚é
printf("Vendor:%s\n",glGetString(GL_VENDOR));
printf("GPU:%s\n",glGetString(GL_RENDERER));
printf("OpenGL ver. %s\n",glGetString(GL_VERSION));

exit (0);

