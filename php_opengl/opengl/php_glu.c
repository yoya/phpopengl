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

/* $Id: php_glu.c,v 1.14 2001/10/12 12:56:18 drbrain Exp $ */

#ifdef PHP_WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#include "php.h"
#include "php_glu.h"
#include "php_opengl.h"
#include "php_convert.h"

int le_quad = 0;
#define le_quad_name "GLUquadric"
int le_nurb = 0;
#define le_nurb_name "GLUnurbs"
int le_tess = 0;
#define le_tess_name "GLUtesselator"

static HashTable *tess_callbacks = NULL;
static HashTable *tess_stack = NULL;
static unsigned int tess_stack_current = -1;

// {{{ string gluerrorstring(long errCode)
PHP_FUNCTION(gluerrorstring)
{
	zval *errCode;
	GLubyte *str;
	ONE_PARAM(errCode);
	convert_to_long(errCode);
	str = (GLubyte *)gluErrorString(Z_LVAL_P(errCode));
	RETURN_STRING(str,1);
}
// }}}


// {{{ string gluerrorunicodestringext(long errCode)
PHP_FUNCTION(gluerrorunicodestringext)
{
	//TODO: ???
	/*zval *errCode;
	wchar_t *str;
	ONE_PARAM(errCode);
	convert_to_long(errCode);
	str = (wchar_t *)gluErrorUnicodeStringEXT(Z_LVAL_P(errCode));
	RETURN_STRING(str,1);*/
}
// }}}


// {{{ string glugetstring(long errCode)
PHP_FUNCTION(glugetstring)
{
	zval *errCode;
	GLubyte *str;
	ONE_PARAM(errCode);
	convert_to_long(errCode);
	str = (GLubyte *)gluGetString(Z_LVAL_P(errCode));
	RETURN_STRING(str,1);
}
// }}}


// {{{ void gluortho2d(double left, double right, double bottom, double top)
PHP_FUNCTION(gluortho2d)
{
	zval *left,*right,*bottom,*top;
	FOUR_PARAM(left,right,bottom,top);
	convert_to_double(left);
	convert_to_double(right);
	convert_to_double(bottom);
	convert_to_double(top);
	gluOrtho2D(Z_DVAL_P(left),Z_DVAL_P(right),Z_DVAL_P(bottom),Z_DVAL_P(top));
}
// }}}


// {{{ void gluperspective(double degree, double ratio, double neara, double fara)
PHP_FUNCTION(gluperspective)
{
	zval *degree,*ratio,*neara,*fara;
	FOUR_PARAM(degree,ratio,neara,fara);
	convert_to_double(degree);
	convert_to_double(ratio);
	convert_to_double(neara);
	convert_to_double(fara);
	gluPerspective(Z_DVAL_P(degree),Z_DVAL_P(ratio),Z_DVAL_P(neara),Z_DVAL_P(fara));
}
// }}}


// {{{ void glupickmatrix(double x, double y, double width, double height, array viewport)
PHP_FUNCTION(glupickmatrix)
{
	zval *x,*y,*width,*height,*viewport;
	GLint *v_viewport;
	FIVE_PARAM(x,y,width,height,viewport);
	convert_to_double(x);
	convert_to_double(y);
	convert_to_double(width);
	convert_to_double(height);
	convert_to_array(viewport);
	v_viewport = php_array_to_int_array(viewport);
	gluPickMatrix(Z_DVAL_P(x),Z_DVAL_P(y),Z_DVAL_P(width),Z_DVAL_P(height),v_viewport);
}
// }}}


// {{{ void gluproject(double objx, double objy, double objz, array modelMatrix, array projMatrix, array viewport, double winx, double winy, double winz)
PHP_FUNCTION(gluproject)
{
	zval *objx,*objy,*objz,*modelMatrix,*projMatrix,*viewport,*winx,*winy,*winz;
	GLdouble *v_model,*v_proj,v_winx,v_winy,v_winz;
	GLint *v_viewport;

	NINE_PARAM(objx,objy,objz,modelMatrix,projMatrix,viewport,winx,winy,winz);
	convert_to_double(objx);
	convert_to_double(objy);
	convert_to_double(objz);
	convert_to_array(modelMatrix);
	convert_to_array(projMatrix);
	convert_to_array(viewport);
	convert_to_double(winx);
	convert_to_double(winy);
	convert_to_double(winz);
	v_model = php_array_to_double_array(modelMatrix);
	v_proj = php_array_to_double_array(projMatrix);
	v_viewport = php_array_to_int_array(viewport);
	gluProject(Z_DVAL_P(objx),Z_DVAL_P(objy),Z_DVAL_P(objz),v_model,v_proj,v_viewport,&v_winx,&v_winy,&v_winz);
	ZVAL_DOUBLE(winx,v_winx);ZVAL_DOUBLE(winy,v_winy);ZVAL_DOUBLE(winz,v_winz);
}
// }}}


// {{{ void glunuproject(double objx, double objy, double objz, array modelMatrix, array projMatrix, array viewport, double winx, double winy, double winz)
PHP_FUNCTION(glunuproject)
{
	zval *objx,*objy,*objz,*modelMatrix,*projMatrix,*viewport,*winx,*winy,*winz;
	GLdouble *v_model,*v_proj,v_winx,v_winy,v_winz;
	GLint *v_viewport;

	NINE_PARAM(objx,objy,objz,modelMatrix,projMatrix,viewport,winx,winy,winz);
	convert_to_double(objx);
	convert_to_double(objy);
	convert_to_double(objz);
	convert_to_array(modelMatrix);
	convert_to_array(projMatrix);
	convert_to_array(viewport);
	convert_to_double(winx);
	convert_to_double(winy);
	convert_to_double(winz);
	v_model = php_array_to_double_array(modelMatrix);
	v_proj = php_array_to_double_array(projMatrix);
	v_viewport = php_array_to_int_array(viewport);
	gluUnProject(Z_DVAL_P(objx),Z_DVAL_P(objy),Z_DVAL_P(objz),v_model,v_proj,v_viewport,&v_winx,&v_winy,&v_winz);
	ZVAL_DOUBLE(winx,v_winx);ZVAL_DOUBLE(winy,v_winy);ZVAL_DOUBLE(winz,v_winz);
}
// }}}


