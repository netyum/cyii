#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_ifilter.h"

YII_CLASS_DECLARE_ENTRY(ifilter);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_ifilter_filter, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(1, filterChain, CFilterChain, 0)
ZEND_END_ARG_INFO()
/* }}} */

/** {{{ IFilter's methods 
*/
YII_CLASS_METHODS(ifilter){
	PHP_ABSTRACT_ME(IFilter, filter, arginfo_ifilter_filter)
	PHP_FE_END
};

/** {{{ interface IFilter
*/
YII_CLASS_FUNCTION(ifilter){

	YII_CLASS_INTERFACE(IFilter, ifilter);

	return SUCCESS;
}
/* }}} */