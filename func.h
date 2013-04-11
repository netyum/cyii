void yii_concat(zval **left, zval *right TSRMLS_DC);

/* call global function */
int yii_call_user_fun(const char *function_name, zval **retval_ptr_ptr, zend_uint param_count, zval **params[]);
int yii_call_user_fun_1(const char *func_name, zval **retval, zval *param);
int yii_call_user_fun_2(const char *func_name, zval **retval, zval *param1, zval *param2);
int yii_call_user_fun_3(const char *func_name, zval **retval, zval *param1, zval *param2, zval *param3);

/* call class method */
int yii_call_class_method(zval *object, char *method_name, zval **retval_prt_prt, zend_uint param_count, zval **params[]);
int yii_call_class_method_0(zval *object, char *method_name, zval **retval);

/* update class property */
void yii_update_class_property(zval *object, const char *property_name, zval *value);
void yii_read_class_property(zval *object, const char *property_name, zval **retval);


int yii_find_scope(zend_class_entry *ce, char *method_name TSRMLS_DC);


