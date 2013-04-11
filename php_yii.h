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

#ifndef PHP_YII_H
#define PHP_YII_H

extern zend_module_entry yii_module_entry;
#define phpext_yii_ptr &yii_module_entry

#ifdef PHP_WIN32
#	define PHP_YII_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_YII_API __attribute__ ((visibility("default")))
#else
#	define PHP_YII_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define YII_VERSION 					"1.1.14-dev"

/* Declaration Class */
#define YII_CLASS_FUNCTION(name)   	ZEND_MINIT_FUNCTION(yii_##name)

/* Call Class */
#define YII_CLASS(name)	 			ZEND_MODULE_STARTUP_N(yii_##name)(INIT_FUNC_ARGS_PASSTHRU)

/* Declaration Class Method */
#define YII_CLASS_METHODS(name) const zend_function_entry yii_ ##name## _method_entry[] =

/* Declaration class Entry */
#define YII_CLASS_DECLARE_ENTRY(name) zend_class_entry *yii_ ##name## _ce;

/* Declaration class Entry Extern*/
#define YII_CLASS_DECLARE_ENTRY_EX(name) extern zend_class_entry *yii_ ##name## _ce;

/* Call class Entry Extern*/
#define YII_CLASS_ENTRY(name) yii_ ##name## _ce

/** class/interface registering */
#define YII_CLASS_DECLARE(class_name, name, flags) \
	{ \
		zend_class_entry ce; \
		INIT_CLASS_ENTRY(ce, #class_name, yii_ ##name## _method_entry); \
		yii_ ##name## _ce = zend_register_internal_class(&ce TSRMLS_CC); \
		yii_ ##name## _ce->ce_flags |= flags;  \
	}

#define YII_CLASS_DECLARE_EX(class_name, name, parent, flags) \
	{ \
		zend_class_entry ce; \
		INIT_CLASS_ENTRY(ce, #class_name, yii_ ##name## _method_entry); \
		yii_ ##name## _ce = zend_register_internal_class_ex(&ce, NULL, parent TSRMLS_CC); \
		if (!yii_ ##name## _ce) { \
			yii_inherit_not_found(parent, #class_name); \
			return FAILURE;	\
		}  \
		yii_ ##name## _ce->ce_flags |= flags;  \
	}
	
#define YII_NS_CLASS_DECLARE(ns, class_name, name, flags) \
	{ \
		zend_class_entry ce; \
		INIT_NS_CLASS_ENTRY(ce, #ns, #class_name, yii_ ##name## _method_entry); \
		yii_ ##name## _ce = zend_register_internal_class(&ce TSRMLS_CC); \
		yii_ ##name## _ce->ce_flags |= flags;  \
	}

#define YII_NS_CLASS_DECLARE_EX(ns, class_name, name, parent, flags) \
	{ \
		zend_class_entry ce; \
		INIT_NS_CLASS_ENTRY(ce, #ns, #class_name, yii_ ##name## _method_entry); \
		yii_ ##name## _ce = zend_register_internal_class_ex(&ce, NULL, parent TSRMLS_CC); \
		if (!yii_ ##name## _ce) { \
			yii_inherit_not_found(parent, ZEND_NS_NAME(#ns, #class_name)); \
			return FAILURE;	\
		}  \
		yii_ ##name## _ce->ce_flags |= flags;  \
	}

#define YII_CLASS_INTERFACE(class_name, name) \
	{ \
		zend_class_entry ce; \
		INIT_CLASS_ENTRY(ce, #class_name, yii_ ##name## _method_entry); \
		yii_ ##name## _ce = zend_register_internal_interface(&ce TSRMLS_CC); \
	}

#define YII_CLASS_INTERFACE_EX(class_name, name, parent) \
	{ \
		zend_class_entry ce; \
		INIT_CLASS_ENTRY(ce, #class_name, yii_ ##name## _method_entry); \
		yii_ ##name## _ce = yii_register_internal_interface_ex(&ce, parent TSRMLS_CC); \
		if (!yii_ ##name## _ce) { \
			fprintf(stderr, "Can't register interface with parent: %s", parent); \
			return FAILURE;	\
		}  \
	}
	
#define YII_NS_CLASS_INTERFACE(ns, class_name, name) \
	{ \
		zend_class_entry ce; \
		INIT_NS_CLASS_ENTRY(ce, #ns, #class_name, yii_ ##name## _method_entry); \
		yii_ ##name## _ce = zend_register_internal_interface(&ce TSRMLS_CC); \
	}

#define YII_NS_CLASS_INTERFACE_EX(ns, class_name, name, parent) \
	{ \
		zend_class_entry ce; \
		INIT_NS_CLASS_ENTRY(ce, #ns, #class_name, yii_ ##name## _method_entry); \
		yii_ ##name## _ce = yii_register_internal_interface_ex(&ce, parent TSRMLS_CC); \
		if (!yii_ ##name## _ce) { \
			fprintf(stderr, "Can't register interface with parent: %s", parent); \
			return FAILURE;	\
		}  \
	}


#define YII_SL(str) ZEND_STRL(str)
#define YII_SS(str) ZEND_STRS(str)

#define YII_NEW_STRING(zv, str) \
	MAKE_STD_ZVAL(zv); \
	ZVAL_STRING(zv, str, 1);
	
#define YII_NEW_LONG(zv, l) \
	MAKE_STD_ZVAL(zv); \
	ZVAL_LONG(zv, l);

#define YII_NEW_ARRAY(arr_name) \
	ALLOC_INIT_ZVAL(arr_name); \
	array_init(arr_name);

#define YII_DTOR(z) \
	if (&z) {	\
		zval_dtor(&z); \
	}
	
#define YII_PTR_DTOR(zp) \
	if (zp) {	\
		zval_ptr_dtor(&zp); \
	}


PHP_MINIT_FUNCTION(yii);
PHP_MSHUTDOWN_FUNCTION(yii);
PHP_RINIT_FUNCTION(yii);
PHP_RSHUTDOWN_FUNCTION(yii);
PHP_MINFO_FUNCTION(yii);


/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(yii)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(yii)
*/

/* In every utility function you add that needs to use variables 
   in php_yii_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as YII_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define YII_G(v) TSRMG(yii_globals_id, zend_yii_globals *, v)
#else
#define YII_G(v) (yii_globals.v)
#endif

#endif	/* PHP_YII_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
