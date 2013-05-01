#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */
#include "ext/standard/php_var.h"
#include "ext/spl/spl_iterators.h"
#include "php_yii.h"
#include "func.h"

#include "system/base/yii_ccomponent.h"
#include "system/collections/yii_cmap.h"
#include "system/collections/yii_cmapiterator.h"

YII_CLASS_DECLARE_ENTRY(cmap);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_cmap___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, readOnly)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cmap_setReadOnly, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cmap_itemAt, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cmap_add, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cmap_remove, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cmap_contains, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cmap_copyFrom, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cmap_mergeWith, 0, 0, 2)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, recursive)
ZEND_END_ARG_INFO()

// static
ZEND_BEGIN_ARG_INFO_EX(arginfo_cmap_mergeArray, 0, 0, 2)
	ZEND_ARG_ARRAY_INFO(0, a, 0)
	ZEND_ARG_ARRAY_INFO(0, b, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cmap_offsetExists, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cmap_offsetGet, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cmap_offsetSet, 0, 0, 2)
	ZEND_ARG_INFO(0, offset)
	ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cmap_offsetUnset, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()
/* }}} */


/** {{{ public CMap::__construct()
*/
PHP_METHOD(CMap, __construct){
	zval *data_zv=NULL, *readOnly_zv=NULL, *d_zv;
	int *readOnly=0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|zb", &data_zv, &readOnly) == FAILURE) {
		return;
	}
	
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
	//if not array is init 
	if ( Z_TYPE_P(d_zv) != IS_ARRAY ) {
		YII_NEW_ARRAY(d_zv);
		zend_update_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), d_zv TSRMLS_CC);
		YII_PTR_DTOR(d_zv);
	}


	if (!data_zv) {
		YII_NEW_NULL(data_zv);
	}

	if (Z_TYPE_P(data_zv) != IS_NULL) {
		if (yii_call_class_method_1_no(getThis(), "copyFrom", data_zv) != SUCCESS) {
			return;
		}
	}
	
}
/* }}} */

/** {{{ public CMap::getReadOnly()
*/
PHP_METHOD(CMap, getReadOnly){
	zval *r_zv;
	r_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_r"), 0 TSRMLS_CC);
	RETURN_ZVAL(r_zv, 1, 0);
}
/* }}} */

/** {{{ public CMap::setReadOnly()
*/
PHP_METHOD(CMap, setReadOnly){
	int value;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &value) == FAILURE) {
		return;
	}
	
	zend_update_property_bool(Z_OBJCE_P(getThis()), getThis(), YII_SL("_r"), value TSRMLS_CC);

}
/* }}} */

/** {{{ public CMap::getIterator()
*/
PHP_METHOD(CMap, getIterator){
	zval *retval, *d_zv;
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
	if (yii_new_class_instance_1(&retval, "CMapIterator", d_zv) == SUCCESS) {
		RETVAL_ZVAL(retval, 1, 0);
		YII_PTR_DTOR(retval);
		return;
	}
	YII_PTR_DTOR(retval);
	return;
}
/* }}} */

/** {{{ public CMap::count()
*/
PHP_METHOD(CMap, count){
	zval *retval;
	yii_call_class_method_0(getThis(), "getCount", &retval);
	RETVAL_LONG(Z_LVAL_P(retval));
	YII_PTR_DTOR(retval);
	return;
}
/* }}} */

/** {{{ public CMap::getCount()
*/
PHP_METHOD(CMap, getCount){
	zval *d_zv;
	int d_zv_count;
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
	d_zv_count = zend_hash_num_elements(Z_ARRVAL_P(d_zv));
	RETVAL_LONG(d_zv_count);
	return;
}
/* }}} */

/** {{{ public CMap::getKeys()
*/
PHP_METHOD(CMap, getKeys){
	zval *retval, *d_zv;
	
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);

	if (yii_call_user_fun_1("array_keys", &retval, d_zv) == SUCCESS) {
		RETVAL_ZVAL(retval, 1, 0);
		YII_PTR_DTOR(retval);
		return;
	}
	YII_PTR_DTOR(retval);
	return;
}
/* }}} */

