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

/* $Id: php_opengl.h,v 1.6 2001/10/08 20:55:15 drbrain Exp $ */

#ifndef PHP_OPENGL_H
#define PHP_OPENGL_H

extern zend_module_entry opengl_module_entry;
#define opengl_module_ptr &opengl_module_entry
#define phpext_opengl_ptr opengl_module_ptr

/* Module */

PHP_MINIT_FUNCTION(opengl);
PHP_MSHUTDOWN_FUNCTION(opengl);
PHP_RINIT_FUNCTION(opengl);
PHP_RSHUTDOWN_FUNCTION(opengl);
PHP_MINFO_FUNCTION(opengl);

/* Functions */

PHP_FUNCTION(glaccum);
PHP_FUNCTION(glalphafunc);
PHP_FUNCTION(glaretexturesresident);
PHP_FUNCTION(glarrayelement);
PHP_FUNCTION(glbegin);
PHP_FUNCTION(glbindtexture);
PHP_FUNCTION(glbitmap);
PHP_FUNCTION(glblendfunc);
PHP_FUNCTION(glcalllist);
PHP_FUNCTION(glcalllists);
PHP_FUNCTION(glclear);
PHP_FUNCTION(glclearaccum);
PHP_FUNCTION(glclearcolor);
PHP_FUNCTION(glcleardepth);
PHP_FUNCTION(glclearindex);
PHP_FUNCTION(glclearstencil);
PHP_FUNCTION(glclipplane);
PHP_FUNCTION(glcolor3b);
PHP_FUNCTION(glcolor3bv);
PHP_FUNCTION(glcolor3d);
PHP_FUNCTION(glcolor3dv);
PHP_FUNCTION(glcolor3f);
PHP_FUNCTION(glcolor3fv);
PHP_FUNCTION(glcolor3i);
PHP_FUNCTION(glcolor3iv);
PHP_FUNCTION(glcolor3s);
PHP_FUNCTION(glcolor3sv);
PHP_FUNCTION(glcolor3ub);
PHP_FUNCTION(glcolor3ubv);
PHP_FUNCTION(glcolor3ui);
PHP_FUNCTION(glcolor3uiv);
PHP_FUNCTION(glcolor3us);
PHP_FUNCTION(glcolor3usv);
PHP_FUNCTION(glcolor4b);
PHP_FUNCTION(glcolor4bv);
PHP_FUNCTION(glcolor4d);
PHP_FUNCTION(glcolor4dv);
PHP_FUNCTION(glcolor4f);
PHP_FUNCTION(glcolor4fv);
PHP_FUNCTION(glcolor4i);
PHP_FUNCTION(glcolor4iv);
PHP_FUNCTION(glcolor4s);
PHP_FUNCTION(glcolor4sv);
PHP_FUNCTION(glcolor4ub);
PHP_FUNCTION(glcolor4ubv);
PHP_FUNCTION(glcolor4ui);
PHP_FUNCTION(glcolor4uiv);
PHP_FUNCTION(glcolor4us);
PHP_FUNCTION(glcolor4usv);
PHP_FUNCTION(glcolormask);
PHP_FUNCTION(glcolormaterial);
PHP_FUNCTION(glcolorpointer);
PHP_FUNCTION(glcopypixels);
PHP_FUNCTION(glcopyteximage1d);
PHP_FUNCTION(glcopyteximage2d);
PHP_FUNCTION(glcopytexsubimage1d);
PHP_FUNCTION(glcopytexsubimage2d);
PHP_FUNCTION(glcullface);
PHP_FUNCTION(gldeletelists);
PHP_FUNCTION(gldeletetextures);
PHP_FUNCTION(gldepthfunc);
PHP_FUNCTION(gldepthmask);
PHP_FUNCTION(gldepthrange);
PHP_FUNCTION(gldisable);
PHP_FUNCTION(gldisableclientstate);
PHP_FUNCTION(gldrawarrays);
PHP_FUNCTION(gldrawbuffer);
PHP_FUNCTION(gldrawelements);
PHP_FUNCTION(gldrawpixels);
PHP_FUNCTION(gledgeflag);
PHP_FUNCTION(gledgeflagpointer);
PHP_FUNCTION(gledgeflagv);
PHP_FUNCTION(glenable);
PHP_FUNCTION(glenableclientstate);
PHP_FUNCTION(glend);
PHP_FUNCTION(glendlist);
PHP_FUNCTION(glevalcoord1d);
PHP_FUNCTION(glevalcoord1dv);
PHP_FUNCTION(glevalcoord1f);
PHP_FUNCTION(glevalcoord1fv);
PHP_FUNCTION(glevalcoord2d);
PHP_FUNCTION(glevalcoord2dv);
PHP_FUNCTION(glevalcoord2f);
PHP_FUNCTION(glevalcoord2fv);
PHP_FUNCTION(glevalmesh1);
PHP_FUNCTION(glevalmesh2);
PHP_FUNCTION(glevalpoint1);
PHP_FUNCTION(glevalpoint2);
PHP_FUNCTION(glfeedbackbuffer);
PHP_FUNCTION(glfinish);
PHP_FUNCTION(glflush);
PHP_FUNCTION(glfogf);
PHP_FUNCTION(glfogfv);
PHP_FUNCTION(glfogi);
PHP_FUNCTION(glfogiv);
PHP_FUNCTION(glfrontface);
PHP_FUNCTION(glfrustum);
PHP_FUNCTION(glgenlists);
PHP_FUNCTION(glgentextures);
PHP_FUNCTION(glgetbooleanv);
PHP_FUNCTION(glgetclipplane);
PHP_FUNCTION(glgetdoublev);
PHP_FUNCTION(glgeterror);
PHP_FUNCTION(glgetfloatv);
PHP_FUNCTION(glgetintegerv);
PHP_FUNCTION(glgetlightfv);
PHP_FUNCTION(glgetlightiv);
PHP_FUNCTION(glgetmapdv);
PHP_FUNCTION(glgetmapfv);
PHP_FUNCTION(glgetmapiv);
PHP_FUNCTION(glgetmaterialfv);
PHP_FUNCTION(glgetmaterialiv);
PHP_FUNCTION(glgetpixelmapfv);
PHP_FUNCTION(glgetpixelmapuiv);
PHP_FUNCTION(glgetpixelmapusv);
PHP_FUNCTION(glgetpointerv);
PHP_FUNCTION(glgetpolygonstipple);
PHP_FUNCTION(glgetstring);
PHP_FUNCTION(glgettexenvfv);
PHP_FUNCTION(glgettexenviv);
PHP_FUNCTION(glgettexgendv);
PHP_FUNCTION(glgettexgenfv);
PHP_FUNCTION(glgettexgeniv);
PHP_FUNCTION(glgetteximage);
PHP_FUNCTION(glgettexlevelparameterfv);
PHP_FUNCTION(glgettexlevelparameteriv);
PHP_FUNCTION(glgettexparameterfv);
PHP_FUNCTION(glgettexparameteriv);
PHP_FUNCTION(glhint);
PHP_FUNCTION(glindexmask);
PHP_FUNCTION(glindexpointer);
PHP_FUNCTION(glindexd);
PHP_FUNCTION(glindexdv);
PHP_FUNCTION(glindexf);
PHP_FUNCTION(glindexfv);
PHP_FUNCTION(glindexi);
PHP_FUNCTION(glindexiv);
PHP_FUNCTION(glindexs);
PHP_FUNCTION(glindexsv);
PHP_FUNCTION(glindexub);
PHP_FUNCTION(glindexubv);
PHP_FUNCTION(glinitnames);
PHP_FUNCTION(glinterleavedarrays);
PHP_FUNCTION(glisenabled);
PHP_FUNCTION(glislist);
PHP_FUNCTION(glistexture);
PHP_FUNCTION(gllightmodelf);
PHP_FUNCTION(gllightmodelfv);
PHP_FUNCTION(gllightmodeli);
PHP_FUNCTION(gllightmodeliv);
PHP_FUNCTION(gllightf);
PHP_FUNCTION(gllightfv);
PHP_FUNCTION(gllighti);
PHP_FUNCTION(gllightiv);
PHP_FUNCTION(gllinestipple);
PHP_FUNCTION(gllinewidth);
PHP_FUNCTION(gllistbase);
PHP_FUNCTION(glloadidentity);
PHP_FUNCTION(glloadmatrixd);
PHP_FUNCTION(glloadmatrixf);
PHP_FUNCTION(glloadname);
PHP_FUNCTION(gllogicop);
PHP_FUNCTION(glmap1d);
PHP_FUNCTION(glmap1f);
PHP_FUNCTION(glmap2d);
PHP_FUNCTION(glmap2f);
PHP_FUNCTION(glmapgrid1d);
PHP_FUNCTION(glmapgrid1f);
PHP_FUNCTION(glmapgrid2d);
PHP_FUNCTION(glmapgrid2f);
PHP_FUNCTION(glmaterialf);
PHP_FUNCTION(glmaterialfv);
PHP_FUNCTION(glmateriali);
PHP_FUNCTION(glmaterialiv);
PHP_FUNCTION(glmatrixmode);
PHP_FUNCTION(glmultmatrixd);
PHP_FUNCTION(glmultmatrixf);
PHP_FUNCTION(glnewlist);
PHP_FUNCTION(glnormal3b);
PHP_FUNCTION(glnormal3bv);
PHP_FUNCTION(glnormal3d);
PHP_FUNCTION(glnormal3dv);
PHP_FUNCTION(glnormal3f);
PHP_FUNCTION(glnormal3fv);
PHP_FUNCTION(glnormal3i);
PHP_FUNCTION(glnormal3iv);
PHP_FUNCTION(glnormal3s);
PHP_FUNCTION(glnormal3sv);
PHP_FUNCTION(glnormalpointer);
PHP_FUNCTION(glortho);
PHP_FUNCTION(glpassthrough);
PHP_FUNCTION(glpixelmapfv);
PHP_FUNCTION(glpixelmapuiv);
PHP_FUNCTION(glpixelmapusv);
PHP_FUNCTION(glpixelstoref);
PHP_FUNCTION(glpixelstorei);
PHP_FUNCTION(glpixeltransferf);
PHP_FUNCTION(glpixeltransferi);
PHP_FUNCTION(glpixelzoom);
PHP_FUNCTION(glpointsize);
PHP_FUNCTION(glPointParameterfv);
PHP_FUNCTION(glpolygonmode);
PHP_FUNCTION(glpolygonoffset);
PHP_FUNCTION(glpolygonstipple);
PHP_FUNCTION(glpopattrib);
PHP_FUNCTION(glpopclientattrib);
PHP_FUNCTION(glpopmatrix);
PHP_FUNCTION(glpopname);
PHP_FUNCTION(glprioritizetextures);
PHP_FUNCTION(glpushattrib);
PHP_FUNCTION(glpushclientattrib);
PHP_FUNCTION(glpushmatrix);
PHP_FUNCTION(glpushname);
PHP_FUNCTION(glrasterpos2d);
PHP_FUNCTION(glrasterpos2dv);
PHP_FUNCTION(glrasterpos2f);
PHP_FUNCTION(glrasterpos2fv);
PHP_FUNCTION(glrasterpos2i);
PHP_FUNCTION(glrasterpos2iv);
PHP_FUNCTION(glrasterpos2s);
PHP_FUNCTION(glrasterpos2sv);
PHP_FUNCTION(glrasterpos3d);
PHP_FUNCTION(glrasterpos3dv);
PHP_FUNCTION(glrasterpos3f);
PHP_FUNCTION(glrasterpos3fv);
PHP_FUNCTION(glrasterpos3i);
PHP_FUNCTION(glrasterpos3iv);
PHP_FUNCTION(glrasterpos3s);
PHP_FUNCTION(glrasterpos3sv);
PHP_FUNCTION(glrasterpos4d);
PHP_FUNCTION(glrasterpos4dv);
PHP_FUNCTION(glrasterpos4f);
PHP_FUNCTION(glrasterpos4fv);
PHP_FUNCTION(glrasterpos4i);
PHP_FUNCTION(glrasterpos4iv);
PHP_FUNCTION(glrasterpos4s);
PHP_FUNCTION(glrasterpos4sv);
PHP_FUNCTION(glreadbuffer);
PHP_FUNCTION(glreadpixels);
PHP_FUNCTION(glreadpixels_yoya);
PHP_FUNCTION(glrectd);
PHP_FUNCTION(glrectdv);
PHP_FUNCTION(glrectf);
PHP_FUNCTION(glrectfv);
PHP_FUNCTION(glrecti);
PHP_FUNCTION(glrectiv);
PHP_FUNCTION(glrects);
PHP_FUNCTION(glrectsv);
PHP_FUNCTION(glrendermode);
PHP_FUNCTION(glrotated);
PHP_FUNCTION(glrotatef);
PHP_FUNCTION(glscaled);
PHP_FUNCTION(glscalef);
PHP_FUNCTION(glscissor);
PHP_FUNCTION(glselectbuffer);
PHP_FUNCTION(glshademodel);
PHP_FUNCTION(glstencilfunc);
PHP_FUNCTION(glstencilmask);
PHP_FUNCTION(glstencilop);
PHP_FUNCTION(gltexcoord1d);
PHP_FUNCTION(gltexcoord1dv);
PHP_FUNCTION(gltexcoord1f);
PHP_FUNCTION(gltexcoord1fv);
PHP_FUNCTION(gltexcoord1i);
PHP_FUNCTION(gltexcoord1iv);
PHP_FUNCTION(gltexcoord1s);
PHP_FUNCTION(gltexcoord1sv);
PHP_FUNCTION(gltexcoord2d);
PHP_FUNCTION(gltexcoord2dv);
PHP_FUNCTION(gltexcoord2f);
PHP_FUNCTION(gltexcoord2fv);
PHP_FUNCTION(gltexcoord2i);
PHP_FUNCTION(gltexcoord2iv);
PHP_FUNCTION(gltexcoord2s);
PHP_FUNCTION(gltexcoord2sv);
PHP_FUNCTION(gltexcoord3d);
PHP_FUNCTION(gltexcoord3dv);
PHP_FUNCTION(gltexcoord3f);
PHP_FUNCTION(gltexcoord3fv);
PHP_FUNCTION(gltexcoord3i);
PHP_FUNCTION(gltexcoord3iv);
PHP_FUNCTION(gltexcoord3s);
PHP_FUNCTION(gltexcoord3sv);
PHP_FUNCTION(gltexcoord4d);
PHP_FUNCTION(gltexcoord4dv);
PHP_FUNCTION(gltexcoord4f);
PHP_FUNCTION(gltexcoord4fv);
PHP_FUNCTION(gltexcoord4i);
PHP_FUNCTION(gltexcoord4iv);
PHP_FUNCTION(gltexcoord4s);
PHP_FUNCTION(gltexcoord4sv);
PHP_FUNCTION(gltexcoordpointer);
PHP_FUNCTION(gltexenvf);
PHP_FUNCTION(gltexenvfv);
PHP_FUNCTION(gltexenvi);
PHP_FUNCTION(gltexenviv);
PHP_FUNCTION(gltexgend);
PHP_FUNCTION(gltexgendv);
PHP_FUNCTION(gltexgenf);
PHP_FUNCTION(gltexgenfv);
PHP_FUNCTION(gltexgeni);
PHP_FUNCTION(gltexgeniv);
PHP_FUNCTION(glteximage1d);
PHP_FUNCTION(glteximage2d);
PHP_FUNCTION(gltexparameterf);
PHP_FUNCTION(gltexparameterfv);
PHP_FUNCTION(gltexparameteri);
PHP_FUNCTION(gltexparameteriv);
PHP_FUNCTION(gltexsubimage1d);
PHP_FUNCTION(gltexsubimage2d);
PHP_FUNCTION(gltranslated);
PHP_FUNCTION(gltranslatef);
PHP_FUNCTION(glvertex2d);
PHP_FUNCTION(glvertex2dv);
PHP_FUNCTION(glvertex2f);
PHP_FUNCTION(glvertex2fv);
PHP_FUNCTION(glvertex2i);
PHP_FUNCTION(glvertex2iv);
PHP_FUNCTION(glvertex2s);
PHP_FUNCTION(glvertex2sv);
PHP_FUNCTION(glvertex3d);
PHP_FUNCTION(glvertex3dv);
PHP_FUNCTION(glvertex3f);
PHP_FUNCTION(glvertex3fv);
PHP_FUNCTION(glvertex3i);
PHP_FUNCTION(glvertex3iv);
PHP_FUNCTION(glvertex3s);
PHP_FUNCTION(glvertex3sv);
PHP_FUNCTION(glvertex4d);
PHP_FUNCTION(glvertex4dv);
PHP_FUNCTION(glvertex4f);
PHP_FUNCTION(glvertex4fv);
PHP_FUNCTION(glvertex4i);
PHP_FUNCTION(glvertex4iv);
PHP_FUNCTION(glvertex4s);
PHP_FUNCTION(glvertex4sv);
PHP_FUNCTION(glvertexpointer);
PHP_FUNCTION(glviewport);
PHP_FUNCTION(glgetselectbuffer);

