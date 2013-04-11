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
/* }}} */

/** {{{ string static public YiiBase::getVersion()
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
			if (yii_call_class_method_0(getThis(), "getinit", &get_zv) == SUCCESS) {
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
			}
			
			
			if (!zend_symtable_exists(Z_ARRVAL_P(e_zv), Z_STRVAL_P(name_zv), Z_STRLEN_P(name_zv)+1 ) ) {
				add_assoc_long(e_zv, Z_STRVAL_P(name_zv), 1);
			}
			
			php_var_dump(&e_zv, 1);
			
			//$this->_e[$name]=new CList;
			//yii_update_class_property(getThis(), "_e")
			//zend_update_property(yaf_config_ini_ce, instance, ZEND_STRL(YAF_CONFIG_PROPERT_NAME), filename TSRMLS_CC);
			
			
			YII_PTR_DTOR(e_zv);
			YII_PTR_DTOR(strncasecmp_return_zv);
			YII_PTR_DTOR(name_zv);
			YII_PTR_DTOR(on_zv);
			YII_PTR_DTOR(len_zv);

			YII_PTR_DTOR(method_exists_return_zv);
			
			php_printf("the on\n");
			return;
			
			//
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

/** {{{ YII_CLASS_METHODS
*/
YII_CLASS_METHODS(ccomponent) {
	PHP_ME(CComponent, __get, arginfo_ccomponent___get, ZEND_ACC_PUBLIC)
	
	//PHP_ME(CComponent, getVersion, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC) //静态方法
	//PHP_ME(CComponent, createWebApplication, arginfo_yiibase_createWebApplication, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC) //静态方法
	//PHP_ME(CComponent, createConsoleApplication, arginfo_yiibase_createConsoleApplication, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC) //静态方法
	//PHP_ME(CComponent, createApplication, arginfo_yiibase_createApplication, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC) //静态方法
	//PHP_ME(CComponent, app, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC) //静态方法
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
	
	
	//zend_declare_property_bool(YII_CLASS_ENTRY(ccomponent), YII_SL("enableIncludePath"), 0, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC TSRMLS_CC);


	return SUCCESS;
}
/* }}} */