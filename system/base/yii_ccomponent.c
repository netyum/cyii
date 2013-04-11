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

YII_CLASS_DECLARE_ENTRY(ccomponent);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent___get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent___set, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent___isset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent___unset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent___call, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_asa, 0, 0, 1)
	ZEND_ARG_INFO(0, behavior)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_attachBehaviors, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, behaviors, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_attachBehavior, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, behavior)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_detachBehavior, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_enableBehavior, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_disableBehavior, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_hasProperty, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_canGetProperty, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_canSetProperty, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_hasEvent, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_hasEventHandler, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_getEventHandlers, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_attachEventHandler, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, handler) //callback
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_detachEventHandler, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, handler) //callback
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_raiseEvent, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_OBJ_INFO(1, event, CEvent, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ccomponent_evaluateExpression, 0, 0, 2)
	ZEND_ARG_INFO(0, _expression_)
	ZEND_ARG_ARRAY_INFO(0, _data, 0)
ZEND_END_ARG_INFO()
/* }}} */


/** {{{ public CComponent::__get()
*/
PHP_METHOD(CComponent, __get){

	zval *getter_zv, *name_zv, *on_zv, *len_zv, *e_zv=NULL, *m_zv;
	char *name, *getter;
	int name_len, getter_len;
	zval *method_exists_return_zv=NULL, *get_zv=NULL;
	zval *strncasecmp_return_zv=NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {
		return;
	}
	
	/* $getter='get'.$name; */
	getter_len = spprintf(&getter, 0, "get%s", name);
	
	YII_NEW_STRING(getter_zv, getter);
	/* method_exists($this,$getter) */
	if (yii_call_user_fun_2("method_exists", &method_exists_return_zv, getThis(), getter_zv) == SUCCESS) {
		if (Z_TYPE_P(method_exists_return_zv) == IS_BOOL && Z_BVAL_P(method_exists_return_zv) == 1) {
			/* return $this->$getter();*/
			if (yii_call_class_method_0(getThis(), getter, &get_zv) == SUCCESS) {
			
				RETVAL_ZVAL(get_zv, 1, 0);
				
				YII_PTR_DTOR(method_exists_return_zv);
				YII_PTR_DTOR(getter_zv);
				YII_PTR_DTOR(get_zv);
				efree(getter);
				return;
			}
			
		}
	}

	YII_PTR_DTOR(getter_zv);
	efree(getter);
	
	YII_PTR_DTOR(method_exists_return_zv);
	
	/* strncasecmp($name,'on',2) */
	YII_NEW_STRING(name_zv, name);
	YII_NEW_STRING(on_zv, "on");
	YII_NEW_LONG(len_zv, 2);
	
	if (
		yii_call_user_fun_3("strncasecmp", &strncasecmp_return_zv, name_zv, on_zv, len_zv) == SUCCESS &&
		Z_TYPE_P(strncasecmp_return_zv) == IS_LONG && Z_LVAL_P(strncasecmp_return_zv) == 0
	) {

		/* method_exists($this,$name) */
		if (
			yii_call_user_fun_2("method_exists", &method_exists_return_zv, getThis(), name_zv) == SUCCESS && 
			Z_TYPE_P(method_exists_return_zv) == IS_BOOL && Z_BVAL_P(method_exists_return_zv) == 1
		) {
			
			/* $name=strtolower($name); */
			zend_str_tolower(Z_STRVAL_P(name_zv), Z_STRLEN_P(name_zv));

			e_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_e"), 0 TSRMLS_CC);
			
			if (Z_TYPE_P(e_zv) != IS_ARRAY) {
				YII_NEW_ARRAY(e_zv);
				add_assoc_long(e_zv, Z_STRVAL_P(name_zv), 5);
			}
			
			if (!zend_symtable_exists(Z_ARRVAL_P(e_zv), Z_STRVAL_P(name_zv), Z_STRLEN_P(name_zv)+1 ) ) {
				add_assoc_long(e_zv, Z_STRVAL_P(name_zv), 1);
			}
			
			php_var_dump(&e_zv, 1);
			php_printf("xxxxxxxxx\n");
			zval *e_name_zv;
			if (zend_symtable_find(Z_ARRVAL_P(e_zv),  Z_STRVAL_P(name_zv), Z_STRLEN_P(name_zv), (void **) &e_name_zv) ) {
				//convert_to_object(e_name_zv);
				//convert_to_long(e_name_zv);
				//php_printf("this    onononono\n");
				//php_var_dump(&e_name_zv, 1);
				
				//RETVAL_ZVAL(e_name_zv, 1, 0);
				
			}

			//$this->_e[$name]=new CList;
			//yii_update_class_property(getThis(), "_e")
			//zend_update_property(yaf_config_ini_ce, instance, ZEND_STRL(YAF_CONFIG_PROPERT_NAME), filename TSRMLS_CC);
			YII_PTR_DTOR(e_name_zv);
			YII_PTR_DTOR(e_zv);
			YII_PTR_DTOR(strncasecmp_return_zv);
			YII_PTR_DTOR(name_zv);
			YII_PTR_DTOR(on_zv);
			YII_PTR_DTOR(len_zv);

			YII_PTR_DTOR(method_exists_return_zv);

			return;

		}
	}

	YII_PTR_DTOR(strncasecmp_return_zv);
	YII_PTR_DTOR(name_zv);
	YII_PTR_DTOR(on_zv);
	YII_PTR_DTOR(len_zv);

	YII_PTR_DTOR(method_exists_return_zv);
	return;

}
/* }}} */

