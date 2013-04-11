#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"


#include "func.h"

void yii_concat(zval **left, zval *right TSRMLS_DC){

	zval left_copy, right_copy;
	uint length;
	int use_copy_left = 0, use_copy_right = 0;

	if (Z_TYPE_P(right) != IS_STRING) {
		return;
	}

	if (Z_TYPE_PP(left) == IS_NULL) {

		Z_STRVAL_PP(left) = emalloc(Z_STRLEN_P(right)+1);
		memcpy(Z_STRVAL_PP(left), Z_STRVAL_P(right), Z_STRLEN_P(right));
		Z_STRVAL_PP(left)[Z_STRLEN_P(right)] = 0;
		Z_STRLEN_PP(left) = Z_STRLEN_P(right);
		Z_TYPE_PP(left) = IS_STRING;

		if (use_copy_right) {
			zval_dtor(&right_copy);
		}

		return;
	}

	if (Z_TYPE_PP(left) != IS_STRING) {
		return;
	}

	length = Z_STRLEN_PP(left) + Z_STRLEN_P(right);
	Z_STRVAL_PP(left) = erealloc(Z_STRVAL_PP(left), length+1);

	memcpy(Z_STRVAL_PP(left) + Z_STRLEN_PP(left), Z_STRVAL_P(right), Z_STRLEN_P(right));
	Z_STRVAL_PP(left)[length] = 0;
	Z_STRLEN_PP(left) = length;
	Z_TYPE_PP(left) = IS_STRING;

	if (use_copy_left) {
		zval_dtor(&left_copy);
	}

	if (use_copy_right) {
		zval_dtor(&right_copy);
	}
}


int yii_call_user_fun(const char *function_name, zval **retval_ptr_ptr, zend_uint param_count, zval **params[]) {
	TSRMLS_FETCH();
	zval *func_name;
	YII_NEW_STRING(func_name, function_name);
	 
	if (call_user_function_ex(EG(function_table), NULL, func_name, retval_ptr_ptr, param_count, params, 1, NULL TSRMLS_CC) == FAILURE) {
		return FAILURE;
	}
	YII_PTR_DTOR(func_name);
	return SUCCESS;
}

int yii_call_user_fun_0(const char *func_name, zval **retval) {
	if (yii_call_user_fun(func_name, retval, 0, NULL) == FAILURE) {
		return FAILURE;
	}
	return SUCCESS;
}

int yii_call_user_fun_1(const char *func_name, zval **retval, zval *param) {
	zval **params[1];
	params[0] = &param;
	
	if (yii_call_user_fun(func_name, retval, 1, params) == FAILURE) {
		return FAILURE;
	}
	return SUCCESS;
}

int yii_call_user_fun_2(const char *func_name, zval **retval, zval *param1, zval *param2) {
	zval **params[2];
	params[0] = &param1;
	params[1] = &param2;
	
	if (yii_call_user_fun(func_name, retval, 2, params) == FAILURE) {
		return FAILURE;
	}
	return SUCCESS;
}

int yii_call_user_fun_3(const char *func_name, zval **retval, zval *param1, zval *param2, zval *param3) {
	zval **params[3];
	params[0] = &param1;
	params[1] = &param2;
	params[2] = &param3;
	
	if (yii_call_user_fun(func_name, retval, 3, params) == FAILURE) {
		return FAILURE;
	}
	return SUCCESS;
}


int yii_call_class_method(zval *object, char *method_name, zval **retval_ptr_ptr, zend_uint param_count, zval **params[]) {
	TSRMLS_FETCH();
	zend_class_entry *ce;
	zval *func_name;
	
	YII_NEW_STRING(func_name, method_name);
	
	if (Z_TYPE_P(object) != IS_OBJECT) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Call to method %s() on a non object", method_name);
		return FAILURE;
	}

	
	ce = Z_OBJCE_P(object);
	EG(scope) = ce;
	
	if (call_user_function_ex(&ce->function_table, &object, func_name, NULL, param_count, params, 0, NULL TSRMLS_CC) == FAILURE) {
		return FAILURE;
	}
	
	YII_PTR_DTOR(func_name);
	return SUCCESS;
}

int yii_call_class_method_0(zval *object, char *method_name, zval **retval) {
	//if (yii_call_class_method(object, method_name, retval, 0, NULL) == FAILURE) {
	//	return FAILURE;
	//}
	TSRMLS_FETCH();
	zend_class_entry *ce;
	
	ce = Z_OBJCE_P(object);
	EG(scope) = ce;
	
	zend_call_method(&object, ce, NULL, YII_SL(method_name), retval, 0, NULL, NULL TSRMLS_CC);
	return SUCCESS;
}

/*
void yii_update_class_property(zval *object, const char *property_name, zval *value) {
	TSRMLS_FETCH();
	zend_class_entry *ce;
	
	ce = Z_OBJCE_P(object);
	EG(scope) = ce;
	
	zend_update_property(ce, object, property_name, strlen(property_name), value TSRMLS_CC);
}*/

void yii_read_class_property(zval *object, const char *property_name, zval **retval) {
	TSRMLS_FETCH();
	zend_class_entry *ce;
	
	ce = Z_OBJCE_P(object);
	//EG(scope) = ce;
	
	*retval = zend_read_property(ce, object, property_name, strlen(property_name), 1 TSRMLS_CC);
}