// {{{ int gluscaleimage(long format, long widthin, long heightin, long typein, string datain, long widthout, long heightout, long typeout, string dataout)
PHP_FUNCTION(gluscaleimage)
{
	zval *format,*widthin,*heightin,*typein,*datain,*widthout,*heightout,*typeout,*dataout;
	void *v_dataout;
	int size;
	GLint ret;

	NINE_PARAM(format,widthin,heightin,typein,datain,widthout,heightout,typeout,dataout);
	convert_to_long(format);
	convert_to_long(widthin);
	convert_to_long(heightin);
	convert_to_long(typein);
	convert_to_long(widthout);
	convert_to_long(heightout);
	convert_to_long(typeout);
	convert_to_string(dataout);
	convert_to_string(datain);

	size = Z_LVAL_P(widthout) * Z_LVAL_P(heightout) * gl_pixel_size(Z_LVAL_P(format)) * gl_type_size(Z_LVAL_P(typeout));
	v_dataout = emalloc(size);

	ret = gluScaleImage(Z_LVAL_P(format),Z_LVAL_P(widthin),Z_LVAL_P(heightin),Z_LVAL_P(typein),Z_STRVAL_P(datain),Z_LVAL_P(widthout),Z_LVAL_P(heightout),Z_LVAL_P(typeout),v_dataout);

	ZVAL_STRINGL(dataout, v_dataout, size, 0);
	RETURN_LONG(ret);
}
// }}}


// {{{ void glulookat(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
PHP_FUNCTION(glulookat)
{
	zval *x1,*y1,*z1,*x2,*y2,*z2,*x3,*y3,*z3;
	NINE_PARAM(x1,y1,z1,x2,y2,z2,x3,y3,z3);
	convert_to_double(x1);
	convert_to_double(y1);
	convert_to_double(z1);
	convert_to_double(x2);
	convert_to_double(y2);
	convert_to_double(z2);
	convert_to_double(x3);
	convert_to_double(y3);
	convert_to_double(z3);
	gluLookAt(Z_DVAL_P(x1),Z_DVAL_P(y1),Z_DVAL_P(z1),Z_DVAL_P(x2),Z_DVAL_P(y2),Z_DVAL_P(z2),Z_DVAL_P(x3),Z_DVAL_P(y3),Z_DVAL_P(z3));
}
// }}}


// {{{ long glubuild1dmipmaps(long target, long components, long width, long format, long type, string data)
PHP_FUNCTION(glubuild1dmipmaps)
{
	zval *target,*components,*width,*format,*type,*data;
	int ret;
	SIX_PARAM(target,components,width,format,type,data);
	convert_to_long(target);
	convert_to_long(components);
	convert_to_long(width);
	convert_to_long(format);
	convert_to_long(type);
	convert_to_string(data);
	ret = gluBuild1DMipmaps(Z_LVAL_P(target),Z_LVAL_P(components),Z_LVAL_P(width),Z_LVAL_P(format),Z_LVAL_P(type),Z_STRVAL_P(data));
	RETURN_LONG(ret);
}
// }}}


// {{{ long glubuild2dmipmaps(long target, long components, long width, long height, long format, long type, string data)
PHP_FUNCTION(glubuild2dmipmaps)
{
	zval *target,*components,*width,*height,*format,*type,*data;
	int ret;
	SEVEN_PARAM(target,components,width,height,format,type,data);
	convert_to_long(target);
	convert_to_long(components);
	convert_to_long(width);
	convert_to_long(height);
	convert_to_long(format);
	convert_to_long(type);
	convert_to_string(data);
	ret = gluBuild2DMipmaps(Z_LVAL_P(target),Z_LVAL_P(components),Z_LVAL_P(width),Z_LVAL_P(height),Z_LVAL_P(format),Z_LVAL_P(type),Z_STRVAL_P(data));
	RETURN_LONG(ret);
}
// }}}


// {{{ resource glunewquadric()
PHP_FUNCTION(glunewquadric)
{
	GLUquadric *gluquad = gluNewQuadric();
	ZEND_REGISTER_RESOURCE(return_value, gluquad, le_quad);
}
// }}}


// {{{ void gludeletequadric(resource quad)
PHP_FUNCTION(gludeletequadric)
{
	zval *quad;
	GLUquadric *gluquad;
	ONE_PARAM(quad);
	ZEND_FETCH_RESOURCE(gluquad, GLUquadric *, &quad, -1, le_quad_name, le_quad);
	zend_list_delete(Z_RESVAL_P(quad));
}
// }}}


// {{{ void gluquadricnormals(resource quad, long normals)
PHP_FUNCTION(gluquadricnormals)
{
	zval *quad,*normals;
	GLUquadric *gluquad;

	TWO_PARAM(quad,normals);
	ZEND_FETCH_RESOURCE(gluquad, GLUquadric *, &quad, -1, le_quad_name, le_quad);
	convert_to_long(normals);
	gluQuadricNormals(gluquad,Z_LVAL_P(normals));
}
// }}}


// {{{ void gluquadrictexture(resource quad, boolean textcords)
PHP_FUNCTION(gluquadrictexture)
{
	zval *quad,*textcords;
	GLUquadric *gluquad;

	TWO_PARAM(quad,textcords);
	ZEND_FETCH_RESOURCE(gluquad, GLUquadric *, &quad, -1, le_quad_name, le_quad);
	convert_to_boolean(textcords);
	gluQuadricTexture(gluquad,Z_BVAL_P(textcords));
}
// }}}


// {{{ void gluquadricorientation(resource quad, long orientation)
PHP_FUNCTION(gluquadricorientation)
{
	zval *quad,*orientation;
	GLUquadric *gluquad;

	TWO_PARAM(quad,orientation);
	ZEND_FETCH_RESOURCE(gluquad, GLUquadric *, &quad, -1, le_quad_name, le_quad);
	convert_to_long(orientation);
	gluQuadricOrientation(gluquad,Z_LVAL_P(orientation));
}
// }}}


// {{{ void gluquadricdrawstyle(resource quad, long drawStyle)
PHP_FUNCTION(gluquadricdrawstyle)
{
	zval *quad,*drawStyle;
	GLUquadric *gluquad;

	TWO_PARAM(quad,drawStyle);
	ZEND_FETCH_RESOURCE(gluquad, GLUquadric *, &quad, -1, le_quad_name, le_quad);
	convert_to_long(drawStyle);
	gluQuadricDrawStyle(gluquad,Z_LVAL_P(drawStyle));
}
// }}}


// {{{ void glucylinder(resource quad, double baseRadius, double topRadius, double height, long slices, long stacks)
PHP_FUNCTION(glucylinder)
{
	zval *quad,*baseRadius,*topRadius,*height,*slices,*stacks;
	GLUquadric *gluquad;

	SIX_PARAM(quad,baseRadius,topRadius,height,slices,stacks);
	ZEND_FETCH_RESOURCE(gluquad, GLUquadric *, &quad, -1, le_quad_name, le_quad);
	convert_to_double(baseRadius);
	convert_to_double(topRadius);
	convert_to_double(height);
	convert_to_long(slices);
	convert_to_long(stacks);
	gluCylinder(gluquad,Z_DVAL_P(baseRadius),Z_DVAL_P(topRadius),Z_DVAL_P(height),Z_LVAL_P(slices),Z_LVAL_P(stacks));
}
// }}}


