#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_idataprovider.h"

YII_CLASS_DECLARE_ENTRY(idataprovider);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_idataprovider_getItemCount, 0, 0, 1)
	ZEND_ARG_INFO(0, refresh)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_idataprovider_getTotalItemCount, 0, 0, 1)
	ZEND_ARG_INFO(0, refresh)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_idataprovider_getData, 0, 0, 1)
	ZEND_ARG_INFO(0, refresh)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_idataprovider_getKeys, 0, 0, 1)
	ZEND_ARG_INFO(0, refresh)
ZEND_END_ARG_INFO()
/* }}} */

/** {{{ IDataProvider's methods 
*/
YII_CLASS_METHODS(idataprovider){
	PHP_ABSTRACT_ME(IDataProvider, getId, NULL)
	PHP_ABSTRACT_ME(IDataProvider, getItemCount, arginfo_idataprovider_getItemCount)
	PHP_ABSTRACT_ME(IDataProvider, getTotalItemCount, arginfo_idataprovider_getTotalItemCount)
	PHP_ABSTRACT_ME(IDataProvider, getData, arginfo_idataprovider_getData)
	PHP_ABSTRACT_ME(IDataProvider, getKeys, arginfo_idataprovider_getKeys)
	PHP_ABSTRACT_ME(IDataProvider, getSort, NULL)
	PHP_ABSTRACT_ME(IDataProvider, getPagination, NULL)
	PHP_FE_END
};

/** {{{ interface IDataProvider
*/
YII_CLASS_FUNCTION(idataprovider){

	YII_CLASS_INTERFACE(IDataProvider, idataprovider);

	return SUCCESS;
}
/* }}} */