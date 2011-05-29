<?php

glutInit($argv);
glutCreateWindow('Check OpenGL');

printf("%s\n",glGetString(GL_EXTENSIONS));

exit (0);