// {{{ void gludisk(resource quad, double innerRadius, double outerRadius, long slices, long stacks)
PHP_FUNCTION(gludisk)
{
	zval *quad,*innerRadius,*outerRadius,*slices,*stacks;
	GLUquadric *gluquad;

	FIVE_PARAM(quad,innerRadius,outerRadius,slices,stacks);
	ZEND_FETCH_RESOURCE(gluquad, GLUquadric *, &quad, -1, le_quad_name, le_quad);
	convert_to_double(innerRadius);
	convert_to_double(outerRadius);
	convert_to_long(slices);
	convert_to_long(stacks);
	gluDisk(gluquad,Z_DVAL_P(innerRadius),Z_DVAL_P(outerRadius),Z_LVAL_P(slices),Z_LVAL_P(stacks));
}
// }}}


// {{{ void glupartialdisk(resource quad, double innerRadius, double outerRadius, long slices, long stacks, double startAngle, double sweepAngle)
PHP_FUNCTION(glupartialdisk)
{
	zval *quad,*innerRadius,*outerRadius,*slices,*stacks,*startAngle,*sweepAngle;
	GLUquadric *gluquad;

	SEVEN_PARAM(quad,innerRadius,outerRadius,slices,stacks,startAngle,sweepAngle);
	ZEND_FETCH_RESOURCE(gluquad, GLUquadric *, &quad, -1, le_quad_name, le_quad);
	convert_to_double(innerRadius);
	convert_to_double(outerRadius);
	convert_to_long(slices);
	convert_to_long(stacks);
	convert_to_double(startAngle);
	convert_to_double(sweepAngle);
	gluPartialDisk(gluquad,Z_DVAL_P(innerRadius),Z_DVAL_P(outerRadius),Z_LVAL_P(slices),Z_LVAL_P(stacks),Z_DVAL_P(startAngle),Z_DVAL_P(sweepAngle));
}
// }}}


// {{{ void glusphere(resource quad, double radius, long slices, long stacks)
PHP_FUNCTION(glusphere)
{
	zval *quad,*radius,*slices,*stacks;
	GLUquadric *gluquad;

	FOUR_PARAM(quad,radius,slices,stacks);
	ZEND_FETCH_RESOURCE(gluquad, GLUquadric *, &quad, -1, le_quad_name, le_quad);
	convert_to_double(radius);
	convert_to_long(slices);
	convert_to_long(stacks);
	gluSphere(gluquad,Z_DVAL_P(radius),Z_LVAL_P(slices),Z_LVAL_P(stacks));
}
// }}}


// {{{ resource glunewtess()
PHP_FUNCTION(glunewtess)
{
	GLUtesselator *tess = gluNewTess();
	ZEND_REGISTER_RESOURCE(return_value, tess, le_tess);
}
// }}}


// {{{ void gludeletetess(resource tess)
PHP_FUNCTION(gludeletetess)
{
	zval *tess;
	GLUtesselator *glutess;
	ONE_PARAM(tess);
	ZEND_FETCH_RESOURCE(glutess, GLUtesselator *, &tess, -1, le_tess_name, le_tess);
	zend_list_delete(Z_RESVAL_P(tess));
}
// }}}

/* GLU Tessellator Callbacks */

void CALLBACK glu_tess_callback_begin(GLenum type)
{
	zval *params[1], *callback_hash;
	TESS_FETCH(callback_hash);

	MAKE_STD_ZVAL(params[0]);
	ZVAL_LONG(params[0], type);
	call_user_callback(Z_ARRVAL_P(callback_hash), GLU_TESS_BEGIN, 1, params);
	zval_dtor(params[0]);
}

// TODO: verify
void CALLBACK glu_tess_callback_begin_data(GLenum type, void *polygon_data)
{
	zval *params[2], *callback_hash;
	TESS_FETCH(callback_hash);

	MAKE_STD_ZVAL(params[0]);
	ZVAL_LONG(params[0], type);
	if ( polygon_data == NULL)
	{
		MAKE_STD_ZVAL(params[1]);
		ZVAL_NULL(params[1]);
	} else {
		params[1] = polygon_data;
	}
	call_user_callback(Z_ARRVAL_P(callback_hash), GLU_TESS_BEGIN_DATA, 2, params);
	zval_dtor(params[0]);
}

// TODO: verify
void CALLBACK glu_tess_callback_edge_flag(GLboolean flag)
{
	zval *params[1], *callback_hash;
	TESS_FETCH(callback_hash);

	MAKE_STD_ZVAL(params[0]);
	ZVAL_LONG(params[0], flag);
	call_user_callback(Z_ARRVAL_P(callback_hash), GLU_TESS_EDGE_FLAG, 1, params);
	zval_dtor(params[0]);
}

// TODO: verify
void CALLBACK glu_tess_callback_edge_flag_data(GLboolean flag, void *polygon_data)
{
	zval *params[2], *callback_hash;
	TESS_FETCH(callback_hash);

	MAKE_STD_ZVAL(params[0]);
	ZVAL_LONG(params[0], flag);
	if (polygon_data == NULL)
	{
		MAKE_STD_ZVAL(params[1]);
		ZVAL_NULL(params[1]);
	} else {
		params[1] = polygon_data;
	}
	call_user_callback(Z_ARRVAL_P(callback_hash), GLU_TESS_EDGE_FLAG_DATA, 2, params);
	zval_dtor(params[0]);
}

void CALLBACK glu_tess_callback_vertex(void *vertex_data)
{
	zval *params[1], *callback_hash;
	TESS_FETCH(callback_hash);

	params[0] = vertex_data;
	call_user_callback(Z_ARRVAL_P(callback_hash), GLU_TESS_VERTEX, 1, params);
}

// TODO: verify
void CALLBACK glu_tess_callback_vertex_data(void *vertex_data, void *polygon_data)
{
	zval *params[2], *callback_hash;
	TESS_FETCH(callback_hash);

	params[0] = vertex_data;
	if ( polygon_data == NULL)
	{
		MAKE_STD_ZVAL(params[1]);
		ZVAL_NULL(params[1]);
	} else {
		params[1] = polygon_data;
	}
	call_user_callback(Z_ARRVAL_P(callback_hash), GLU_TESS_VERTEX_DATA, 2, params);
}

void CALLBACK glu_tess_callback_end()
{
	zval *callback_hash;
	TESS_FETCH(callback_hash);

	call_user_callback(Z_ARRVAL_P(callback_hash), GLU_TESS_END, 0, NULL);
}

