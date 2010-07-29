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

/* $Id: php_osmesa.c,v 1.3 2001/10/16 12:01:36 drbrain Exp $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#ifdef PHP_OPENGL_OSMESA

#include "php_osmesa.h"

int le_osmesacontext = 0;
#define le_osmesacontext_name "OSMesaContext"

/* {{{ resource OSMesaCreateContext(long format[, resoruce sharelist])
   create a new Off-Screen Mesa rendering context
   format - one of OSMESA_COLOR_INDEX, OSMESA_RGBA, OSMESA_BGRA,
   			OSMESA_ARGB, OSMESA_RGB, or OSMESA_BGR.
	sharelist - specifies another OSMesaContext with which to share
				display lists.  NULL indicates no sharing. */
PHP_FUNCTION(osmesacreatecontext)
{
	int arg_format;
	zval *arg_sharelist = NULL;
	php_osmesacontext *php_ctx = NULL, *php_sharelist = NULL;
	OSMesaContext ctx;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|r",
							  &arg_format, &arg_sharelist) == FAILURE) {
		RETURN_FALSE;
	}

	if (arg_sharelist) {
		ZEND_FETCH_RESOURCE(php_sharelist, php_osmesacontext *, &arg_sharelist, -1, le_osmesacontext_name, le_osmesacontext)
	}

	ctx = OSMesaCreateContext(arg_format, (php_sharelist) ? php_sharelist->ctx : NULL);
	
	if (!ctx)
		RETURN_FALSE;
	
	php_ctx = (php_osmesacontext*)emalloc(sizeof(php_osmesacontext));
	php_ctx->ctx = ctx;
	php_ctx->buffer = NULL;
	php_ctx->width = php_ctx->height = 0;
	ZEND_REGISTER_RESOURCE(return_value, php_ctx, le_osmesacontext);
}
/* }}} */

/* {{{ resource OSMesaCreateContextExt(long format, long depthBits, long stencilBits, long accumBits[, resource sharelist])
   See OSMesaCreateContext().
   Additionally you can specify desired size of depth buffer, stencil buffer and accumulation buffer.
   If you specify zero for depthBits, stencilBits, accumBits you can save some memory. */
PHP_FUNCTION(osmesacreatecontextext)
{
	int arg_format, arg_depthbits, arg_stencilbits, arg_accumbits;
	zval *arg_sharelist = NULL;
	php_osmesacontext *php_ctx = NULL, *php_sharelist = NULL;
	OSMesaContext ctx;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll|r",
							  &arg_format, &arg_depthbits, &arg_stencilbits,
							  &arg_accumbits, &arg_sharelist) == FAILURE) {
		RETURN_FALSE;
	}

	if (arg_sharelist) {
		ZEND_FETCH_RESOURCE(php_sharelist, php_osmesacontext *, &arg_sharelist, -1, le_osmesacontext_name, le_osmesacontext)
	}

	ctx = OSMesaCreateContextExt(arg_format, arg_depthbits, arg_stencilbits, arg_accumbits, (php_sharelist) ? php_sharelist->ctx : NULL);
	
	if (!ctx)
		RETURN_FALSE;
	
	php_ctx = (php_osmesacontext*)emalloc(sizeof(php_osmesacontext));
	php_ctx->ctx = ctx;
	php_ctx->buffer = NULL;
	php_ctx->width = php_ctx->height = 0;
	ZEND_REGISTER_RESOURCE(return_value, php_ctx, le_osmesacontext);
}

/* {{{ void OSMesaContextDestroy(resource context) */
PHP_FUNCTION(osmesadestroycontext)
{
	zval *arg_context = NULL;
	php_osmesacontext *php_ctx = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r",
							  &arg_context) == FAILURE) {
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(php_ctx, php_osmesacontext *, &arg_context, -1, le_osmesacontext_name, le_osmesacontext);

	if (!php_ctx->ctx) {
		php_error(E_WARNING, "%s() argument 1 is resoure but has no associated OSMesaContext (did you call OSMesaContextDestroy?)",
				  get_active_function_name(TSRMLS_C));
		return;
	}

	zend_list_delete(Z_RESVAL_P(arg_context));
}
/* }}} */

/* {{{ bool OSMesaMakeCurrent(resource context, long pixeltype, long width, long height);
    Bind an OSMesaContext to an image buffer.  The php_osmesa extension
	allocates the required buffer itself.
    
    Image data is stored in the order of glDrawPixels:  row-major order
    with the lower-left image pixel stored in the first array position
    (ie. bottom-to-top).
    
    Since the only type initially supported is GL_UNSIGNED_BYTE, if the
    context is in RGBA mode, each pixel will be stored as a 4-byte RGBA
    value.  If the context is in color indexed mode, each pixel will be
    stored as a 1-byte value.
    
    If the context's viewport hasn't been initialized yet, it will now be
    initialized to (0,0,width,height).
    
    Input:  ctx - the rendering context
            type - data type for pixel components, only GL_UNSIGNED_BYTE
                   supported now
            width, height - size of image buffer in pixels, at least 1
    Return:  GL_TRUE if success, GL_FALSE if error because of invalid ctx,
             type!=GL_UNSIGNED_BYTE, width<1, height<1,
             width>internal limit or height>internal limit. */
