#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_ilogfilter.h"

YII_CLASS_DECLARE_ENTRY(ilogfilter);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_ilogfilter_filter, 0, 0, 1)
	ZEND_ARG_INFO(1, logs)
ZEND_END_ARG_INFO()
/* }}} */

/** {{{ ILogFilter's methods 
*/
YII_CLASS_METHODS(ilogfilter){
	PHP_ABSTRACT_ME(ILogFilter, filter, arginfo_ilogfilter_filter)
	PHP_FE_END
};

/** {{{ interface ILogFilter
*/
YII_CLASS_FUNCTION(ilogfilter){

	YII_CLASS_INTERFACE(ILogFilter, ilogfilter);

	return SUCCESS;
}
/* }}} */