/** {{{ public CComponent::__set()
*/
PHP_METHOD(CComponent, __set){
	zval *getter_zv, *name_zv, *on_zv, *len_zv, *e_zv=NULL, *m_zv;
	char *name, *getter;
	int name_len, getter_len;
	zval *method_exists_return_zv=NULL, *get_zv=NULL;
	zval *strncasecmp_return_zv=NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {
		return;
	}
}
/* }}} */

/** {{{ public CComponent::__isset()
*/
PHP_METHOD(CComponent, __isset){
	php_printf("this __isset");
}
/* }}} */

/** {{{ public CComponent::__unset()
*/
PHP_METHOD(CComponent, __unset){
	php_printf("this __unset");
}
/* }}} */

/** {{{ public CComponent::__call()
*/
PHP_METHOD(CComponent, __call){
	php_printf("this __call");
}
/* }}} */

/** {{{ public CComponent::asa()
*/
PHP_METHOD(CComponent, asa){
	php_printf("this asa");
}
/* }}} */

/** {{{ public CComponent::attachBehaviors()
*/
PHP_METHOD(CComponent, attachBehaviors){
	php_printf("this attachBehaviors");
}
/* }}} */

/** {{{ public CComponent::detachBehaviors()
*/
PHP_METHOD(CComponent, detachBehaviors){
	php_printf("this detachBehaviors");
}
/* }}} */

/** {{{ public CComponent::attachBehavior()
*/
PHP_METHOD(CComponent, attachBehavior){
	php_printf("this attachBehavior");
}
/* }}} */

/** {{{ public CComponent::detachBehavior()
*/
PHP_METHOD(CComponent, detachBehavior){
	php_printf("this detachBehavior");
}
/* }}} */

/** {{{ public CComponent::enableBehaviors()
*/
PHP_METHOD(CComponent, enableBehaviors){
	php_printf("this enableBehaviors");
}
/* }}} */

/** {{{ public CComponent::disableBehaviors()
*/
PHP_METHOD(CComponent, disableBehaviors){
	php_printf("this disableBehaviors");
}
/* }}} */

/** {{{ public CComponent::enableBehavior()
*/
PHP_METHOD(CComponent, enableBehavior){
	php_printf("this enableBehavior");
}
/* }}} */

/** {{{ public CComponent::disableBehavior()
*/
PHP_METHOD(CComponent, disableBehavior){
	php_printf("this disableBehavior");
}
/* }}} */

/** {{{ public CComponent::hasProperty()
*/
PHP_METHOD(CComponent, hasProperty){
	zval *getter_zv, *setter_zv;
	char *name, *getter, *setter;
	int name_len, getter_len, setter_len;
	zval *method_exists_return_zv=NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {
		return;
	}
	
	/*  method_exists($this,'get'.$name) */
	getter_len = spprintf(&getter, 0, "get%s", name);
	YII_NEW_STRING(getter_zv, getter);
	if (
		yii_call_user_fun_2("method_exists", &method_exists_return_zv, getThis(), getter_zv) == SUCCESS &&
		Z_TYPE_P(method_exists_return_zv) == IS_BOOL && Z_BVAL_P(method_exists_return_zv) == 1
	) {
		RETVAL_TRUE;
		
		YII_PTR_DTOR(getter_zv);
		YII_PTR_DTOR(method_exists_return_zv);
		efree(getter);
		
		return;
	}
	
	YII_PTR_DTOR(getter_zv);
	YII_PTR_DTOR(method_exists_return_zv);
	efree(getter);
	
	
	/* method_exists($this,'set'.$name); */
	setter_len = spprintf(&setter, 0, "set%s", name);
	YII_NEW_STRING(setter_zv, setter);
	if (
		yii_call_user_fun_2("method_exists", &method_exists_return_zv, getThis(), setter_zv) == SUCCESS &&
		Z_TYPE_P(method_exists_return_zv) == IS_BOOL && Z_BVAL_P(method_exists_return_zv) == 1
	) {
		RETVAL_TRUE;
		
		YII_PTR_DTOR(setter_zv);
		YII_PTR_DTOR(method_exists_return_zv);
		efree(setter);
		
		return;
	}
	
	YII_PTR_DTOR(setter_zv);
	YII_PTR_DTOR(method_exists_return_zv);
	efree(setter);
	RETURN_FALSE;
}
/* }}} */

