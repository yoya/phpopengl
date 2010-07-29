/* 
 +----------------------------------------------------------------------------+
 | php_opengl - The PHP OpenGL bindings                                       |
 +----------------------------------------------------------------------------+
 | Copyright (c) 2001 Brad Lafountain                                         |
 +----------------------------------------------------------------------------+
 | This file is part of php_opengl.                                           |
 |                                                                            |
 | php_opengl is free software; you can redistribute it and/or modify         |
 | it under the terms of the GNU General Public License as published by       |
 | the Free Software Foundation; either version 2 of the License, or          |
 | (at your option) any later version.                                        |
 |                                                                            |
 | php_opengl is distributed in the hope that it will be useful,              |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of             |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              |
 | GNU General Public License for more details.                               |
 |                                                                            |
 | You should have received a copy of the GNU General Public License          |
 | along with php_opengl; if not, write to the Free Software                  |
 | Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA  |
 +----------------------------------------------------------------------------+
 | Authors: Markus Fischer <mfischer@guru.josefine.at>                        |
 +----------------------------------------------------------------------------+
*/

/* $Id: php_osmesa.h,v 1.2 2001/10/15 11:07:00 drbrain Exp $ */

#ifndef PHP_OSMESA_H
#define PHP_OSMESA_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#ifdef PHP_OPENGL_OSMESA

#include <GL/osmesa.h>

#define NOT_IMPLEMENTED() \
	php_error(E_WARNING, "%s() not yet implemented", get_active_function_name(TSRMLS_C));

typedef struct {
	OSMesaContext ctx;
	GLubyte *buffer;
	int width, height, size;
} php_osmesacontext;

/* {{{ OSMesa API */
PHP_FUNCTION(osmesacreatecontext);
PHP_FUNCTION(osmesacreatecontextext);
PHP_FUNCTION(osmesadestroycontext);
PHP_FUNCTION(osmesamakecurrent);
PHP_FUNCTION(osmesagetcurrentcontext);
PHP_FUNCTION(osmesapixelstore);
PHP_FUNCTION(osmesagetintegerv);
PHP_FUNCTION(osmesagetdepthbuffer);
PHP_FUNCTION(osmesagetcolorbuffer);

// Only for php_osmesa
PHP_FUNCTION(osmesagetbuffer);
/* }}} */

#define OSMESA_BUFFER_RAW 0
#define OSMESA_BUFFER_TGA 1

void osmesacontext_destructor(zend_rsrc_list_entry *osmesacontext TSRMLS_DC);

int osmesa_init(int module_number);
int osmesa_request_shutdown();

#endif /* PHP_OPENGL_OSMESA */
#endif /* PHP_OSMESA_H */