/** {{{ public CMap::itemAt()
*/
PHP_METHOD(CMap, itemAt){
	zval **find_zv, *d_zv, *key_zv;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &key_zv) == FAILURE) {
		return;
	}

	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);

	/* if(isset($this->_d[$key])) */
	if ( Z_TYPE_P(key_zv) == IS_LONG ) {
		if (zend_hash_index_find(Z_ARRVAL_P(d_zv), Z_LVAL_P(key_zv), (void **)&find_zv) == SUCCESS) {
			RETVAL_ZVAL(*find_zv, 1, 0);
			return;
		}
		else {
			RETURN_NULL();
		}
	}
	else if ( Z_TYPE_P(key_zv) == IS_BOOL ) {
		if (zend_hash_index_find(Z_ARRVAL_P(d_zv), Z_BVAL_P(key_zv), (void **)&find_zv) == SUCCESS) {
			RETVAL_ZVAL(*find_zv, 1, 0);
			return;
		}
		else {
			RETURN_NULL();
		}
	}
	else if ( Z_TYPE_P(key_zv) == IS_STRING ) {
		if (zend_hash_find(Z_ARRVAL_P(d_zv), Z_STRVAL_P(key_zv), Z_STRLEN_P(key_zv), (void **)&find_zv) == SUCCESS) {
			RETVAL_ZVAL(*find_zv, 1, 0);
			return;
		}
		else {
			RETURN_NULL();
		}
	}
	else {
		RETURN_NULL();
	}
}
/* }}} */

/** {{{ public CMap::add()
*/
PHP_METHOD(CMap, add){
	zval *key_zv;
	zval *value_zv, *copy_value_zv, *d_zv, *r_zv;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &key_zv, &value_zv) == FAILURE) {
		return;
	}
	
	r_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_r"), 0 TSRMLS_CC);

	if (Z_BVAL_P(r_zv) == 0) {
		d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
		if (Z_TYPE_P(key_zv) == IS_NULL || Z_TYPE_P(key_zv) == IS_LONG) {
			switch(Z_TYPE_P(value_zv)) {
				case IS_LONG:
					add_next_index_long(d_zv, Z_LVAL_P(value_zv));
					break;
				case IS_NULL:
					add_next_index_null(d_zv);
					break;
				case IS_BOOL:
					add_next_index_bool(d_zv, Z_BVAL_P(value_zv));
					break;
				case IS_RESOURCE:
					add_next_index_resource(d_zv, Z_RESVAL_P(value_zv));
					break;
				case IS_DOUBLE:
					add_next_index_double(d_zv, Z_DVAL_P(value_zv));
					break;
				case IS_STRING:
					add_next_index_stringl(d_zv, Z_STRVAL_P(value_zv), Z_STRLEN_P(value_zv), 1);
					break;
				default:
					add_next_index_zval(d_zv, value_zv);
			}
		}
		else if (Z_TYPE_P(key_zv) == IS_STRING) {
			switch(Z_TYPE_P(value_zv)) {
				case IS_LONG:
					add_assoc_long(d_zv, Z_STRVAL_P(key_zv), Z_LVAL_P(value_zv));
					break;
				case IS_NULL:
					add_assoc_null(d_zv, Z_STRVAL_P(key_zv));
					break;
				case IS_BOOL:
					add_assoc_bool(d_zv, Z_STRVAL_P(key_zv), Z_BVAL_P(value_zv));
					break;
				case IS_RESOURCE:
					add_assoc_resource(d_zv, Z_STRVAL_P(key_zv), Z_RESVAL_P(value_zv));
					break;
				case IS_DOUBLE:
					add_assoc_double(d_zv, Z_STRVAL_P(key_zv), Z_DVAL_P(value_zv));
					break;
				case IS_STRING:
					add_assoc_stringl(d_zv, Z_STRVAL_P(key_zv), Z_STRVAL_P(value_zv), Z_STRLEN_P(value_zv), 1);
					break;
				default:
					add_assoc_zval(d_zv, Z_STRVAL_P(key_zv), value_zv);
			}
		}
		zend_update_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), d_zv TSRMLS_CC);
		
	}
	else {
		php_printf("The map is read only.'\n");
	}
}
/* }}} */

