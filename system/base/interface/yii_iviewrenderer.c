#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_iviewrenderer.h"

YII_CLASS_DECLARE_ENTRY(iviewrenderer);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_iviewrenderer_renderFile, 0, 0, 4)
	ZEND_ARG_INFO(0, context)
	ZEND_ARG_INFO(0, file)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, return)
ZEND_END_ARG_INFO()
/* }}} */

/** {{{ IViewRenderer's methods 
*/
YII_CLASS_METHODS(iviewrenderer){
	PHP_ABSTRACT_ME(IViewRenderer, renderFile, arginfo_iviewrenderer_renderFile)
	PHP_FE_END
};

/** {{{ interface IViewRenderer
*/
YII_CLASS_FUNCTION(iviewrenderer){

	YII_CLASS_INTERFACE(IViewRenderer, iviewrenderer);

	return SUCCESS;
}
/* }}} */