// TODO: verify
void CALLBACK glu_tess_callback_end_data(void *polygon_data)
{
	zval *params[1], *callback_hash;
	TESS_FETCH(callback_hash);

	if ( polygon_data == NULL)
	{
		MAKE_STD_ZVAL(params[0]);
		ZVAL_NULL(params[0]);
	} else {
		params[0] = polygon_data;
	}
	call_user_callback(Z_ARRVAL_P(callback_hash), GLU_TESS_END_DATA, 1, params);
}

void CALLBACK glu_tess_callback_combine(GLdouble coords[3], void *vertex_data[4], GLfloat weight[4], void **out_data)
{
	zval *params[4], *callback_hash;
	int i;
	TESS_FETCH(callback_hash);

	MAKE_STD_ZVAL(params[0]);
	array_init(params[0]);
	double_array_to_php_array(coords, 3, params[0]);
	
	MAKE_STD_ZVAL(params[1]);
	array_init(params[1]);
	for (i=0; i<4; i++) {
		zend_hash_next_index_insert(Z_ARRVAL_P(params[1]), &vertex_data[i], sizeof(zval*), NULL);
	}

	MAKE_STD_ZVAL(params[2]);
	array_init(params[2]);
	float_array_to_php_array(weight, 4, params[2]);

	MAKE_STD_ZVAL(params[3]);
	array_init(params[3]);

	call_user_callback(Z_ARRVAL_P(callback_hash), GLU_TESS_COMBINE, 4, params);

	if (Z_TYPE_P(params[3]) != IS_NULL)
		*out_data = params[3];
}

// TODO: verify
void CALLBACK glu_tess_callback_combine_data(GLdouble coords[3], void *vertex_data[4], GLfloat weight[4], void **out_data, void *polygon_data)
{
	zval *params[5], *callback_hash;
	int i;
	TESS_FETCH(callback_hash);

	MAKE_STD_ZVAL(params[0]);
	array_init(params[0]);
	double_array_to_php_array(coords, 3, params[0]);
	
	MAKE_STD_ZVAL(params[1]);
	array_init(params[1]);
	for (i=0; i<4; i++) {
		zend_hash_next_index_insert(Z_ARRVAL_P(params[1]), &vertex_data[i], sizeof(zval*), NULL);
	}

	MAKE_STD_ZVAL(params[2]);
	array_init(params[2]);
	float_array_to_php_array(weight, 4, params[2]);

	MAKE_STD_ZVAL(params[3]);
	array_init(params[3]);

	if ( polygon_data == NULL)
	{
		MAKE_STD_ZVAL(params[4]);
		ZVAL_NULL(params[4]);
	} else {
		params[4] = polygon_data;
	}

	call_user_callback(Z_ARRVAL_P(callback_hash), GLU_TESS_COMBINE_DATA, 5, params);

	if (Z_TYPE_P(params[3]) != IS_NULL)
		*out_data = params[3];
}

void CALLBACK glu_tess_callback_error(GLenum error_number)
{
	zval *params[1], *callback_hash;
	TESS_FETCH(callback_hash);

	MAKE_STD_ZVAL(params[0]);
	ZVAL_LONG(params[0], error_number);
	call_user_callback(Z_ARRVAL_P(callback_hash), GLU_TESS_ERROR, 1, params);
	zval_dtor(params[0]);
}

// TODO: verify
void CALLBACK glu_tess_callback_error_data(GLenum error_number, void *polygon_data)
{
	zval *params[1], *callback_hash;
	TESS_FETCH(callback_hash);

	MAKE_STD_ZVAL(params[0]);
	ZVAL_LONG(params[0], error_number);
	if ( polygon_data == NULL)
	{
		MAKE_STD_ZVAL(params[1]);
		ZVAL_NULL(params[1]);
	} else {
		params[1] = polygon_data;
	}
	call_user_callback(Z_ARRVAL_P(callback_hash), GLU_TESS_ERROR_DATA, 2, params);
	zval_dtor(params[0]);
}

// {{{ void glutesscallback(resource tess, long which, mixed callback)
PHP_FUNCTION(glutesscallback)
{
	zval *tess, *which, *callback, *tess_entry;
	GLUtesselator *glutess;
	int valid_callback_type = 1;

	THREE_PARAM(tess, which, callback);
	ZEND_FETCH_RESOURCE(glutess, GLUtesselator *, &tess, -1, le_tess_name, le_tess);
	convert_to_long(which);
	if (Z_TYPE_P(callback) == IS_NULL) {
		gluTessCallback(glutess, Z_LVAL_P(which), NULL);
		return;
	}
	IS_CALLBACK(callback, 3);

	if (zend_hash_index_find(tess_callbacks, Z_LVAL_P(tess), (void**)&tess_entry) == FAILURE) {
		MAKE_STD_ZVAL(tess_entry);
		array_init(tess_entry);
		zend_hash_index_update(tess_callbacks, Z_LVAL_P(tess), tess_entry, sizeof(zval), NULL);
	}

	switch(Z_LVAL_P(which)) {
		case GLU_TESS_BEGIN:
			gluTessCallback(glutess, Z_LVAL_P(which), (GLvoid (CALLBACK*) ()) &glu_tess_callback_begin);
			break;
		case GLU_TESS_BEGIN_DATA:
			gluTessCallback(glutess, Z_LVAL_P(which), (GLvoid (CALLBACK*) ()) &glu_tess_callback_begin_data);
			break;
		case GLU_TESS_EDGE_FLAG:
			gluTessCallback(glutess, Z_LVAL_P(which), (GLvoid (CALLBACK*) ()) &glu_tess_callback_edge_flag);
			break;
		case GLU_TESS_EDGE_FLAG_DATA:
			gluTessCallback(glutess, Z_LVAL_P(which), (GLvoid (CALLBACK*) ()) &glu_tess_callback_edge_flag_data);
			break;
		case GLU_TESS_VERTEX:
			gluTessCallback(glutess, Z_LVAL_P(which), (GLvoid (CALLBACK*) ()) &glu_tess_callback_vertex);
			break;
		case GLU_TESS_VERTEX_DATA:
			gluTessCallback(glutess, Z_LVAL_P(which), (GLvoid (CALLBACK*) ()) &glu_tess_callback_vertex_data);
			break;
		case GLU_TESS_END:
			gluTessCallback(glutess, Z_LVAL_P(which), (GLvoid (CALLBACK*) ()) &glu_tess_callback_end);
			break;
		case GLU_TESS_END_DATA:
			gluTessCallback(glutess, Z_LVAL_P(which), (GLvoid (CALLBACK*) ()) &glu_tess_callback_end_data);
			break;
		case GLU_TESS_COMBINE:
			gluTessCallback(glutess, Z_LVAL_P(which), (GLvoid (CALLBACK*) ()) &glu_tess_callback_combine);
			break;
		case GLU_TESS_COMBINE_DATA:
			gluTessCallback(glutess, Z_LVAL_P(which), (GLvoid (CALLBACK*) ()) &glu_tess_callback_combine_data);
			break;
		case GLU_TESS_ERROR:
			gluTessCallback(glutess, Z_LVAL_P(which), (GLvoid (CALLBACK*) ()) &glu_tess_callback_error);
			break;
		case GLU_TESS_ERROR_DATA:
			gluTessCallback(glutess, Z_LVAL_P(which), (GLvoid (CALLBACK*) ()) &glu_tess_callback_error_data);
			break;
		default:
			php_error(E_WARNING, "%s() argument 2 unsupported or unknown tess callback '%d'",
					get_active_function_name(TSRMLS_C), Z_LVAL_P(which));
			valid_callback_type = 0;
			return;
	}
	if (valid_callback_type)
	{
		zval_add_ref(&callback);
		zend_hash_index_update(Z_ARRVAL_P(tess_entry), Z_LVAL_P(which), callback, sizeof(zval), NULL);
	}
}


