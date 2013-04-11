#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_istatepersister.h"

YII_CLASS_DECLARE_ENTRY(istatepersister);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_istatepersister_save, 0, 0, 1)
	ZEND_ARG_INFO(0, state)
ZEND_END_ARG_INFO()
/* }}} */

/** {{{ IStatePersister's methods 
*/
YII_CLASS_METHODS(istatepersister){
	PHP_ABSTRACT_ME(IStatePersister, load, NULL)
	PHP_ABSTRACT_ME(IStatePersister, save, arginfo_istatepersister_save)
	PHP_FE_END
};

/** {{{ interface IStatePersister
*/
YII_CLASS_FUNCTION(istatepersister){

	YII_CLASS_INTERFACE(IStatePersister, istatepersister);

	return SUCCESS;
}
/* }}} */