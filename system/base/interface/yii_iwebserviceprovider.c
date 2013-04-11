#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_iwebserviceprovider.h"

YII_CLASS_DECLARE_ENTRY(iwebserviceprovider);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_iwebserviceprovider_beforeWebMethod, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(1, service, CWebService, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iwebserviceprovider_afterWebMethod, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(1, service, CWebService, 0)
ZEND_END_ARG_INFO()
/* }}} */

/** {{{ IWebServiceProvider's methods 
*/
YII_CLASS_METHODS(iwebserviceprovider){
	PHP_ABSTRACT_ME(IWebServiceProvider, beforeWebMethod, arginfo_iwebserviceprovider_beforeWebMethod)
	PHP_ABSTRACT_ME(IWebServiceProvider, afterWebMethod, arginfo_iwebserviceprovider_afterWebMethod)
	PHP_FE_END
};

/** {{{ interface IWebServiceProvider
*/
YII_CLASS_FUNCTION(iwebserviceprovider){

	YII_CLASS_INTERFACE(IWebServiceProvider, iwebserviceprovider);

	return SUCCESS;
}
/* }}} */