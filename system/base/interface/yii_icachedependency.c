#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_icachedependency.h"

YII_CLASS_DECLARE_ENTRY(icachedependency);

/** {{{ ARG_INFO
*/
/* }}} */

/** {{{ ICacheDependency's methods 
*/
YII_CLASS_METHODS(icachedependency){
	PHP_ABSTRACT_ME(ICacheDependency, evaluateDependency, NULL)
	PHP_ABSTRACT_ME(ICacheDependency, getHasChanged, NULL)
	PHP_FE_END
};

/** {{{ interface ICacheDependency
*/
YII_CLASS_FUNCTION(icachedependency){

	YII_CLASS_INTERFACE(ICacheDependency, icachedependency);

	return SUCCESS;
}
/* }}} */