PHP_FUNCTION(osmesamakecurrent)
{	

	int arg_type, arg_width, arg_height, size = 0;
	zval *arg_context;
	php_osmesacontext *php_ctx = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlll",
							  &arg_context, &arg_type, &arg_width, &arg_height) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(php_ctx, php_osmesacontext *, &arg_context, -1, le_osmesacontext_name, le_osmesacontext);

	if (!php_ctx->ctx) {
		php_error(E_WARNING, "%s() argument 1 is resoure but has no associated OSMesaContext (did you call OSMesaContextDestroy?)",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	switch(arg_type) {
		case GL_UNSIGNED_BYTE:
			size = 4;
			break;
		default:
			php_error(E_WARNING, "%s() unknown or unsupported pixeltype %d",
					  get_active_function_name(TSRMLS_C));
			RETURN_FALSE;
	}

	size = arg_width * arg_height * size;
	if ( !(php_ctx->buffer = emalloc(size))) {
		php_error(E_WARNING, "%s() couldn't allocate buffer size of %d bytes", size);
		RETURN_FALSE;
	}
	php_ctx->size = size;
	php_ctx->width = arg_width;
	php_ctx->height = arg_height;

	RETURN_BOOL(OSMesaMakeCurrent(php_ctx->ctx, php_ctx->buffer, arg_type, arg_width, arg_height));
}
/* }}} */

/* {{{ string OSMesaGetBuffer(resource context[, long format]) */
PHP_FUNCTION(osmesagetbuffer)
{
	zval *arg_context;
	int arg_format = 0;
	php_osmesacontext *php_ctx;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|l", &arg_context, &arg_format) == FAILURE)
		return;

	ZEND_FETCH_RESOURCE(php_ctx, php_osmesacontext *, &arg_context, -1, le_osmesacontext_name, le_osmesacontext);

	if (!php_ctx->ctx) {
		php_error(E_WARNING, "%s() argument 1 is resoure but has no associated OSMesaContext (did you call OSMesaContextDestroy() ?)",
				  get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	if (!php_ctx->buffer) {
		php_error(E_WARNING, "%s() argument 1 is resource but has no associated buffer (forgot to call OSMesaMakeCurrent() ?)",
				get_active_function_name(TSRMLS_C));
		RETURN_FALSE;
	}

	switch (arg_format) {
		case OSMESA_BUFFER_RAW:
			RETURN_STRINGL(php_ctx->buffer, php_ctx->size, 1);
			break;
		case OSMESA_BUFFER_TGA:
			{
				int tgasize = (php_ctx->width * php_ctx->height * 3) + 18;
				GLubyte *tga = emalloc(tgasize);
				GLint y_up;
				OSMesaGetIntegerv(OSMESA_Y_UP, &y_up);
				if (!tga) {
					php_error(E_WARNING, "%s() unable to allocate %d bytes for TGA buffer",
						get_active_function_name(TSRMLS_C), tgasize);
					RETURN_FALSE;
				}
				memset(tga, 0, 18); // size of TGA header
				tga[2] = 0x02; // Image Type, 2 => Uncompressed, True-color Image
				tga[12] = php_ctx->width & 0xff; // Image Width
				tga[13] = (php_ctx->width>>8) & 0xff;
				tga[14] = php_ctx->height & 0xff; // Image Height
				tga[15] = (php_ctx->height>>8) & 0xff;
				tga[16] = 0x18; // Pixel Depth, 0x18 => 24 Bits
				tga[17] = 0x20; // Image Descriptor
				// TGA image is always the right orientation, ie. its not upside
				// down when you change OSMESA_Y_UP
				{
					int x, y, ydelta = php_ctx->width * 4, xinc = 4, xmax, i = 18; // Header offset
					if (y_up) {
						for (y = (php_ctx->height - 1) * php_ctx->width * 4; y >= 0; y -= ydelta) {
							xmax = y + (php_ctx->width * 4);
							for (x = y; x < xmax; x += xinc) {
								tga[i++] = php_ctx->buffer[x+2];
								tga[i++] = php_ctx->buffer[x+1];
								tga[i++] = php_ctx->buffer[x];
							}
						}
					} else {
						for (y = 0; y < (php_ctx->height * php_ctx->width * 4); y += ydelta) {
							xmax = y + (php_ctx->width * 4);
							for (x = y; x < xmax; x += xinc) {
								tga[i++] = php_ctx->buffer[x+2];
								tga[i++] = php_ctx->buffer[x+1];
								tga[i++] = php_ctx->buffer[x];
							}
						}
					}
				}
				// No idea why RETURN_STRINGL(tga, tgasize, 0); doesn't work
				// .. needing to copy the full data costs time and memory :/
				ZVAL_STRINGL(return_value, tga, tgasize, 1);
				efree(tga);
				return;
			}
			break;
	}

	php_error(E_WARNING, "%s() argument 2 unknown format type '%d'",
			get_active_function_name(TSRMLS_C), arg_format);
	RETURN_FALSE;
}

/* {{{ resource OSMesaGetCurrentContext() */
PHP_FUNCTION(osmesagetcurrentcontext)
{
	OSMesaContext ctx = OSMesaGetCurrentContext();
	zend_rsrc_list_entry *le;
	ulong index;

	if (ctx)
		for (zend_hash_internal_pointer_reset(&EG(regular_list));
			 zend_hash_get_current_data(&EG(regular_list), (void **) &le) == SUCCESS;
			 zend_hash_move_forward(&EG(regular_list))) {
			if (((php_osmesacontext*)(le->ptr))->ctx == ctx) {
				zend_hash_get_current_key_ex(&EG(regular_list), NULL, NULL, &index, 0, NULL);
				return_value->value.lval = index;
				return_value->type = IS_RESOURCE;
				return;
			}
		}
}
/* }}} */

/* {{{ void OSMesaPixelStore(long pname, long value)
   This is similar to glPixelStore.
   Input:  pname - OSMESA_ROW_LENGTH
                      specify actual pixels per row in image buffer
                      0 = same as image width (default)
                   OSMESA_Y_UP
                      zero = Y coordinates increase downward
                      non-zero = Y coordinates increase upward (default)
           value - the value for the parameter pname. */
PHP_FUNCTION(osmesapixelstore)
{
	GLint arg_pname, arg_value;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ll",
							  &arg_pname, &arg_value) == FAILURE)
		return;

	OSMesaPixelStore(arg_pname, arg_value);
}

/* {{{ long OSMesaGetIntegerv(long pname[, long value])
   Return an integer value like glGetIntegerv.
   Input:  pname -
                   OSMESA_WIDTH  return current image width
                   OSMESA_HEIGHT  return current image height
                   OSMESA_FORMAT  return image format
                   OSMESA_TYPE  return color component data type
                   OSMESA_ROW_LENGTH return row length in pixels
                   OSMESA_Y_UP returns 1 or 0 to indicate Y axis direction
           value - long value with result. */
PHP_FUNCTION(osmesagetintegerv)
{
	int arg_pname;
	GLint value;
	zval *arg_value = NULL;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l|z",
							  &arg_pname, &arg_value) == FAILURE)
		return;

	OSMesaGetIntegerv(arg_pname, &value);
	if (arg_value) {
		convert_to_long(arg_value);
		ZVAL_LONG(arg_value, value);
	}
	RETURN_LONG(value);
}

