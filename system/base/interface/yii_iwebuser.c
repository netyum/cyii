#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_iwebuser.h"

YII_CLASS_DECLARE_ENTRY(iwebuser);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_iwebuser_checkAccess, 0, 0, 1)
	ZEND_ARG_INFO(0, operation)
	ZEND_ARG_ARRAY_INFO(0, params, 0)
ZEND_END_ARG_INFO()
/* }}} */

/** {{{ IWebUser's methods 
*/
YII_CLASS_METHODS(iwebuser){
	PHP_ABSTRACT_ME(IWebUser, getId, NULL)
	PHP_ABSTRACT_ME(IWebUser, getName, NULL)
	PHP_ABSTRACT_ME(IWebUser, getIsGuest, NULL)
	PHP_ABSTRACT_ME(IWebUser, checkAccess, arginfo_iwebuser_checkAccess)
	PHP_ABSTRACT_ME(IWebUser, loginRequired, NULL)
	PHP_FE_END
};

/** {{{ interface IWebUser
*/
YII_CLASS_FUNCTION(iwebuser){

	YII_CLASS_INTERFACE(IWebUser, iwebuser);

	return SUCCESS;
}
/* }}} */