// {{{ void glutessbeginpolygon(resource tess, unknown data)
PHP_FUNCTION(glutessbeginpolygon)
{
	zval *tess,*data;
	GLUtesselator *glutess;

	TWO_PARAM(tess,data);
	ZEND_FETCH_RESOURCE(glutess, GLUtesselator *, &tess, -1, le_tess_name, le_tess);
	if (Z_TYPE_P(data) == IS_NULL) {
		gluTessBeginPolygon(glutess, NULL);
	} else {
		zval_add_ref(&data);
		gluTessBeginPolygon(glutess, data);
	}
	zend_hash_index_update(tess_stack, zend_hash_num_elements(tess_stack), &Z_LVAL_P(tess), sizeof(int), NULL);
	tess_stack_current = Z_LVAL_P(tess);
}
// }}}


// {{{ void glutessbegincontour(resource tess)
PHP_FUNCTION(glutessbegincontour)
{
	zval *tess;
	GLUtesselator *glutess;

	ONE_PARAM(tess);
	ZEND_FETCH_RESOURCE(glutess, GLUtesselator *, &tess, -1, le_tess_name, le_tess);
	gluTessBeginContour(glutess);
}
// }}}


// {{{ void glutessvertex(resource tess, array cords, unknown data)
PHP_FUNCTION(glutessvertex)
{
	zval *tess,*cords,*data;
	GLUtesselator *glutess;
	GLdouble *v_cords;

	THREE_PARAM(tess,cords,data);
	ZEND_FETCH_RESOURCE(glutess, GLUtesselator *, &tess, -1, le_tess_name, le_tess);
	convert_to_array(cords);
	v_cords = php_array_to_double_array(cords);
	zval_add_ref(&data);
	gluTessVertex(glutess,v_cords,data);
}
// }}}


// {{{ void glutessendcontour(resource tess)
PHP_FUNCTION(glutessendcontour)
{
	zval *tess;
	GLUtesselator *glutess;

	ONE_PARAM(tess);
	ZEND_FETCH_RESOURCE(glutess, GLUtesselator *, &tess, -1, le_tess_name, le_tess);
	gluTessEndContour(glutess);
}
// }}}


// {{{ void glutessendpolygon(resource tess)
PHP_FUNCTION(glutessendpolygon)
{
	zval *tess, *stack_value;
	GLUtesselator *glutess;

	ONE_PARAM(tess);
	ZEND_FETCH_RESOURCE(glutess, GLUtesselator *, &tess, -1, le_tess_name, le_tess);
	gluTessEndPolygon(glutess);
	zend_hash_index_del(tess_stack, zend_hash_num_elements(tess_stack)-1);
	if (zend_hash_index_find(tess_stack, zend_hash_num_elements(tess_stack)-1, (void**)&stack_value) == SUCCESS) {
		tess_stack_current = Z_LVAL_P(stack_value);
	} else {
		tess_stack_current = -1;
	}
}
// }}}


// {{{ void glutessproperty(resource tess, long which, double value)
PHP_FUNCTION(glutessproperty)
{
	zval *tess,*which,*value;
	GLUtesselator *glutess;

	THREE_PARAM(tess,which,value);
	ZEND_FETCH_RESOURCE(glutess, GLUtesselator *, &tess, -1, le_tess_name, le_tess);
	convert_to_long(which);
	convert_to_double(value);
	gluTessProperty(glutess,Z_LVAL_P(which),Z_DVAL_P(value));
}
// }}}


// {{{ void glutessnormal(resource tess, double x, double y, double z)
PHP_FUNCTION(glutessnormal)
{
	zval *tess,*x,*y,*z;
	GLUtesselator *glutess;

	FOUR_PARAM(tess,x,y,z);
	ZEND_FETCH_RESOURCE(glutess, GLUtesselator *, &tess, -1, le_tess_name, le_tess);
	convert_to_double(x);
	convert_to_double(y);
	convert_to_double(z);
	gluTessNormal(glutess,Z_DVAL_P(x),Z_DVAL_P(y),Z_DVAL_P(z));
}
// }}}


// {{{ void glugettessproperty(resource tess, long which, double value)
PHP_FUNCTION(glugettessproperty)
{
	zval *tess,*which,*value;
	GLUtesselator *glutess;

	THREE_PARAM(tess,which,value);
	ZEND_FETCH_RESOURCE(glutess, GLUtesselator *, &tess, -1, le_tess_name, le_tess);
	convert_to_long(which);
	convert_to_double(value);
	gluGetTessProperty(glutess,Z_LVAL_P(which),&Z_DVAL_P(value));
}
// }}}


// {{{ resource glunewnurbsrenderer()
PHP_FUNCTION(glunewnurbsrenderer)
{
	GLUnurbs *nurb = gluNewNurbsRenderer();
	ZEND_REGISTER_RESOURCE(return_value, nurb, le_nurb);
}
// }}}


// {{{ void gludeletenurbsrenderer(resource nurb)
PHP_FUNCTION(gludeletenurbsrenderer)
{
	zval *nurb;
	GLUnurbs *glunurb;
	ONE_PARAM(nurb);
	ZEND_FETCH_RESOURCE(glunurb, GLUnurbs *, &nurb, -1, le_nurb_name, le_nurb);
	zend_list_delete(Z_RESVAL_P(nurb));
}
// }}}