PHP_FUNCTION(osmesagetdepthbuffer)
{
	NOT_IMPLEMENTED();
}

PHP_FUNCTION(osmesagetcolorbuffer)
{
	NOT_IMPLEMENTED();
}

void osmesacontext_destructor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	php_osmesacontext *php_ctx = (php_osmesacontext *) rsrc->ptr;

	if (php_ctx->ctx)
		OSMesaDestroyContext(php_ctx->ctx);
	if (php_ctx->buffer)
		efree(php_ctx->buffer);
	efree(php_ctx);
}

int osmesa_init(int module_number)
{
	TSRMLS_FETCH();

	le_osmesacontext = zend_register_list_destructors_ex(osmesacontext_destructor, NULL, le_osmesacontext_name, module_number);

	// OSMesa constants
	REGISTER_LONG_CONSTANT("OSMESA_MAJOR_VERSION", OSMESA_MAJOR_VERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OSMESA_MINOR_VERSION", OSMESA_MINOR_VERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OSMESA_COLOR_INDEX", OSMESA_COLOR_INDEX, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OSMESA_RGBA", OSMESA_RGBA, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OSMESA_BGRA", OSMESA_BGRA, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OSMESA_ARGB", OSMESA_ARGB, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OSMESA_RGB", OSMESA_RGB, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OSMESA_BGR", OSMESA_BGR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OSMESA_ROW_LENGTH", OSMESA_ROW_LENGTH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OSMESA_Y_UP", OSMESA_Y_UP, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OSMESA_WIDTH", OSMESA_WIDTH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OSMESA_HEIGHT", OSMESA_HEIGHT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OSMESA_FORMAT", OSMESA_FORMAT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OSMESA_TYPE", OSMESA_TYPE, CONST_CS | CONST_PERSISTENT);

	// Constants for OSMesaGetBuffer()
	REGISTER_LONG_CONSTANT("OSMESA_BUFFER_RAW", OSMESA_BUFFER_RAW, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("OSMESA_BUFFER_TGA", OSMESA_BUFFER_TGA, CONST_CS | CONST_PERSISTENT);
	
	return SUCCESS;
}

int osmesa_request_shutdown()
{
	return SUCCESS;
}

#endif // PHP_OPENGL_OSMESA