// glGet*() helper macro
#define GET_STATE_NUM_PARAMS(pname,num) \
	{ \
		if ((unsigned int)pname > glget_max || pname < 0) { \
			TSRMLS_FETCH(); \
			php_error(E_WARNING, "%s() argument 1 out of range unknown constant", \
				get_active_function_name(TSRMLS_C)); \
				return; \
		} \
		if (glget_mask[pname] == -1) { \
			TSRMLS_FETCH(); \
			php_error(E_WARNING, "%s() argument 1 unknown constant", \
				get_active_function_name(TSRMLS_C)); \
				return; \
		} \
		num = glget_mask[pname]; \
	}

// glGetMaterial(f|i)v
#define GET_MATERIAL_NUM(constant, num) \
	{ \
		switch(constant) { \
			case GL_AMBIENT: \
			case GL_DIFFUSE: \
			case GL_SPECULAR: \
			case GL_EMISSION: num = 4; break; \
			case GL_COLOR_INDEXES: num = 3; break; \
			case GL_SHININESS: num = 1; break; \
			default: \
				{ \
					TSRMLS_FETCH(); \
					php_error(E_WARNING, "%s() argument 2 unknown constant", \
						get_active_function_name(TSRMLS_C)); \
					RETURN_NULL(); \
				} \
		} \
	}