// {{{ void glubeginsurface(resource nurb)
PHP_FUNCTION(glubeginsurface)
{
	zval *nurb;
	GLUnurbs *glunurb;

	ONE_PARAM(nurb);
	ZEND_FETCH_RESOURCE(glunurb, GLUnurbs *, &nurb, -1, le_nurb_name, le_nurb);
	gluBeginSurface(glunurb);
}
// }}}


// {{{ void glubegincurve(resource nurb)
PHP_FUNCTION(glubegincurve)
{
	zval *nurb;
	GLUnurbs *glunurb;

	ONE_PARAM(nurb);
	ZEND_FETCH_RESOURCE(glunurb, GLUnurbs *, &nurb, -1, le_nurb_name, le_nurb);
	gluBeginCurve(glunurb);
}
// }}}


// {{{ void gluendcurve(resource nurb)
PHP_FUNCTION(gluendcurve)
{
	zval *nurb;
	GLUnurbs *glunurb;

	ONE_PARAM(nurb);
	ZEND_FETCH_RESOURCE(glunurb, GLUnurbs *, &nurb, -1, le_nurb_name, le_nurb);
	gluEndCurve(glunurb);
}
// }}}


// {{{ void gluendsurface(resource nurb)
PHP_FUNCTION(gluendsurface)
{
	zval *nurb;
	GLUnurbs *glunurb;

	ONE_PARAM(nurb);
	ZEND_FETCH_RESOURCE(glunurb, GLUnurbs *, &nurb, -1, le_nurb_name, le_nurb);
	gluEndSurface(glunurb);
}
// }}}


// {{{ void glubegintrim(resource nurb)
PHP_FUNCTION(glubegintrim)
{
	zval *nurb;
	GLUnurbs *glunurb;

	ONE_PARAM(nurb);
	ZEND_FETCH_RESOURCE(glunurb, GLUnurbs *, &nurb, -1, le_nurb_name, le_nurb);
	gluBeginTrim(glunurb);
}
// }}}


// {{{ void gluendtrim(resource nurb)
PHP_FUNCTION(gluendtrim)
{
	zval *nurb;
	GLUnurbs *glunurb;

	ONE_PARAM(nurb);
	ZEND_FETCH_RESOURCE(glunurb, GLUnurbs *, &nurb, -1, le_nurb_name, le_nurb);
	gluEndTrim(glunurb);
}
// }}}


// {{{ void glupwlcurve(resource nurb, long count, array array, long stride, long type)
PHP_FUNCTION(glupwlcurve)
{
	zval *nurb,*count,*array,*stride,*type;
	GLUnurbs *glunurb;
	float *v_array;

	FIVE_PARAM(nurb,count,array,stride,type);
	ZEND_FETCH_RESOURCE(glunurb, GLUnurbs *, &nurb, -1, le_nurb_name, le_nurb);
	convert_to_long(count);
	convert_to_long(stride);
	convert_to_long(type);
	convert_to_array(array);
	v_array = php_array_to_float_array(array);
	gluPwlCurve(glunurb,Z_LVAL_P(count),v_array,Z_LVAL_P(stride),Z_LVAL_P(type));
}
// }}}


// {{{ void glunurbscurve(resource nurb, long nknots, array knot, long stride, array ctlarray, long order, long type)
PHP_FUNCTION(glunurbscurve)
{
	zval *nurb,*nknots,*knot,*stride,*ctlarray,*order,*type;
	GLUnurbs *glunurb;
	float *v_knot,*v_ctlarray;

	SEVEN_PARAM(nurb,nknots,knot,stride,ctlarray,order,type);
	ZEND_FETCH_RESOURCE(glunurb, GLUnurbs *, &nurb, -1, le_nurb_name, le_nurb);
	convert_to_long(nknots);
	convert_to_long(stride);
	convert_to_long(type);
	convert_to_long(order);
	convert_to_array(knot);
	convert_to_array(ctlarray);
	v_knot = php_array_to_float_array(knot);
	v_ctlarray = php_array_to_float_array(ctlarray);
	gluNurbsCurve(glunurb,Z_LVAL_P(nknots),v_knot,Z_LVAL_P(stride),v_ctlarray,Z_LVAL_P(order),Z_LVAL_P(type));
}
// }}}


// {{{ void glunurbssurface(resource nurb, long sknot_count, array sknot, long tknot_count, array tknot, long s_stride, long t_stride, array ctlarray, long sorder, long torder, long type)
PHP_FUNCTION(glunurbssurface)
{
	zval *nurb,*sknot_count,*sknot,*tknot_count,*tknot,*s_stride,*t_stride,*ctlarray,*sorder,*torder,*type;
	GLUnurbs *glunurb;
	float *v_sknot,*v_ctlarray,*v_tknot;

	ELEVEN_PARAM(nurb,sknot_count,sknot,tknot_count,tknot,s_stride,t_stride,ctlarray,sorder,torder,type);
	ZEND_FETCH_RESOURCE(glunurb, GLUnurbs *, &nurb, -1, le_nurb_name, le_nurb);
	convert_to_long(sknot_count);
	convert_to_long(tknot_count);
	convert_to_long(s_stride);
	convert_to_long(t_stride);
	convert_to_long(sorder);
	convert_to_long(torder);
	convert_to_long(type);
	convert_to_array(sknot);
	convert_to_array(ctlarray);
	convert_to_array(tknot);
	v_sknot = php_array_to_float_array(sknot);
	v_tknot = php_array_to_float_array(tknot);
	v_ctlarray = php_array_to_float_array(ctlarray);
	gluNurbsSurface(glunurb,Z_LVAL_P(sknot_count),v_sknot,Z_LVAL_P(tknot_count),v_tknot,Z_LVAL_P(s_stride),Z_LVAL_P(t_stride),v_ctlarray,Z_LVAL_P(sorder),Z_LVAL_P(torder),Z_LVAL_P(type));
}
// }}}


// {{{ void gluloadsamplingmatrices(resource nurb, array modelMatrix, array projMatrix, array viewport)
PHP_FUNCTION(gluloadsamplingmatrices)
{
	zval *nurb,*modelMatrix,*projMatrix,*viewport;
	GLUnurbs *glunurb;
	float *v_modelMatrix,*v_projMatrix;
	int *v_viewport;

	FOUR_PARAM(nurb,modelMatrix,projMatrix,viewport);
	ZEND_FETCH_RESOURCE(glunurb, GLUnurbs *, &nurb, -1, le_nurb_name, le_nurb);
	convert_to_array(modelMatrix);
	convert_to_array(projMatrix);
	convert_to_array(viewport);
	v_modelMatrix = php_array_to_float_array(modelMatrix);
	v_projMatrix = php_array_to_float_array(projMatrix);
	v_viewport = php_array_to_int_array(viewport);
	gluLoadSamplingMatrices(glunurb,v_modelMatrix,v_projMatrix,v_viewport);
}
// }}}


