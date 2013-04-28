#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */
#include "ext/standard/php_var.h"
#include "php_yii.h"
#include "func.h"


void yii_inherit_not_found(char *class_name, char *inherit_name) {
	fprintf(stderr, "Error: Class to extend '%s' was not found when registering class '%s'\n", class_name, inherit_name);
}

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

int yii_call_class_static_method(zval *object, char *class_name, char *method_name, zval **retval_ptr_ptr, zend_uint param_count, zval **params[]) {
	
	zval *method_name_zv, *class_name_zv, *fn;
	int status = FAILURE;
	zend_class_entry *ce, *active_scope = NULL;


	/*if (Z_TYPE_P(object) != IS_OBJECT) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Call to method %s() on a non object", method_name);
		return FAILURE;
	}*/

	if (object) {
		active_scope = EG(scope);
		ce = Z_OBJCE_P(object);
		if (ce->parent) {
			yii_find_scope(ce, method_name TSRMLS_CC);
		}
	}

	ALLOC_INIT_ZVAL(fn);
	array_init_size(fn, 2);

	YII_NEW_STRING(class_name_zv, class_name);
	add_next_index_zval(fn, class_name_zv);
	YII_NEW_STRING(method_name_zv, method_name);
	add_next_index_zval(fn, method_name_zv);
	status = call_user_function_ex(CG(function_table), NULL, fn, retval_ptr_ptr, param_count, params, 1, NULL TSRMLS_CC);

	if (object) {
		EG(scope) = active_scope;
	}
	
	YII_PTR_DTOR(method_name_zv);
	YII_PTR_DTOR(class_name_zv);
	YII_PTR_DTOR(fn);
	return status;
}

int yii_call_class_static_method_0(zval *object, char *class_name, char *method_name, zval **retval) {
	return yii_call_class_static_method(object, class_name, method_name, retval, 0, NULL);
}

int yii_call_class_static_method_0_no(zval *object, char *class_name, char *method_name) {
	zval *retval;
	int status;
	status = yii_call_class_static_method(object, class_name, method_name, &retval, 0, NULL);
	YII_PTR_DTOR(retval);
	return status;
}

int yii_call_class_static_method_1(zval *object, char *class_name, char *method_name, zval **retval, zval *param) {
	zval **params[1];
	params[0] = &param;
	return yii_call_class_static_method(object, class_name, method_name, retval, 1, params);
}

int yii_call_class_static_method_1_no(zval *object, char *class_name, char *method_name, zval *param) {
	zval *retval;
	int status;
	zval **params[1];
	params[0] = &param;
	status = yii_call_class_static_method(object, class_name, method_name, &retval, 1, params);
	YII_PTR_DTOR(retval);
	return status;
}

int yii_call_class_static_method_2(zval *object, char *class_name, char *method_name, zval **retval, zval *param1, zval *param2) {
	zval **params[2];
	params[0] = &param1;
	params[1] = &param2;
	return yii_call_class_static_method(object, class_name, method_name, retval, 2, params);
}

