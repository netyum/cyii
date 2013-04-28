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
#include "ext/standard/php_var.h"
#include "ext/spl/spl_iterators.h"
#include "php_yii.h"
#include "func.h"

/* interface */
#include "system/base/interface/yii_iapplicationcomponent.h"
#include "system/base/interface/yii_iaction.h"
#include "system/base/interface/yii_iauthmanager.h"
#include "system/base/interface/yii_ibehavior.h"
#include "system/base/interface/yii_icache.h"
#include "system/base/interface/yii_icachedependency.h"
#include "system/base/interface/yii_idataprovider.h"
#include "system/base/interface/yii_ifilter.h"
#include "system/base/interface/yii_ilogfilter.h"
#include "system/base/interface/yii_istatepersister.h"
#include "system/base/interface/yii_iuseridentity.h"
#include "system/base/interface/yii_iviewrenderer.h"
#include "system/base/interface/yii_iwebserviceprovider.h"
#include "system/base/interface/yii_iwebuser.h"
#include "system/base/interface/yii_iwidgetfactory.h"

/* base class */
#include "system/base/yii_ccomponent.h"
#include "system/base/yii_cevent.h"

/* collections class */
#include "system/collections/yii_clist.h"
#include "system/collections/yii_clistiterator.h"
#include "system/collections/yii_cstackiterator.h"
#include "system/collections/yii_cmap.h"
#include "system/collections/yii_cmapiterator.h"
#include "system/collections/yii_cqueueiterator.h"

#include "system/yii_yiibase.h"




/* If you declare any globals in php_yii.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(yii)
*/

/* True global resources - no need for thread safety here */
static int le_yii;

zend_class_entry * ze_router_ce;

/* {{{ yii_functions[]
 *
 * Every user visible function must have an entry in yii_functions[].
 */
const zend_function_entry yii_functions[] = {
	PHP_FE_END	/* Must be the last line in yii_functions[] */
};
/* }}} */


#ifdef COMPILE_DL_YII
ZEND_GET_MODULE(yii)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("yii.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_yii_globals, yii_globals)
    STD_PHP_INI_ENTRY("yii.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_yii_globals, yii_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_yii_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_yii_init_globals(zend_yii_globals *yii_globals)
{
	yii_globals->global_value = 0;
	yii_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(yii)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/

	
	/* interface */
	YII_CLASS(iapplicationcomponent);
	YII_CLASS(iaction);
	YII_CLASS(iauthmanager);
	YII_CLASS(ibehavior);
	YII_CLASS(icache);
	YII_CLASS(icachedependency);
	YII_CLASS(idataprovider);
	YII_CLASS(ifilter);
	YII_CLASS(ilogfilter);
	YII_CLASS(istatepersister);
	YII_CLASS(iuseridentity);
	YII_CLASS(iviewrenderer);
	YII_CLASS(iwebserviceprovider);
	YII_CLASS(iwebuser);
	YII_CLASS(iwidgetfactory);
	
	/* base class */
	
	YII_CLASS(ccomponent);
	YII_CLASS(cevent);
	
	/* collections class */
	YII_CLASS(clist);
	YII_CLASS(clistiterator);
	YII_CLASS(cstackiterator);
	YII_CLASS(cmap);
	YII_CLASS(cmapiterator);
	YII_CLASS(cqueueiterator);
	
	/*  class */
	YII_CLASS(yiibase);

	return SUCCESS;
}

/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(yii)
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
PHP_RINIT_FUNCTION(yii)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(yii)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(yii)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "yii support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ yii_module_entry
 */
zend_module_entry yii_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"yii",
	yii_functions,
	PHP_MINIT(yii),
	PHP_MSHUTDOWN(yii),
	PHP_RINIT(yii),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(yii),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(yii),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