// {{{ void glunurbsproperty(resource nurb, long property, double value)
PHP_FUNCTION(glunurbsproperty)
{
	zval *nurb,*property,*value;
	GLUnurbs *glunurb;

	THREE_PARAM(nurb,property,value);
	ZEND_FETCH_RESOURCE(glunurb, GLUnurbs *, &nurb, -1, le_nurb_name, le_nurb);
	convert_to_long(property);
	convert_to_double(value);
	gluNurbsProperty(glunurb,Z_LVAL_P(property),(float)Z_DVAL_P(value));
}
// }}}


// {{{ void glugetnurbsproperty(resource nurb, long property, double value)
PHP_FUNCTION(glugetnurbsproperty)
{
	zval *nurb,*property,*value;
	GLUnurbs *glunurb;
	float f_property;

	THREE_PARAM(nurb,property,value);
	ZEND_FETCH_RESOURCE(glunurb, GLUnurbs *, &nurb, -1, le_nurb_name, le_nurb);
	convert_to_long(property);
	convert_to_double(value);
	gluGetNurbsProperty(glunurb,Z_LVAL_P(property),&f_property);
	ZVAL_DOUBLE(value, f_property);
}
// }}}


void gluquadric_destructor(zend_rsrc_list_entry *quad TSRMLS_DC)
{
	gluDeleteQuadric(quad->ptr);
}

void glunurbs_destructor(zend_rsrc_list_entry *nurbs TSRMLS_DC)
{
	gluDeleteNurbsRenderer(nurbs->ptr);
}

void glutesselator_destructor(zend_rsrc_list_entry *tesselator TSRMLS_DC)
{
	gluDeleteTess(tesselator->ptr);
}