/** {{{ public CMap::remove()
*/
PHP_METHOD(CMap, remove){
	zval *key_zv, *r_zv, *d_zv, **find_zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &key_zv) == FAILURE) {
		return;
	}

	r_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_r"), 0 TSRMLS_CC);

	if (Z_BVAL_P(r_zv) == 0) {
		d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);

		/* if(isset($this->_d[$key])) */
		if ( Z_TYPE_P(key_zv) == IS_LONG ) {
			if (zend_hash_index_find(Z_ARRVAL_P(d_zv), Z_LVAL_P(key_zv), (void **)&find_zv) == SUCCESS) {
				RETVAL_ZVAL(*find_zv, 1, 0);
				if (zend_hash_index_del(Z_ARRVAL_P(d_zv), Z_LVAL_P(key_zv))) {
					return;
				}
				RETURN_NULL();
			}
			else {
				RETURN_NULL();
			}
		}
		else if ( Z_TYPE_P(key_zv) == IS_BOOL ) {
			if (zend_hash_index_find(Z_ARRVAL_P(d_zv), Z_BVAL_P(key_zv), (void **)&find_zv) == SUCCESS) {
				RETVAL_ZVAL(*find_zv, 1, 0);
				if (zend_hash_index_del(Z_ARRVAL_P(d_zv), Z_BVAL_P(key_zv))) {
					return;
				}
				RETURN_NULL();
			}
			else {
				RETURN_NULL();
			}
		}
		else if ( Z_TYPE_P(key_zv) == IS_STRING ) {
			if (zend_hash_find(Z_ARRVAL_P(d_zv), Z_STRVAL_P(key_zv), Z_STRLEN_P(key_zv), (void **)&find_zv) == SUCCESS) {
				RETVAL_ZVAL(*find_zv, 1, 0);
				if (zend_hash_del(Z_ARRVAL_P(d_zv), Z_STRVAL_P(key_zv), Z_STRLEN_P(key_zv))) {
					return;
				}
				RETURN_NULL();
			}
			else {
				RETURN_NULL();
			}
		}
	}
	else {
		php_printf("The map is read only.'\n");
	}
	
}
/* }}} */

/** {{{ public CMap::clear()
*/
PHP_METHOD(CMap, clear){
	zval *d_zv, *keys_zv, **z_item;
	int count, i;

	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);

	if (yii_call_user_fun_1("array_keys", &keys_zv, d_zv) == SUCCESS) {
		
		if (Z_TYPE_P(keys_zv) == IS_ARRAY) {
		    count = zend_hash_num_elements(Z_ARRVAL_P(keys_zv));
		    zend_hash_internal_pointer_reset(Z_ARRVAL_P(keys_zv));
		
		    for (i = 0; i < count; i ++) {
				zend_hash_get_current_data(Z_ARRVAL_P(keys_zv), (void**) &z_item);
				yii_call_class_method_1_no(getThis(), "remove", *z_item);
				zend_hash_move_forward(Z_ARRVAL_P(keys_zv));
			}
		}
		
		YII_PTR_DTOR(keys_zv);
		return;
	}
	YII_PTR_DTOR(keys_zv);
}
/* }}} */

/** {{{ public CMap::contains()
*/
PHP_METHOD(CMap, contains){
	zval *d_zv, *key_zv, *retval;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &key_zv) == FAILURE) {
		return;
	}

	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);

	if (yii_call_user_fun_2("array_key_exists", &retval, key_zv, d_zv) == SUCCESS) {
		RETVAL_ZVAL(retval, 1, 0);
		YII_PTR_DTOR(retval);
		return;
	}
	YII_PTR_DTOR(retval);
	RETURN_FALSE;
}
/* }}} */