/** {{{ public CComponent::canGetProperty()
*/
PHP_METHOD(CComponent, canGetProperty){
	zval *getter_zv;
	char *name, *getter;
	int name_len, getter_len;
	zval *method_exists_return_zv=NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {
		return;
	}
	
	/*  method_exists($this,'get'.$name) */
	getter_len = spprintf(&getter, 0, "get%s", name);
	YII_NEW_STRING(getter_zv, getter);
	if (
		yii_call_user_fun_2("method_exists", &method_exists_return_zv, getThis(), getter_zv) == SUCCESS &&
		Z_TYPE_P(method_exists_return_zv) == IS_BOOL && Z_BVAL_P(method_exists_return_zv) == 1
	) {
		RETVAL_TRUE;
		
		YII_PTR_DTOR(getter_zv);
		YII_PTR_DTOR(method_exists_return_zv);
		efree(getter);
		
		return;
	}
	
	YII_PTR_DTOR(getter_zv);
	YII_PTR_DTOR(method_exists_return_zv);
	efree(getter);
}
/* }}} */

/** {{{ public CComponent::canSetProperty()
*/
PHP_METHOD(CComponent, canSetProperty){
	zval *setter_zv;
	char *name, *setter;
	int name_len, setter_len;
	zval *method_exists_return_zv=NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {
		return;
	}
	
	/* method_exists($this,'set'.$name); */
	setter_len = spprintf(&setter, 0, "set%s", name);
	YII_NEW_STRING(setter_zv, setter);
	if (
		yii_call_user_fun_2("method_exists", &method_exists_return_zv, getThis(), setter_zv) == SUCCESS &&
		Z_TYPE_P(method_exists_return_zv) == IS_BOOL && Z_BVAL_P(method_exists_return_zv) == 1
	) {
		RETVAL_TRUE;
		
		YII_PTR_DTOR(setter_zv);
		YII_PTR_DTOR(method_exists_return_zv);
		efree(setter);
		
		return;
	}
	
	YII_PTR_DTOR(setter_zv);
	YII_PTR_DTOR(method_exists_return_zv);
	efree(setter);
	RETURN_FALSE;
}
/* }}} */

/** {{{ public CComponent::hasEvent()
*/
PHP_METHOD(CComponent, hasEvent){
	php_printf("this hasEvent");
}
/* }}} */

/** {{{ public CComponent::hasEventHandler()
*/
PHP_METHOD(CComponent, hasEventHandler){
	php_printf("this hasEventHandler");
}
/* }}} */

/** {{{ public CComponent::getEventHandlers()
*/
PHP_METHOD(CComponent, getEventHandlers){
	php_printf("this getEventHandlers");
}
/* }}} */

/** {{{ public CComponent::attachEventHandler()
*/
PHP_METHOD(CComponent, attachEventHandler){
	php_printf("this attachEventHandler");
}
/* }}} */

/** {{{ public CComponent::detachEventHandler()
*/
PHP_METHOD(CComponent, detachEventHandler){
	php_printf("this detachEventHandler");
}
/* }}} */

/** {{{ public CComponent::raiseEvent()
*/
PHP_METHOD(CComponent, raiseEvent){
	php_printf("this raiseEvent");
}
/* }}} */

/** {{{ public CComponent::evaluateExpression()
*/
PHP_METHOD(CComponent, evaluateExpression){
	php_printf("this evaluateExpression");
}
/* }}} */

/** {{{ YII_CLASS_METHODS
*/
YII_CLASS_METHODS(ccomponent) {
	PHP_ME(CComponent, __get, arginfo_ccomponent___get, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, __set, arginfo_ccomponent___set, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, __isset, arginfo_ccomponent___isset, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, __unset, arginfo_ccomponent___unset, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, __call, arginfo_ccomponent___call, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, asa, arginfo_ccomponent_asa, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, attachBehaviors, arginfo_ccomponent_attachBehaviors, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, detachBehaviors, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, attachBehavior, arginfo_ccomponent_attachBehavior, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, detachBehavior, arginfo_ccomponent_detachBehavior, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, enableBehaviors, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, disableBehaviors, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, enableBehavior, arginfo_ccomponent_enableBehavior, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, disableBehavior, arginfo_ccomponent_disableBehavior, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, hasProperty, arginfo_ccomponent_hasProperty, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, canGetProperty, arginfo_ccomponent_canGetProperty, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, canSetProperty, arginfo_ccomponent_canSetProperty, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, hasEvent, arginfo_ccomponent_hasEvent, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, hasEventHandler, arginfo_ccomponent_hasEventHandler, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, getEventHandlers, arginfo_ccomponent_getEventHandlers, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, attachEventHandler, arginfo_ccomponent_attachEventHandler, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, detachEventHandler, arginfo_ccomponent_detachEventHandler, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, raiseEvent, arginfo_ccomponent_raiseEvent, ZEND_ACC_PUBLIC)
	PHP_ME(CComponent, evaluateExpression, arginfo_ccomponent_evaluateExpression, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/** {{{ Class CComponent
*/
YII_CLASS_FUNCTION(ccomponent) {
	//AUTO CALL CLASS METHOD
	YII_CLASS_DECLARE(CComponent, ccomponent, 0);
	
	zend_declare_property_null(YII_CLASS_ENTRY(ccomponent), YII_SL("_e"), ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);
	zend_declare_property_null(YII_CLASS_ENTRY(ccomponent), YII_SL("_m"), ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);
	return SUCCESS;
}
/* }}} */
