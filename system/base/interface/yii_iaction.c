#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_iaction.h"

YII_CLASS_DECLARE_ENTRY(iaction);

/** {{{ ARG_INFO
*/
/* }}} */

/** {{{ IAction's methods 
*/
YII_CLASS_METHODS(iaction){
	PHP_ABSTRACT_ME(IAction, getId, NULL)
	PHP_ABSTRACT_ME(IAction, getController, NULL)
	PHP_FE_END
};

/** {{{ interface IAction
*/
YII_CLASS_FUNCTION(iaction){

	YII_CLASS_INTERFACE(IAction, iaction);

	return SUCCESS;
}
/* }}} */