int glu_init(int module_number)
{
	// GLU_1_2
	REGISTER_LONG_CONSTANT("GLU_VERSION_1_1", GLU_VERSION_1_1 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_VERSION_1_2", GLU_VERSION_1_2 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_INVALID_ENUM", GLU_INVALID_ENUM , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_INVALID_VALUE", GLU_INVALID_VALUE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_OUT_OF_MEMORY", GLU_OUT_OF_MEMORY , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_VERSION", GLU_VERSION , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_EXTENSIONS", GLU_EXTENSIONS , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TRUE", GLU_TRUE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_FALSE", GLU_FALSE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_SMOOTH", GLU_SMOOTH , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_FLAT", GLU_FLAT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NONE", GLU_NONE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_POINT", GLU_POINT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_LINE", GLU_LINE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_FILL", GLU_FILL , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_SILHOUETTE", GLU_SILHOUETTE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_OUTSIDE", GLU_OUTSIDE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_INSIDE", GLU_INSIDE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_ERROR", GLU_ERROR , CONST_CS | CONST_PERSISTENT);
	// TODO: Fix really huge constant
	//REGISTER_LONG_CONSTANT("GLU_TESS_MAX_COORD", GLU_TESS_MAX_COORD , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_WINDING_RULE", GLU_TESS_WINDING_RULE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_BOUNDARY_ONLY", GLU_TESS_BOUNDARY_ONLY , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_TOLERANCE", GLU_TESS_TOLERANCE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_WINDING_ODD", GLU_TESS_WINDING_ODD , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_WINDING_NONZERO", GLU_TESS_WINDING_NONZERO , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_WINDING_POSITIVE", GLU_TESS_WINDING_POSITIVE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_WINDING_NEGATIVE", GLU_TESS_WINDING_NEGATIVE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_WINDING_ABS_GEQ_TWO", GLU_TESS_WINDING_ABS_GEQ_TWO , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_BEGIN", GLU_TESS_BEGIN , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_VERTEX", GLU_TESS_VERTEX , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_END", GLU_TESS_END , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_ERROR", GLU_TESS_ERROR , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_EDGE_FLAG", GLU_TESS_EDGE_FLAG , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_COMBINE", GLU_TESS_COMBINE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_BEGIN_DATA", GLU_TESS_BEGIN_DATA , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_VERTEX_DATA", GLU_TESS_VERTEX_DATA , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_END_DATA", GLU_TESS_END_DATA , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_ERROR_DATA", GLU_TESS_ERROR_DATA , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_EDGE_FLAG_DATA", GLU_TESS_EDGE_FLAG_DATA , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_COMBINE_DATA", GLU_TESS_COMBINE_DATA , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_ERROR1", GLU_TESS_ERROR1 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_ERROR2", GLU_TESS_ERROR2 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_ERROR3", GLU_TESS_ERROR3 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_ERROR4", GLU_TESS_ERROR4 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_ERROR5", GLU_TESS_ERROR5 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_ERROR6", GLU_TESS_ERROR6 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_ERROR7", GLU_TESS_ERROR7 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_ERROR8", GLU_TESS_ERROR8 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_MISSING_BEGIN_POLYGON", GLU_TESS_MISSING_BEGIN_POLYGON , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_MISSING_BEGIN_CONTOUR", GLU_TESS_MISSING_BEGIN_CONTOUR , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_MISSING_END_POLYGON", GLU_TESS_MISSING_END_POLYGON , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_MISSING_END_CONTOUR", GLU_TESS_MISSING_END_CONTOUR , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_COORD_TOO_LARGE", GLU_TESS_COORD_TOO_LARGE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_TESS_NEED_COMBINE_CALLBACK", GLU_TESS_NEED_COMBINE_CALLBACK , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_AUTO_LOAD_MATRIX", GLU_AUTO_LOAD_MATRIX , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_CULLING", GLU_CULLING , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_SAMPLING_TOLERANCE", GLU_SAMPLING_TOLERANCE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_DISPLAY_MODE", GLU_DISPLAY_MODE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_PARAMETRIC_TOLERANCE", GLU_PARAMETRIC_TOLERANCE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_SAMPLING_METHOD", GLU_SAMPLING_METHOD , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_U_STEP", GLU_U_STEP , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_V_STEP", GLU_V_STEP , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_PATH_LENGTH", GLU_PATH_LENGTH , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_PARAMETRIC_ERROR", GLU_PARAMETRIC_ERROR , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_DOMAIN_DISTANCE", GLU_DOMAIN_DISTANCE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_MAP1_TRIM_2", GLU_MAP1_TRIM_2 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_MAP1_TRIM_3", GLU_MAP1_TRIM_3 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_OUTLINE_POLYGON", GLU_OUTLINE_POLYGON , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_OUTLINE_PATCH", GLU_OUTLINE_PATCH , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR1", GLU_NURBS_ERROR1 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR2", GLU_NURBS_ERROR2 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR3", GLU_NURBS_ERROR3 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR4", GLU_NURBS_ERROR4 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR5", GLU_NURBS_ERROR5 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR6", GLU_NURBS_ERROR6 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR7", GLU_NURBS_ERROR7 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR8", GLU_NURBS_ERROR8 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR9", GLU_NURBS_ERROR9 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR10", GLU_NURBS_ERROR10 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR11", GLU_NURBS_ERROR11 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR12", GLU_NURBS_ERROR12 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR13", GLU_NURBS_ERROR13 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR14", GLU_NURBS_ERROR14 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR15", GLU_NURBS_ERROR15 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR16", GLU_NURBS_ERROR16 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR17", GLU_NURBS_ERROR17 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR18", GLU_NURBS_ERROR18 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR19", GLU_NURBS_ERROR19 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR20", GLU_NURBS_ERROR20 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR21", GLU_NURBS_ERROR21 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR22", GLU_NURBS_ERROR22 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR23", GLU_NURBS_ERROR23 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR24", GLU_NURBS_ERROR24 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR25", GLU_NURBS_ERROR25 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR26", GLU_NURBS_ERROR26 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR27", GLU_NURBS_ERROR27 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR28", GLU_NURBS_ERROR28 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR29", GLU_NURBS_ERROR29 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR30", GLU_NURBS_ERROR30 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR31", GLU_NURBS_ERROR31 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR32", GLU_NURBS_ERROR32 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR33", GLU_NURBS_ERROR33 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR34", GLU_NURBS_ERROR34 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR35", GLU_NURBS_ERROR35 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR36", GLU_NURBS_ERROR36 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR37", GLU_NURBS_ERROR37 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_CW", GLU_CW , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_CCW", GLU_CCW , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_INTERIOR", GLU_INTERIOR , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_EXTERIOR", GLU_EXTERIOR , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_UNKNOWN", GLU_UNKNOWN , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_BEGIN", GLU_BEGIN , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_VERTEX", GLU_VERTEX , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_END", GLU_END , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_EDGE_FLAG", GLU_EDGE_FLAG , CONST_CS | CONST_PERSISTENT);
	
#ifdef PHP_WIN32
	REGISTER_LONG_CONSTANT("GLU_INCOMPATIBLE_GL_VERSION", GLU_INCOMPATIBLE_GL_VERSION , CONST_CS | CONST_PERSISTENT);
#endif
	
#ifdef GLU_VERSION_1_3
	REGISTER_LONG_CONSTANT("GLU_EXT_object_space_tess", GLU_EXT_object_space_tess , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_EXT_nurbs_tessellator", GLU_EXT_nurbs_tessellator , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_VERSION_1_3", GLU_VERSION_1_3 , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_INVALID_OPERATION", GLU_INVALID_OPERATION , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_ERROR", GLU_NURBS_ERROR , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_BEGIN", GLU_NURBS_BEGIN , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_BEGIN_EXT", GLU_NURBS_BEGIN_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_VERTEX", GLU_NURBS_VERTEX , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_VERTEX_EXT", GLU_NURBS_VERTEX_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_NORMAL", GLU_NURBS_NORMAL , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_NORMAL_EXT", GLU_NURBS_NORMAL_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_COLOR", GLU_NURBS_COLOR , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_COLOR_EXT", GLU_NURBS_COLOR_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_TEXTURE_COORD", GLU_NURBS_TEXTURE_COORD , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_TEX_COORD_EXT", GLU_NURBS_TEX_COORD_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_END", GLU_NURBS_END , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_END_EXT", GLU_NURBS_END_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_BEGIN_DATA", GLU_NURBS_BEGIN_DATA , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_BEGIN_DATA_EXT", GLU_NURBS_BEGIN_DATA_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_VERTEX_DATA", GLU_NURBS_VERTEX_DATA , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_VERTEX_DATA_EXT", GLU_NURBS_VERTEX_DATA_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_NORMAL_DATA", GLU_NURBS_NORMAL_DATA , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_NORMAL_DATA_EXT", GLU_NURBS_NORMAL_DATA_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_COLOR_DATA", GLU_NURBS_COLOR_DATA , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_COLOR_DATA_EXT", GLU_NURBS_COLOR_DATA_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_TEXTURE_COORD_DATA", GLU_NURBS_TEXTURE_COORD_DATA , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_TEX_COORD_DATA_EXT", GLU_NURBS_TEX_COORD_DATA_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_END_DATA", GLU_NURBS_END_DATA , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_END_DATA_EXT", GLU_NURBS_END_DATA_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_MODE", GLU_NURBS_MODE , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_MODE_EXT", GLU_NURBS_MODE_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_TESSELLATOR", GLU_NURBS_TESSELLATOR , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_TESSELLATOR_EXT", GLU_NURBS_TESSELLATOR_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_RENDERER", GLU_NURBS_RENDERER , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_NURBS_RENDERER_EXT", GLU_NURBS_RENDERER_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_OBJECT_PARAMETRIC_ERROR", GLU_OBJECT_PARAMETRIC_ERROR , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_OBJECT_PARAMETRIC_ERROR_EXT", GLU_OBJECT_PARAMETRIC_ERROR_EXT , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_OBJECT_PATH_LENGTH", GLU_OBJECT_PATH_LENGTH , CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GLU_OBJECT_PATH_LENGTH_EXT", GLU_OBJECT_PATH_LENGTH_EXT , CONST_CS | CONST_PERSISTENT);
#endif

	return SUCCESS;
}

int glu_request_init(int module_number)
{
    	TSRMLS_FETCH();

	tess_callbacks = (HashTable*)emalloc(sizeof(HashTable));
	zend_hash_init(tess_callbacks, 0, NULL, ZVAL_PTR_DTOR, 0);
	tess_stack = (HashTable*)emalloc(sizeof(HashTable));
	zend_hash_init(tess_stack, 0, NULL, NULL, 0);

	le_quad = zend_register_list_destructors_ex(gluquadric_destructor, NULL, le_quad_name, module_number);
	le_nurb = zend_register_list_destructors_ex(glunurbs_destructor, NULL, le_nurb_name, module_number);
	le_tess = zend_register_list_destructors_ex(glutesselator_destructor, NULL, le_tess_name, module_number);
        
    	return SUCCESS;
}
    int glu_request_shutdown()
{
	zend_hash_destroy(tess_callbacks);
	efree(tess_callbacks);
        tess_callbacks = NULL;
	zend_hash_destroy(tess_stack);
	efree(tess_stack);
        tess_stack = NULL;
	return SUCCESS;
}
