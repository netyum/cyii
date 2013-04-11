#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_iwidgetfactory.h"

YII_CLASS_DECLARE_ENTRY(iwidgetfactory);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_iwidgetfactory_createWidget, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(1, owner, CBaseController, 0)
	ZEND_ARG_INFO(0, className)
	ZEND_ARG_ARRAY_INFO(0, properties, 0)
ZEND_END_ARG_INFO()
/* }}} */

/** {{{ IWidgetFactory's methods 
*/
YII_CLASS_METHODS(iwidgetfactory){
	PHP_ABSTRACT_ME(IWidgetFactory, createWidget, arginfo_iwidgetfactory_createWidget)
	PHP_FE_END
};

/** {{{ interface IWidgetFactory
*/
YII_CLASS_FUNCTION(iwidgetfactory){

	YII_CLASS_INTERFACE(IWidgetFactory, iwidgetfactory);

	return SUCCESS;
}
/* }}} */