// glGetLight(f|i)v
#define GET_LIGHT_NUM(constant, num) \
	{ \
		switch(constant) { \
			case GL_AMBIENT: \
			case GL_DIFFUSE: \
			case GL_SPECULAR: \
			case GL_POSITION: num = 4; break; \
			case GL_SPOT_DIRECTION: num = 3; break; \
			case GL_SPOT_EXPONENT: \
			case GL_SPOT_CUTOFF: \
			case GL_CONSTANT_ATTENUATION: \
			case GL_LINEAR_ATTENUATION: \
			case GL_QUADRATIC_ATTENUATION : num = 1; break; \
			default: \
				{ \
					TSRMLS_FETCH(); \
					php_error(E_WARNING, "%s() argument 2 unknown constant", \
						get_active_function_name(TSRMLS_C)); \
					RETURN_NULL(); \
				} \
		} \
	}

// TODO: ugly
// glGetTexeEnv(f|i)v()
#ifdef PHP_WIN32
#define GET_TEXENV_NUM(constant, num) \
	{ \
		switch(constant) { \
			case GL_TEXTURE_ENV_MODE: num = 1; break; \
			case GL_TEXTURE_ENV_COLOR: num = 4; break; \
			default: \
				{ \
					TSRMLS_FETCH(); \
					php_error(E_WARNING, "%s() argument 2 unknown constant", \
						get_active_function_name(TSRMLS_C)); \
					RETURN_NULL(); \
				} \
		} \
	}