/** {{{ public CMap::toArray()
*/
PHP_METHOD(CMap, toArray){
	zval *d_zv;
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
	RETVAL_ZVAL(d_zv, 1, 0);
	return;
}
/* }}} */

/** {{{ public CMap::copyFrom()
*/
PHP_METHOD(CMap, copyFrom){
	zval *data_zv, *d_zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &data_zv) == FAILURE) {
		return;
	}

	if ( Z_TYPE_P(data_zv) != IS_ARRAY && Z_TYPE_P(data_zv) != IS_OBJECT && Z_TYPE_P(data_zv)!=IS_NULL) {
		php_printf("yii','Map data must be an array or an object implementing Traversable.'\n");
		return;
	}
	else if (Z_TYPE_P(data_zv) == IS_OBJECT && Z_OBJ_HT_P(data_zv)->get_class_entry && !instanceof_function(Z_OBJCE_P(data_zv), zend_ce_traversable TSRMLS_CC)) {
		php_printf("yii','Map data must be an array or an object implementing Traversable.'\n");
		return;
	}

	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
	int d_zv_count;
	d_zv_count = zend_hash_num_elements(Z_ARRVAL_P(d_zv));
	if ( d_zv_count > 0 ) {
		if (yii_call_class_method_0_no(getThis(), "clear") != SUCCESS) {
			return;
		}
	}

	if (Z_TYPE_P(data_zv) == IS_OBJECT && Z_OBJ_HT_P(data_zv)->get_class_entry && instanceof_function(Z_OBJCE_P(data_zv), zend_ce_traversable TSRMLS_CC)) {

		if (Z_OBJ_HT_P(data_zv)->get_class_entry && instanceof_function(Z_OBJCE_P(data_zv), YII_CLASS_ENTRY(cmap) TSRMLS_CC)) {
			//zend_ce_arrayaccess foreach
			zval *data;
			yii_call_class_method_0(data_zv, "toArray", &data);
			if (Z_TYPE_P(data) == IS_ARRAY) {
				int count, i;
				zval **z_item;
				// 获取数组大小
			    count = zend_hash_num_elements(Z_ARRVAL_P(data));
			    // 将数组的内部指针指向第一个单元
			    zend_hash_internal_pointer_reset(Z_ARRVAL_P(data));
			    for (i = 0; i < count; i ++) {
					char *key; int idx;
					zval *key_zv, *idx_zv, *item_zv;
			        // 获取当前数据
			        zend_hash_get_current_data(Z_ARRVAL_P(data), (void**) &z_item);
					ALLOC_INIT_ZVAL(item_zv);
					ZVAL_ZVAL(item_zv, *z_item, 1, 0);
					if (zend_hash_get_current_key(Z_ARRVAL_P(data), &key, (unsigned long *)&idx, 0) == HASH_KEY_IS_STRING) {
						YII_NEW_STRING(key_zv, key);
						if (yii_call_class_method_2_no(getThis(), "add", key_zv, item_zv) != SUCCESS) {
							return;
						}
						YII_PTR_DTOR(key_zv);
					}
					else {
						YII_NEW_LONG(idx_zv, idx);
						if (yii_call_class_method_2_no(getThis(), "add", idx_zv, item_zv) != SUCCESS) {
							return;
						}
						YII_PTR_DTOR(idx_zv);
					}
					
					if (Z_TYPE_P(item_zv) != IS_ARRAY && Z_TYPE_P(item_zv) != IS_OBJECT) {
						YII_PTR_DTOR(item_zv);
					}
			        // 将数组中的内部指针向前移动一位
			        zend_hash_move_forward(Z_ARRVAL_P(data));
			    }
			}
			YII_PTR_DTOR(data);
		}
	}
	
	if (Z_TYPE_P(data_zv) == IS_ARRAY) {
		int count, i;
		zval **z_item;
		// 获取数组大小
	    count = zend_hash_num_elements(Z_ARRVAL_P(data_zv));
	    // 将数组的内部指针指向第一个单元
	    zend_hash_internal_pointer_reset(Z_ARRVAL_P(data_zv));
	    for (i = 0; i < count; i ++) {
			char *key; int idx;
			zval *key_zv, *idx_zv, *item_zv;
	        // 获取当前数据
	        zend_hash_get_current_data(Z_ARRVAL_P(data_zv), (void**) &z_item);
	
			ALLOC_INIT_ZVAL(item_zv);
			ZVAL_ZVAL(item_zv, *z_item, 1, 0);

			if (zend_hash_get_current_key(Z_ARRVAL_P(data_zv), &key, (unsigned long *)&idx, 0) == HASH_KEY_IS_STRING) {
				YII_NEW_STRING(key_zv, key);
				if (yii_call_class_method_2_no(getThis(), "add", key_zv, item_zv) != SUCCESS) {
					return;
				}
				YII_PTR_DTOR(key_zv);
				
			}
			else {
				YII_NEW_LONG(idx_zv, idx);
				if (yii_call_class_method_2_no(getThis(), "add", idx_zv, item_zv) != SUCCESS) {
					php_printf("error\n");
					return;
				}
				YII_PTR_DTOR(idx_zv);
			}
			
			if (Z_TYPE_P(item_zv) != IS_ARRAY && Z_TYPE_P(item_zv) != IS_OBJECT) {
				YII_PTR_DTOR(item_zv);
			}
			
	        // 将数组中的内部指针向前移动一位
	        zend_hash_move_forward(Z_ARRVAL_P(data_zv));
	    }
		
	}
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
	
}
/* }}} */

