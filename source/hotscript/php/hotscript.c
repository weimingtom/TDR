/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_hotscript.h"
#include "main/php_output.h"

#ifdef ZTS
#include "TSRM.h"
#endif

#include "ext/standard/php_smart_str.h"

/* If you declare any globals in php_hotscript.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(hotscript)
*/

/* True global resources - no need for thread safety here */
static int le_hotscript;

/* {{{ hotscript_functions[]
 *
 * Every user visible function must have an entry in hotscript_functions[].
 */
const zend_function_entry hotscript_functions[] = {
	PHP_FE(hot_encode,	NULL)
	PHP_FE_END	/* Must be the last line in hotscript_functions[] */
};
/* }}} */

/* {{{ hotscript_module_entry
 */
zend_module_entry hotscript_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"hotscript",
	hotscript_functions,
	PHP_MINIT(hotscript),
	PHP_MSHUTDOWN(hotscript),
	PHP_RINIT(hotscript),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(hotscript),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(hotscript),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_HOTSCRIPT
ZEND_GET_MODULE(hotscript)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("hotscript.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_hotscript_globals, hotscript_globals)
    STD_PHP_INI_ENTRY("hotscript.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_hotscript_globals, hotscript_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_hotscript_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_hotscript_init_globals(zend_hotscript_globals *hotscript_globals)
{
	hotscript_globals->global_value = 0;
	hotscript_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(hotscript)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(hotscript)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(hotscript)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(hotscript)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(hotscript)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "hotscript support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

#include "hotprotocol/hp_abstract_reader.h"
#include "hotpot/hp_error.h"

#define MAX_DEEP 1024
typedef struct tagSTACK_NODE
{
	zval *val;
	HashPosition pos;
}STACK_NODE;

typedef struct _ZVALReader
{
	HPAbstractReader super;
	hpuint32 stack_num;
	STACK_NODE stack[MAX_DEEP];
}ZVALReader;

zval* zval_reade_get_zval(ZVALReader *self)
{
	return self->stack[self->stack_num - 1].val;
}
hpint32 zval_read_field_end(HPAbstractReader *super, const char *var_name, hpuint32 len)
{
	ZVALReader *self = HP_CONTAINER_OF(super, ZVALReader, super);
	--(self->stack_num);
	return E_HP_NOERROR;
}

hpint32 zval_read_field_begin(HPAbstractReader *super, const char *var_name, hpuint32 len)
{
	ZVALReader *self = HP_CONTAINER_OF(super, ZVALReader, super);
	HashTable *myht;
	zval *zv = zval_reade_get_zval(self);
	zval **data;

	if (Z_TYPE_P(zv) != IS_ARRAY)
	{		
		return E_HP_ERROR;
	}
	myht = zv->value.ht;
	

	if(zend_hash_find(myht, var_name, len, (void **)&data) != SUCCESS)
	{			
		printf("error!\n");
		return E_HP_ERROR;
	}
	

	self->stack[self->stack_num].val = *data;


	return E_HP_NOERROR;
}
hpint32 zval_reader_vector_item_end(HPAbstractReader *super, hpuint32 index)
{
	ZVALReader *self = HP_CONTAINER_OF(super, ZVALReader, super);
	--(self->stack_num);
	return E_HP_NOERROR;
}
hpint32 zval_reader_vector_item_begin(HPAbstractReader *super, hpuint32 index)
{
	ZVALReader *self = HP_CONTAINER_OF(super, ZVALReader, super);
	HashTable *myht;
	zval *zv = zval_reade_get_zval(self);
	zval **data;

	if (Z_TYPE_P(zv) != IS_ARRAY)
	{		
		return E_HP_ERROR;
	}
	myht = zv->value.ht;

	if(zend_hash_index_find(myht, index, (void **) &data) != SUCCESS)
	{
		return E_HP_ERROR;
	}
	self->stack[self->stack_num].val = *data;
	
	return E_HP_NOERROR;
}

hpint32 zval_reader_read_type(HPAbstractReader *super, HPType *type)
{
	ZVALReader *self = HP_CONTAINER_OF(super, ZVALReader, super);
	zval *zv = zval_reade_get_zval(self);

	switch(Z_TYPE_P(zv))
	{
	case IS_STRING:
		*type = E_HP_BYTES;
		break;
	case IS_DOUBLE:
		*type = E_HP_DOUBLE;
		break;
	case IS_LONG:
		*type = E_HP_INT64;
		break;
	default:
		return E_HP_ERROR;
	}
	return E_HP_NOERROR;
}

hpint32 zval_reader_bytes(HPAbstractReader *super, hpbytes *bytes)
{
	ZVALReader *self = HP_CONTAINER_OF(super, ZVALReader, super);
	zval *zv = zval_reade_get_zval(self);
	if(Z_TYPE_P(zv) != IS_STRING)
	{
		return E_HP_ERROR;
	}
	bytes->ptr = Z_STRVAL_P(zv);
	bytes->len = Z_STRLEN_P(zv);
	return E_HP_NOERROR;
}

hpint32 zval_reader_double(HPAbstractReader *super, hpdouble *val)
{
	ZVALReader *self = HP_CONTAINER_OF(super, ZVALReader, super);
	zval *zv = zval_reade_get_zval(self);
	if(Z_TYPE_P(zv) != IS_DOUBLE)
	{
		return E_HP_ERROR;
	}
	*val = Z_DVAL_P(zv);
	return E_HP_NOERROR;
}

hpint32 zval_reader_int64(HPAbstractReader *super, hpint64 *val)
{
	ZVALReader *self = HP_CONTAINER_OF(super, ZVALReader, super);
	zval *zv = zval_reade_get_zval(self);
	if(Z_TYPE_P(zv) != IS_LONG)
	{
		return E_HP_ERROR;
	}
	*val = Z_LVAL_P(zv);
	return E_HP_NOERROR;
}

hpint32 zval_reader_end(HPAbstractReader *super)
{
	ZVALReader *self = HP_CONTAINER_OF(super, ZVALReader, super);
	--(self->stack_num);

	return E_HP_NOERROR;
}

hpint32 zval_reader_init(ZVALReader *self)
{
	memset(&self->super, 0, sizeof(HPAbstractReader));

	self->super.read_field_begin = zval_read_field_begin;
	self->super.read_field_end= zval_read_field_end;
	self->super.read_vector_item_begin = zval_reader_vector_item_begin;	
	self->super.read_vector_item_end= zval_reader_vector_item_end;

	self->super.read_hpint64 = zval_reader_int64;
	self->super.read_hpdouble = zval_reader_double;
	self->super.read_bytes = zval_reader_bytes;
	self->super.read_type = zval_reader_read_type;

	return E_HP_NOERROR;
}



#include "hotscript/hot_vm.h"

static void php_putc(HotVM *self, char c)
{
	smart_str_appendc((smart_str*)self->user_data, c);
}

#include "hotscript/script_parser.h"

PHP_FUNCTION(hot_encode)
{
	zval *parameter = NULL;	
	zval **data;
	smart_str buf = {0};
	ZVALReader reader;
	SCRIPT_PARSER sp;
	char *file_name = NULL;
	int file_name_len;

	HashTable *myht;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "as", &parameter, &file_name, &file_name_len) == FAILURE)
	{
		ZVAL_FALSE(return_value);
	}

	myht = parameter->value.ht;
	if(zend_hash_find(myht, "name", 4, (void **)&data) != SUCCESS)
	{			
		printf("error!\n");
		return;
	}


	zval_reader_init(&reader);
	reader.stack[0].val = parameter;
	reader.stack_num = 1;
	
	if(script_parser(&sp, file_name, &reader.super, &buf, php_putc) != E_HP_NOERROR)
	{
		ZVAL_FALSE(return_value);
	}
	ZVAL_STRINGL(return_value, buf.c, buf.len, 1);

	smart_str_free(&buf);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
