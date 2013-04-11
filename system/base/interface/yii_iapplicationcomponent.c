#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_iapplicationcomponent.h"

YII_CLASS_DECLARE_ENTRY(iapplicationcomponent);

/** {{{ ARG_INFO
*/
/* }}} */

/** {{{ IApplicationComponent's methods 
*/
YII_CLASS_METHODS(iapplicationcomponent){
	PHP_ABSTRACT_ME(IApplicationComponent, init, NULL)
	PHP_ABSTRACT_ME(IApplicationComponent, getIsInitialized, NULL)
	PHP_FE_END
};

/** {{{ interface IApplicationComponent
*/
YII_CLASS_FUNCTION(iapplicationcomponent){

	YII_CLASS_INTERFACE(IApplicationComponent, iapplicationcomponent);

	return SUCCESS;
}
/* }}} */