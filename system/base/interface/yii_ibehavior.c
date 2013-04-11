#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_ibehavior.h"

YII_CLASS_DECLARE_ENTRY(ibehavior);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_ibehavior_attach, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(1, component, CComponent, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ibehavior_detach, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(1, component, CComponent, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ibehavior_setEnabled, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()
/* }}} */

/** {{{ IBehavior's methods 
*/
YII_CLASS_METHODS(ibehavior){
	PHP_ABSTRACT_ME(IBehavior, attach, arginfo_ibehavior_attach)
	PHP_ABSTRACT_ME(IBehavior, detach, arginfo_ibehavior_detach)
	PHP_ABSTRACT_ME(IBehavior, getEnabled, NULL)
	PHP_ABSTRACT_ME(IBehavior, setEnabled, arginfo_ibehavior_setEnabled)
	PHP_FE_END
};

/** {{{ interface IBehavior
*/
YII_CLASS_FUNCTION(ibehavior){

	YII_CLASS_INTERFACE(IBehavior, ibehavior);

	return SUCCESS;
}
/* }}} */