/** {{{ public CMap::mergeWith()
*/
PHP_METHOD(CMap, mergeWith){
	zval *data_zv, *d_zv;
	int recursive=1;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|b", &data_zv, &recursive) == FAILURE) {
        return;
    }

	if ( Z_TYPE_P(data_zv) != IS_ARRAY && Z_TYPE_P(data_zv) != IS_OBJECT && Z_TYPE_P(data_zv)!=IS_NULL) {
		php_printf("yii','Map data must be an array or an object implementing Traversable.'\n");
		return;
	}
	
	if (Z_TYPE_P(data_zv) == IS_OBJECT && Z_OBJ_HT_P(data_zv)->get_class_entry && instanceof_function(Z_OBJCE_P(data_zv), zend_ce_traversable TSRMLS_CC)) {
		php_printf("this object zend_ce_traversable\n");
		d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);

		if (Z_OBJ_HT_P(data_zv)->get_class_entry && instanceof_function(Z_OBJCE_P(data_zv), YII_CLASS_ENTRY(cmap) TSRMLS_CC)) {
			//zend_ce_arrayaccess foreach
			zval *data;
			yii_call_class_method_0(data_zv, "toArray", &data);
			if (Z_TYPE_P(data) == IS_ARRAY) {
				if (recursive == 1) {
					zval *retval;
					if (yii_call_class_static_method_2(getThis(), "self", "mergeArray", &retval, d_zv, data)==SUCCESS) {
						zend_update_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), retval TSRMLS_CC);
					}
				}
				else {
					int count, i;
					zval **z_item;
					// 获取数组大小
					count = zend_hash_num_elements(Z_ARRVAL_P(data));
					// 将数组的内部指针指向第一个单元
					zend_hash_internal_pointer_reset(Z_ARRVAL_P(data));
					for (i = 0; i < count; i ++) {
						char *key; int idx;
						zval *key_zv, *idx_zv, *item_zv; 
						// 获取当前数据
						zend_hash_get_current_data(Z_ARRVAL_P(data), (void**) &z_item);
						MAKE_STD_ZVAL(item_zv);
						ZVAL_ZVAL(item_zv, *z_item, 1, 0);
						if (zend_hash_get_current_key(Z_ARRVAL_P(data), &key, (unsigned long *)&idx, 0) == HASH_KEY_IS_STRING) {
							YII_NEW_STRING(key_zv, key);
							if (yii_call_class_method_2_no(getThis(), "add", key_zv, item_zv) != SUCCESS) {
								return;
							}
							YII_PTR_DTOR(key_zv);
						}
						else {
							YII_NEW_LONG(idx_zv, idx);
							if (yii_call_class_method_2_no(getThis(), "add", idx_zv, item_zv) != SUCCESS) {
								return;
							}
							YII_PTR_DTOR(idx_zv);
						}

			        	// 将数组中的内部指针向前移动一位
			        	zend_hash_move_forward(Z_ARRVAL_P(data));
			    	}
				}
			}
			YII_PTR_DTOR(data);
		}
	}
	
	if (Z_TYPE_P(data_zv) == IS_ARRAY) {
		int count, i;
		zval **z_item;
		// 获取数组大小
	    count = zend_hash_num_elements(Z_ARRVAL_P(data_zv));
	    // 将数组的内部指针指向第一个单元
	    zend_hash_internal_pointer_reset(Z_ARRVAL_P(data_zv));
	    for (i = 0; i < count; i ++) {
			char *key; int idx;
			zval *key_zv, *idx_zv, *item_zv;
	        // 获取当前数据
	        zend_hash_get_current_data(Z_ARRVAL_P(data_zv), (void**) &z_item);
			MAKE_STD_ZVAL(item_zv);
			ZVAL_ZVAL(item_zv, *z_item, 1, 0);
			if (zend_hash_get_current_key(Z_ARRVAL_P(data_zv), &key, (unsigned long *)&idx, 0) == HASH_KEY_IS_STRING) {
				YII_NEW_STRING(key_zv, key);
				if (yii_call_class_method_2_no(getThis(), "add", key_zv, item_zv) != SUCCESS) {
					return;
				}
				YII_PTR_DTOR(key_zv);
			}
			else {
				YII_NEW_LONG(idx_zv, idx);
				if (yii_call_class_method_2_no(getThis(), "add", idx_zv, item_zv) != SUCCESS) {
					return;
				}
				YII_PTR_DTOR(idx_zv);
			}
	        // 将数组中的内部指针向前移动一位
	        zend_hash_move_forward(Z_ARRVAL_P(data_zv));
	    }
	}
	
}
/* }}} */

