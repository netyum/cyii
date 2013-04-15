#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */
#include "ext/standard/php_var.h"
#include "php_yii.h"
#include "func.h"
#include "system/base/yii_ccomponent.h"
#include "system/base/yii_cevent.h"

YII_CLASS_DECLARE_ENTRY(cevent);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_cevent___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, sender)
	ZEND_ARG_INFO(0, params)
ZEND_END_ARG_INFO()
/* }}} */


/** {{{ public CEvent::__construct()
*/
PHP_METHOD(CEvent, __construct){

	return;

}
/* }}} */

/** {{{ YII_CLASS_METHODS
*/
YII_CLASS_METHODS(cevent) {
	PHP_ME(CEvent, __construct, arginfo_cevent___construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/** {{{ Class CComponent
*/
YII_CLASS_FUNCTION(cevent) {
	//AUTO CALL CLASS METHOD
	YII_CLASS_DECLARE_EX(CEvent, cevent, YII_CLASS_ENTRY(ccomponent), "CComponent", 0);
	
	zend_declare_property_null(YII_CLASS_ENTRY(cevent), YII_SL("sender"), ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_bool(YII_CLASS_ENTRY(cevent), YII_SL("handled"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(YII_CLASS_ENTRY(cevent), YII_SL("params"), ZEND_ACC_PUBLIC TSRMLS_CC);
	return SUCCESS;
}
/* }}} */