int yii_call_class_static_method_2_no(zval *object, char *class_name, char *method_name, zval *param1, zval *param2) {
	zval *retval;
	int status;
	zval **params[2];
	params[0] = &param1;
	params[1] = &param2;
	status = yii_call_class_static_method(object, class_name, method_name, &retval, 2, params);
	YII_PTR_DTOR(retval);
	return status;
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

int yii_call_user_fun_0_no(const char *func_name) {
	zval *retval;
	int status;
	status = yii_call_user_fun(func_name, &retval, 0, NULL);
	YII_PTR_DTOR(retval);
	return status;
}

int yii_call_user_fun_1(const char *func_name, zval **retval, zval *param) {
	zval **params[1];
	params[0] = &param;
	
	if (yii_call_user_fun(func_name, retval, 1, params) == FAILURE) {
		return FAILURE;
	}
	return SUCCESS;
}

int yii_call_user_fun_1_no(const char *func_name, zval *param) {
	zval **params[1], *retval;
	int status;
	params[0] = &param;
	status = yii_call_user_fun(func_name, &retval, 1, params);
	YII_PTR_DTOR(retval);
	return status;
}

int yii_call_user_fun_2(const char *func_name, zval **retval, zval *param1, zval *param2) {
	zval **params[2];
	params[0] = &param1; params[1] = &param2;
	
	if (yii_call_user_fun(func_name, retval, 2, params) == FAILURE) {
		return FAILURE;
	}
	return SUCCESS;
}

int yii_call_user_fun_2_no(const char *func_name, zval *param1, zval *param2) {
	zval **params[2], *retval;
	int status;
	params[0] = &param1; params[1] = &param2;
	status = yii_call_user_fun(func_name, &retval, 2, params);
	YII_PTR_DTOR(retval);
	return status;
}

int yii_call_user_fun_3(const char *func_name, zval **retval, zval *param1, zval *param2, zval *param3) {
	zval **params[3];
	params[0] = &param1; params[1] = &param2; params[2] = &param3;
	
	if (yii_call_user_fun(func_name, retval, 3, params) == FAILURE) {
		return FAILURE;
	}
	return SUCCESS;
}

int yii_call_user_fun_3_no(const char *func_name, zval *param1, zval *param2, zval *param3) {
	zval **params[3], *retval;
	int status;
	params[0] = &param1; params[1] = &param2; params[2] = &param3;
	status = yii_call_user_fun(func_name, &retval, 3, params);
	YII_PTR_DTOR(retval);
	return status;
}

int yii_call_user_fun_4(const char *func_name, zval **retval, zval *param1, zval *param2, zval *param3, zval *param4) {
	zval **params[4];
	params[0] = &param1; params[1] = &param2; params[2] = &param3; params[3] = &param4;
	
	if (yii_call_user_fun(func_name, retval, 4, params) == FAILURE) {
		return FAILURE;
	}
	return SUCCESS;
}

int yii_call_user_fun_4_no(const char *func_name, zval *param1, zval *param2, zval *param3, zval *param4) {
	zval **params[4], *retval;
	int status;
	params[0] = &param1; params[1] = &param2; params[2] = &param3; params[3] = &param4;
	status = yii_call_user_fun(func_name, &retval, 4, params);
	YII_PTR_DTOR(retval);
	return status;
}

int yii_call_user_fun_5(const char *func_name, zval **retval, zval *param1, zval *param2, zval *param3, zval *param4, zval *param5) {
	zval **params[5];
	params[0] = &param1; params[1] = &param2; params[2] = &param3; params[3] = &param4; params[4] = &param5;
	
	if (yii_call_user_fun(func_name, retval, 5, params) == FAILURE) {
		return FAILURE;
	}
	return SUCCESS;
}

int yii_call_user_fun_5_no(const char *func_name, zval *param1, zval *param2, zval *param3, zval *param4, zval *param5) {
	zval **params[5], *retval;
	int status;
	params[0] = &param1; params[1] = &param2; params[2] = &param3; params[3] = &param4; params[4] = &param5;
	status = yii_call_user_fun(func_name, &retval, 5, params);
	YII_PTR_DTOR(retval);
	return status;
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
	if (ce->parent) {
		yii_find_scope(ce, method_name TSRMLS_CC);
	} else {
		EG(scope) = ce;
	}
	
	if (call_user_function_ex(&ce->function_table, &object, func_name, retval_ptr_ptr, param_count, params, 0, NULL TSRMLS_CC) == FAILURE) {
		return FAILURE;
	}
	
	YII_PTR_DTOR(func_name);
	return SUCCESS;
}

int yii_call_class_method_no(zval *object, char *method_name, zend_uint param_count, zval **params[]) {
	zval *retval;
	int status;
	status = yii_call_class_method(object, method_name, &retval, param_count, params);
	YII_PTR_DTOR(retval);
	return status;
}

int yii_call_class_method_0(zval *object, char *method_name, zval **retval) {
	return yii_call_class_method(object, method_name, retval, 0, NULL);
}

int yii_call_class_method_0_no(zval *object, char *method_name) {
	zval *retval;
	int status;
	status = yii_call_class_method(object, method_name, &retval, 0, NULL);
	YII_PTR_DTOR(retval);
	return status;
}

int yii_call_class_method_1(zval *object, char *method_name, zval **retval, zval *param) {
	zval **params[1];
	params[0] = &param;
	return yii_call_class_method(object, method_name, retval, 1, params);
}

int yii_call_class_method_1_no(zval *object, char *method_name, zval *param) {
	zval **params[1], *retval;
	params[0] = &param;
	int status;
	status = yii_call_class_method(object, method_name, &retval, 1, params);
	YII_PTR_DTOR(retval);
	return status;
}

int yii_call_class_method_2(zval *object, char *method_name, zval **retval, zval *param1, zval *param2) {
	zval **params[2];
	params[0] = &param1;
	params[1] = &param2;
	return yii_call_class_method(object, method_name, retval, 2, params);
}

int yii_call_class_method_2_no(zval *object, char *method_name, zval *param1, zval *param2) {
	zval **params[2], *retval;
	params[0] = &param1;
	params[1] = &param2;
	int status;
	status = yii_call_class_method(object, method_name, &retval, 2, params);
	YII_PTR_DTOR(retval);
	return status;
}

int yii_find_scope(zend_class_entry *ce, char *method_name TSRMLS_DC){

	char *lcname = zend_str_tolower_dup(method_name, strlen(method_name));
	unsigned long hash = zend_inline_hash_func(lcname, strlen(method_name)+1);

	while (ce) {
		if (zend_hash_quick_exists(&ce->function_table, lcname, strlen(method_name)+1, hash)) {
			EG(scope) = ce;
			efree(lcname);
			return SUCCESS;
		}
		ce = ce->parent;
	}

	if (lcname) {
		efree(lcname);
	}

	return FAILURE;
}

int yii_class_has_constructor(zval *object TSRMLS_DC){

	zend_class_entry *ce = Z_OBJCE_P(object);

	while (ce) {
		if (ce->constructor) {
			return 1;
		}
		ce = ce->parent;
	}

	return 0;
}

int yii_new_class_instance(zval **return_value, char *class_name, zend_uint param_count, zval **params[] TSRMLS_DC){
	zend_class_entry *ce;
	ce = zend_fetch_class(class_name, strlen(class_name), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	if (!ce) {
		return FAILURE;
	}

	ALLOC_INIT_ZVAL(*return_value);
	object_init_ex(*return_value, ce);
	if (yii_class_has_constructor(*return_value TSRMLS_CC)) {
		if (yii_call_class_method_no(*return_value, "__construct" , param_count, params) == FAILURE) {
			YII_PTR_DTOR(*return_value);
			return FAILURE;
		}
	}
	return SUCCESS;
}

int yii_new_class_instance_0(zval **return_value, char *class_name TSRMLS_DC) {
	return yii_new_class_instance(return_value, class_name, 0, NULL);
}

int yii_new_class_instance_1(zval **return_value, char *class_name, zval *param TSRMLS_DC) {
	zval **params[1];
	params[0] = &param;
	return yii_new_class_instance(return_value, class_name, 1, params);

}