/** {{{ static public CMap::mergeArray()
*/
PHP_METHOD(CMap, mergeArray){
    zval ***args;
    int argc;
	zval *res;
    int i;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "*", &args, &argc) == FAILURE) {
        return;
    }

	YII_NEW_ARRAY(res);
    
	for (i = 0; i < argc; i++) {
		if (Z_TYPE_P(*args[i]) == IS_ARRAY) {
			int count, k;
			zval **z_item;
			count = zend_hash_num_elements(Z_ARRVAL_P(*args[i]));
			zend_hash_internal_pointer_reset(Z_ARRVAL_P(*args[i]));
			
			for (k = 0; k < count; k ++) {
				char *key; int idx;
		        zend_hash_get_current_data(Z_ARRVAL_P(*args[i]), (void**) &z_item);
				if (zend_hash_get_current_key(Z_ARRVAL_P(*args[i]), &key, (unsigned long *)&idx, 0) != HASH_KEY_IS_STRING) {
					// KEY为数字
					if (zend_hash_index_exists(Z_ARRVAL_P(res), idx)) {
						YII_ADD_NEXT_ARRAY(res, *z_item)
					}
					else {
						YII_ADD_ARRAY(res, idx, *z_item);
					}
				}
				else {
					// KEY为字符串
					if (Z_TYPE_P(*z_item) == IS_ARRAY) {
						
						zval **retval;
						if (zend_hash_find(Z_ARRVAL_P(res), key, strlen(key)+1, (void **)&retval) == SUCCESS) {
							if (Z_TYPE_P(*retval) == IS_ARRAY) {
								zval *merge_retval;
								if (yii_call_class_static_method_2(NULL, "self", "mergeArray", &merge_retval , *retval, *z_item)==SUCCESS) {
									YII_ADD_ARRAY_EX(res, key, merge_retval);
								}
								else {
									YII_ADD_ARRAY_EX(res, key, *z_item);
								}
							} 
							else {
								YII_ADD_ARRAY_EX(res, key, *z_item);
							}
						}
						else {
							YII_ADD_ARRAY_EX(res, key, *z_item);
						}
					}
					else {
						YII_ADD_ARRAY_EX(res, key, *z_item);
					}
					
				}
				zend_hash_move_forward(Z_ARRVAL_P(*args[i]));
			}
		} 
    }  

    efree(args);
	RETVAL_ZVAL(res, 1, 0);
	return;

}
/* }}} */

