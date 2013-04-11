#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_iuseridentity.h"

YII_CLASS_DECLARE_ENTRY(iuseridentity);

/** {{{ ARG_INFO
*/
/* }}} */

/** {{{ IUserIdentity's methods 
*/
YII_CLASS_METHODS(iuseridentity){
	PHP_ABSTRACT_ME(IUserIdentity, authenticate, NULL)
	PHP_ABSTRACT_ME(IUserIdentity, getIsAuthenticated, NULL)
	PHP_ABSTRACT_ME(IUserIdentity, getId, NULL)
	PHP_ABSTRACT_ME(IUserIdentity, getName, NULL)
	PHP_ABSTRACT_ME(IUserIdentity, getPersistentStates, NULL)
	PHP_FE_END
};

/** {{{ interface IUserIdentity
*/
YII_CLASS_FUNCTION(iuseridentity){

	YII_CLASS_INTERFACE(IUserIdentity, iuseridentity);

	return SUCCESS;
}
/* }}} */