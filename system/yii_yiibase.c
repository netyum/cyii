#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/yii_yiibase.h"

YII_CLASS_DECLARE_ENTRY(yiibase);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_yiibase_createWebApplication, 0, 0, 0)
	ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yiibase_createConsoleApplication, 0, 0, 0)
	ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yiibase_createApplication, 0, 0, 1)
	ZEND_ARG_INFO(0, class)
	ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()
/* }}} */


/** {{{ string static public YiiBase::getVersion()
*/
PHP_METHOD(YiiBase, getVersion){
	int len;
	char *strg;
	len = spprintf(&strg, 0, YII_VERSION);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */

/** {{{ YII_CLASS_METHODS
*/
YII_CLASS_METHODS(yiibase){
	PHP_ME(YiiBase, getVersion, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC) //静态方法
	//PHP_ME(YiiBase, createWebApplication, arginfo_yiibase_createWebApplication, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC) //静态方法
	//PHP_ME(YiiBase, createConsoleApplication, arginfo_yiibase_createConsoleApplication, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC) //静态方法
	//PHP_ME(YiiBase, createApplication, arginfo_yiibase_createApplication, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC) //静态方法
	//PHP_ME(YiiBase, app, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC) //静态方法
	PHP_FE_END
};
/* }}} */

/** {{{ Class YiiBase
*/
YII_CLASS_FUNCTION(yiibase) {
	
	
	//AUTO CALL CLASS METHOD
	YII_CLASS_DECLARE(YiiBase, yiibase, 0);
	
	zend_declare_property_null(YII_CLASS_ENTRY(yiibase), YII_SL("_app"), ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);
	zend_declare_property_null(YII_CLASS_ENTRY(yiibase), YII_SL("_logger"), ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);
	zend_declare_property_bool(YII_CLASS_ENTRY(yiibase), YII_SL("enableIncludePath"), 0, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC TSRMLS_CC);


	return SUCCESS;
}
/* }}} */