/** {{{ public CMap::offsetExists()
*/
PHP_METHOD(CMap, offsetExists){
	zval *key_zv, *retval;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &key_zv) == FAILURE) {
		return;
	}

	if (yii_call_class_method_1(getThis(), "contains", &retval, key_zv) != SUCCESS) {
		return;
	}
	
	RETVAL_ZVAL(retval, 1, 0);
	YII_PTR_DTOR(retval);
	return;
}
/* }}} */

/** {{{ public CMap::offsetGet()
*/
PHP_METHOD(CMap, offsetGet){
	zval *key_zv, *retval;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &key_zv) == FAILURE) {
		return;
	}

	if (yii_call_class_method_1(getThis(), "itemAt", &retval, key_zv) != SUCCESS) {
		return;
	}
	
	RETVAL_ZVAL(retval, 1, 0);
	YII_PTR_DTOR(retval);
	return;
}
/* }}} */

/** {{{ public CMap::offsetSet()
*/
PHP_METHOD(CMap, offsetSet){
	zval *key_zv, *item_zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &key_zv, &item_zv) == FAILURE) {
		return;
	}

	if (yii_call_class_method_2_no(getThis(), "add", key_zv, item_zv) != SUCCESS) {
		return;
	}

	return;
}
/* }}} */

/** {{{ public CMap::offsetUnset()
*/
PHP_METHOD(CMap, offsetUnset){
	zval *key_zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &key_zv) == FAILURE) {
		return;
	}

	if (yii_call_class_method_1_no(getThis(), "remove", key_zv) != SUCCESS) {
		return;
	}

	return;
}
/* }}} */

/** {{{ YII_CLASS_METHODS
*/
YII_CLASS_METHODS(cmap) {
	PHP_ME(CMap, __construct, arginfo_cmap___construct, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, getReadOnly, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, setReadOnly, arginfo_cmap_setReadOnly, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, getIterator, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, count, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, getCount, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, getKeys, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, itemAt, arginfo_cmap_itemAt, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, add, arginfo_cmap_add, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, remove, arginfo_cmap_remove, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, clear, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, contains, arginfo_cmap_contains, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, toArray, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, copyFrom, arginfo_cmap_copyFrom, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, mergeWith, arginfo_cmap_mergeWith, ZEND_ACC_PUBLIC)
	//static
	PHP_ME(CMap, mergeArray, arginfo_cmap_mergeArray, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(CMap, offsetExists, arginfo_cmap_offsetExists, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, offsetGet, arginfo_cmap_offsetGet, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, offsetSet, arginfo_cmap_offsetSet, ZEND_ACC_PUBLIC)
	PHP_ME(CMap, offsetUnset, arginfo_cmap_offsetUnset, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/** {{{ Class CMap
*/
YII_CLASS_FUNCTION(cmap) {
	//AUTO CALL CLASS METHOD
	YII_CLASS_DECLARE_EX(CMap, cmap, YII_CLASS_ENTRY(ccomponent), "CComponent", 0);
	zend_declare_property_null(YII_CLASS_ENTRY(cmap), YII_SL("_d"), ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_bool(YII_CLASS_ENTRY(cmap), YII_SL("_r"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(YII_CLASS_ENTRY(cmap) TSRMLS_CC, 3, zend_ce_aggregate, zend_ce_arrayaccess, spl_ce_Countable);
	return SUCCESS;
}
/* }}} */
