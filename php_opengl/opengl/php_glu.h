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
 | Authors: Brad Lafountain <rodif_bl@yahoo.com>                              |
 +----------------------------------------------------------------------------+
*/

/* $Id: php_glu.h,v 1.8 2001/10/12 12:56:18 drbrain Exp $ */

#ifndef PHP_GLU_H
#define PHP_GLU_H

#ifndef CALLBACK
#define CALLBACK
#endif

PHP_FUNCTION(gluerrorstring);
PHP_FUNCTION(gluerrorunicodestringext);
PHP_FUNCTION(glugetstring);
PHP_FUNCTION(gluortho2d);
PHP_FUNCTION(gluperspective);
PHP_FUNCTION(glupickmatrix);
PHP_FUNCTION(gluproject);
PHP_FUNCTION(glunuproject);
PHP_FUNCTION(gluscaleimage);
PHP_FUNCTION(glulookat);
PHP_FUNCTION(glubuild1dmipmaps);
PHP_FUNCTION(glubuild2dmipmaps);
PHP_FUNCTION(glunewquadric);
PHP_FUNCTION(gludeletequadric);
PHP_FUNCTION(gluquadricnormals);
PHP_FUNCTION(gluquadrictexture);
PHP_FUNCTION(gluquadricorientation);
PHP_FUNCTION(gluquadricdrawstyle);
PHP_FUNCTION(glucylinder);
PHP_FUNCTION(gludisk);
PHP_FUNCTION(glupartialdisk);
PHP_FUNCTION(glusphere);
PHP_FUNCTION(glunewtess);
PHP_FUNCTION(gludeletetess);
PHP_FUNCTION(glutessbeginpolygon);
PHP_FUNCTION(glutessbegincontour);
PHP_FUNCTION(glutessvertex);
PHP_FUNCTION(glutessendcontour);
PHP_FUNCTION(glutessendpolygon);
PHP_FUNCTION(glutessproperty);
PHP_FUNCTION(glutessnormal);
PHP_FUNCTION(glugettessproperty);
PHP_FUNCTION(glunewnurbsrenderer);
PHP_FUNCTION(gludeletenurbsrenderer);
PHP_FUNCTION(glubeginsurface);
PHP_FUNCTION(glubegincurve);
PHP_FUNCTION(gluendcurve);
PHP_FUNCTION(gluendsurface);
PHP_FUNCTION(glubegintrim);
PHP_FUNCTION(gluendtrim);
PHP_FUNCTION(glupwlcurve);
PHP_FUNCTION(glunurbscurve);
PHP_FUNCTION(glunurbssurface);
PHP_FUNCTION(gluloadsamplingmatrices);
PHP_FUNCTION(glunurbsproperty);
PHP_FUNCTION(glugetnurbsproperty);
PHP_FUNCTION(glutesscallback);

void gluquadric_destructor(zend_rsrc_list_entry *quad TSRMLS_DC);
void glunurbs_destructor(zend_rsrc_list_entry *nurbs TSRMLS_DC);
void glutesselator_destructor(zend_rsrc_list_entry *tesselator TSRMLS_DC);

int glu_init(int module_number);
int glu_request_init(int module_number);
int glu_request_shutdown();

/* GLU Tessellator Callbacks */
void CALLBACK glu_tess_callback_begin(GLenum type);
void CALLBACK glu_tess_callback_begin_data(GLenum type, void *polygon_data);
void CALLBACK glu_tess_callback_edge_flag(GLboolean flag);
void CALLBACK glu_tess_callback_edge_flag_data(GLboolean flag, void *polygon_data);
void CALLBACK glu_tess_callback_vertex(void *vertex_data);
void CALLBACK glu_tess_callback_vertex_data(void *vertex_data, void *polygon_data);
void CALLBACK glu_tess_callback_end(void);
void CALLBACK glu_tess_callback_end_data(void *polygon_data);
void CALLBACK glu_tess_callback_combine(GLdouble coords[3], void *vertex_data[4], GLfloat weight[4], void **out_data);
void CALLBACK glu_tess_callback_combine_data(GLdouble coords[3], void *vertex_data[4], GLfloat weight[4], void **out_data, void *polygon_data);
void CALLBACK glu_tess_callback_error(GLenum error_number);
void CALLBACK glu_tess_callback_error_data(GLenum error_number, void *polygon_data);

#define TESS_FETCH(callback_hash) \
	TSRMLS_FETCH(); \
	if (zend_hash_index_find(tess_callbacks, tess_stack_current, (void**)&callback_hash) == FAILURE) { \
		php_error(E_WARNING, "%s() invalid current tessellation object", \
			get_active_function_name(TSRMLS_C)); \
		return; \
	}

#endif