#else
#define GET_TEXENV_NUM(constant, num) \
	{ \
		switch(constant) { \
			case GL_TEXTURE_ENV_MODE: num = 1; break; \
			case GL_TEXTURE_ENV_BIAS_SGIX:  \
			case GL_TEXTURE_ENV_COLOR: num = 4; break; \
			default: \
				{ \
					TSRMLS_FETCH(); \
					php_error(E_WARNING, "%s() argument 2 unknown constant", \
						get_active_function_name(TSRMLS_C)); \
					RETURN_NULL(); \
				} \
		} \
	}
#endif

// glGetTexGen(d|f|i)v
#define GET_TEXGEN_NUM(constant, num) \
	{ \
		switch(constant) { \
			case GL_TEXTURE_GEN_MODE: num = 1; break; \
			case GL_OBJECT_PLANE:  \
			case GL_EYE_PLANE: num = 4; break; \
			default: \
				{ \
					TSRMLS_FETCH(); \
					php_error(E_WARNING, "%s() argument 2 unknown constant", \
						get_active_function_name(TSRMLS_C)); \
					RETURN_NULL(); \
				} \
		} \
	}

// TODO: ugly
// glGetTexParameter(f|i)v
#ifdef PHP_WIN32
#define GET_TEXPARAMETER_NUM(constant, num) \
	{ \
		switch(constant) { \
			case GL_TEXTURE_MAG_FILTER: \
			case GL_TEXTURE_MIN_FILTER: \
			case GL_TEXTURE_WRAP_S: \
			case GL_TEXTURE_WRAP_T: \
			case GL_TEXTURE_PRIORITY: \
			case GL_TEXTURE_RESIDENT: \
				num = 1; break; \
			case GL_TEXTURE_BORDER_COLOR: \
				num = 4; break; \
			default: \
				{ \
					TSRMLS_FETCH(); \
					php_error(E_WARNING, "%s() argument 2 unknown constant", \
						get_active_function_name(TSRMLS_C)); \
					RETURN_NULL(); \
				} \
		} \
	}

