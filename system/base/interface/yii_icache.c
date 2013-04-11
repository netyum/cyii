#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_icache.h"

YII_CLASS_DECLARE_ENTRY(icache);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_icache_get, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_icache_mget, 0, 0, 1)
	ZEND_ARG_INFO(0, ids)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_icache_set, 0, 0, 2)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_INFO(0, expire)
	ZEND_ARG_INFO(0, dependency)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_icache_add, 0, 0, 2)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_INFO(0, expire)
	ZEND_ARG_INFO(0, dependency)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_icache_delete, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()
/* }}} */


/** {{{ ICache's methods 
*/
YII_CLASS_METHODS(icache){
	PHP_ABSTRACT_ME(ICache, get, arginfo_icache_get)
	PHP_ABSTRACT_ME(ICache, mget, arginfo_icache_mget)
	PHP_ABSTRACT_ME(ICache, set, arginfo_icache_set)
	PHP_ABSTRACT_ME(ICache, add, arginfo_icache_add)
	PHP_ABSTRACT_ME(ICache, delete, arginfo_icache_delete)
	PHP_ABSTRACT_ME(ICache, flush, NULL)
	PHP_FE_END
};

/** {{{ interface ICache
*/
YII_CLASS_FUNCTION(icache){

	YII_CLASS_INTERFACE(ICache, icache);

	return SUCCESS;
}
/* }}} */