#else
#define GET_TEXPARAMETER_NUM(constant, num) \
	{ \
		switch(constant) { \
			case GL_TEXTURE_MAG_FILTER: \
			case GL_TEXTURE_MIN_FILTER: \
			case GL_TEXTURE_WRAP_S: \
			case GL_TEXTURE_WRAP_T: \
			case GL_TEXTURE_PRIORITY: \
			case GL_TEXTURE_RESIDENT: \
			case GL_DUAL_TEXTURE_SELECT_SGIS: \
			case GL_QUAD_TEXTURE_SELECT_SGIS: \
			case GL_TEXTURE_FILTER4_SIZE_SGIS: \
			case GL_TEXTURE_CLIPMAP_FRAME_SGIX: \
			case GL_TEXTURE_CLIPMAP_CENTER_SGIX: \
			case GL_TEXTURE_CLIPMAP_OFFSET_SGIX: \
			case GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX: \
			case GL_TEXTURE_COMPARE_SGIX: \
			case GL_TEXTURE_COMPARE_OPERATOR_SGIX: \
			case GL_DETAIL_TEXTURE_MODE_SGIS: \
			case GL_DETAIL_TEXTURE_LEVEL_SGIS: \
			case GL_TEXTURE_WRAP_R_EXT: \
			case GL_DETAIL_TEXTURE_FUNC_POINTS_SGIS: \
			case GL_SHARPEN_TEXTURE_FUNC_POINTS_SGIS: \
			case GL_TEXTURE_MIN_LOD_SGIS: \
			case GL_TEXTURE_MAX_LOD_SGIS: \
			case GL_TEXTURE_BASE_LEVEL_SGIS: \
			case GL_TEXTURE_MAX_LEVEL_SGIS: \
			case GL_SHADOW_AMBIENT_SGIX: \
				num = 1; break; \
			case GL_TEXTURE_BORDER_COLOR: \
			case GL_POST_TEXTURE_FILTER_BIAS_SGIX: \
			case GL_POST_TEXTURE_FILTER_SCALE_SGIX: \
				num = 4; break; \
			default: \
				{ \
					TSRMLS_FETCH(); \
					php_error(E_WARNING, "%s() argument 2 unknown constant", \
						get_active_function_name(TSRMLS_C)); \
					RETURN_NULL(); \
				} \
		} \
	}
#endif

#endif

/* yoya customize */
#if !GL_COLOR_TABLE_FORMAT_EXT && GL_COLOR_TABLE_FORMAT_SGI
 #define GL_COLOR_TABLE_FORMAT_EXT         GL_COLOR_TABLE_FORMAT_SGI
 #define GL_COLOR_TABLE_LUMINANCE_SIZE_EXT GL_COLOR_TABLE_LUMINANCE_SIZE_SGI
 #define GL_COLOR_TABLE_INTENSITY_SIZE_EXT GL_COLOR_TABLE_INTENSITY_SIZE_SGI
 #define GL_COLOR_TABLE_WIDTH_EXT          GL_COLOR_TABLE_WIDTH_SGI
 #define GL_COLOR_TABLE_RED_SIZE_EXT       GL_COLOR_TABLE_RED_SIZE_SGI
 #define GL_COLOR_TABLE_GREEN_SIZE_EXT     GL_COLOR_TABLE_GREEN_SIZE_SGI
 #define GL_COLOR_TABLE_BLUE_SIZE_EXT      GL_COLOR_TABLE_BLUE_SIZE_SGI
 #define GL_COLOR_TABLE_ALPHA_SIZE_EXT     GL_COLOR_TABLE_ALPHA_SIZE_SGI
#endif /* GL_COLOR_TABLE_FORMAT_EXT */
