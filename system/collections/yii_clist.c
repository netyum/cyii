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
#include "system/collections/yii_clist.h"
#include "system/collections/yii_clistiterator.h"

YII_CLASS_DECLARE_ENTRY(clist);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_clist___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, readOnly)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_clist_setReadOnly, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_clist_itemAt, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_clist_add, 0, 0, 1)
	ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_clist_insertAt, 0, 0, 2)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_clist_remove, 0, 0, 1)
	ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_clist_removeAt, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_clist_contains, 0, 0, 1)
	ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_clist_indexOf, 0, 0, 1)
	ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_clist_copyFrom, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_clist_mergeWith, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_clist_offsetExists, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_clist_offsetGet, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_clist_offsetSet, 0, 0, 2)
	ZEND_ARG_INFO(0, offset)
	ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_clist_offsetUnset, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

/* }}} */


/** {{{ public CList::__construct()
*/
PHP_METHOD(CList, __construct){
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


	YII_NEW_BOOL(readOnly_zv, readOnly);
	if (!data_zv) {
		YII_NEW_NULL(data_zv);
	}

	if (Z_TYPE_P(data_zv) != IS_NULL) {
		if (yii_call_class_method_1_no(getThis(), "copyFrom", data_zv) != SUCCESS) {
			return;
		}
	}
	
	YII_PTR_DTOR(data_zv);
	YII_PTR_DTOR(readOnly_zv);
	
}
/* }}} */

/** {{{ public CList::getReadOnly()
*/
PHP_METHOD(CList, getReadOnly){
	zval *r_zv;
	r_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_r"), 0 TSRMLS_CC);
	RETURN_ZVAL(r_zv, 1, 0);
}
/* }}} */

/** {{{ public CList::setReadOnly()
*/
PHP_METHOD(CList, setReadOnly){
	int value;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &value) == FAILURE) {
		return;
	}
	
	zend_update_property_bool(Z_OBJCE_P(getThis()), getThis(), YII_SL("_r"), value TSRMLS_CC);

}
/* }}} */

/** {{{ public CList::getIterator()
*/
PHP_METHOD(CList, getIterator){
	zval *retval, *d_zv;
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
	if (yii_new_class_instance_1(&retval, "CListIterator", d_zv) == SUCCESS) {
		RETVAL_ZVAL(retval, 1, 0);
		YII_PTR_DTOR(retval);
		return;
	}
	YII_PTR_DTOR(retval);
	return;
}
/* }}} */

/** {{{ public CList::count()
*/
PHP_METHOD(CList, count){
	zval *retval;
	yii_call_class_method_0(getThis(), "getCount", &retval);
	RETVAL_LONG(Z_LVAL_P(retval));
	YII_PTR_DTOR(retval);
	return;
}
/* }}} */

/** {{{ public CList::getCount()
*/
PHP_METHOD(CList, getCount){
	zval *c_zv;
	c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
	RETVAL_LONG(Z_LVAL_P(c_zv));
	return;
}
/* }}} */

/** {{{ public CList::itemAt()
*/
PHP_METHOD(CList, itemAt){
	int index;
	zval **find_zv, *c_zv, *d_zv;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index) == FAILURE) {
		return;
	}
	
	c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);

	/* if(isset($this->_d[$index])) */
	if (zend_hash_index_find(Z_ARRVAL_P(d_zv), index, (void **)&find_zv) == SUCCESS) {
		RETVAL_ZVAL(*find_zv, 1, 0);
		return;
	}
	else if(index>=0 && index<Z_LVAL_P(c_zv)) { // in case the value is null
		RETURN_NULL();
	}
	else {
		php_printf("'List index %d is out of bound. in itemAt.'\n", index);
	}
}
/* }}} */

/** {{{ public CList::add()
*/
PHP_METHOD(CList, add){
	zval *item_zv, *c_zv;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &item_zv) == FAILURE) {
		return;
	}
	c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
	if (yii_call_class_method_2_no(getThis(), "insertAt", c_zv, item_zv) != SUCCESS) {
		return;
	}
	
	RETURN_LONG(Z_LVAL_P(c_zv)-1);
}
/* }}} */

/** {{{ public CList::insertAt()
*/
PHP_METHOD(CList, insertAt){
	zval *index_zv, *item_zv;
	zval *r_zv, *c_zv, *d_zv, *tmp_zv;
	int index;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &index, &item_zv) == FAILURE) {
		return;
	}
	
	r_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_r"), 0 TSRMLS_CC);
	
	if (Z_BVAL_P(r_zv) == 0) {
		d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
		c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
		if (index == Z_LVAL_P(c_zv)) {
			YII_ADD_ARRAY(d_zv, index, item_zv);
			zend_update_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), d_zv TSRMLS_CC);

			YII_NEW_LONG(index_zv, index+1);
			zend_update_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), index_zv TSRMLS_CC);
			YII_PTR_DTOR(index_zv);
		}
		else if (index>=0 && index<Z_LVAL_P(c_zv)) {
			zval *length_zv, *replacement_zv;
			YII_NEW_LONG(index_zv, index);
			YII_NEW_LONG(length_zv, 0);
			YII_NEW_ARRAY(replacement_zv);
			YII_ADD_ARRAY(replacement_zv, 0, item_zv);
			
			/* array_splice($this->_d,$index,0,array($item)); */
			yii_call_user_fun_4_no("array_splice", d_zv, index_zv, length_zv, replacement_zv);
			
			YII_PTR_DTOR(index_zv);
			YII_PTR_DTOR(length_zv);
			YII_PTR_DTOR(replacement_zv);
			
			YII_NEW_LONG(index_zv, Z_LVAL_P(c_zv)+1);
			zend_update_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), index_zv TSRMLS_CC);
			YII_PTR_DTOR(index_zv);
		}
		else {
			php_printf("'List index %d is out of bound. in insertAt.'\n", index);
		}
	}
	else {
		php_printf("'The list is read only.'\n");
	}
}
/* }}} */

/** {{{ public CList::remove()
*/
PHP_METHOD(CList, remove){
	zval *index_zv, *item_zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &item_zv) == FAILURE) {
		return;
	}
	
	if (yii_call_class_method_1(getThis(), "indexOf", &index_zv, item_zv) == SUCCESS) {
		if ( Z_LVAL_P(index_zv)>=0 ) {
			yii_call_class_method_1_no(getThis(), "removeAt", index_zv);
			RETVAL_ZVAL(index_zv, 1, 0);
			YII_PTR_DTOR(index_zv);
			return;
		}
		YII_PTR_DTOR(index_zv);
	}
	
	RETURN_FALSE;
	
}
/* }}} */

/** {{{ public CList::removeAt()
*/
PHP_METHOD(CList, removeAt){
	zval *index_zv, *item_zv;
	zval *r_zv, *c_zv, *d_zv, *tmp_zv;
	int index;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index) == FAILURE) {
		return;
	}

	r_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_r"), 0 TSRMLS_CC);
	/* if(!$this->_r) */
	if (Z_BVAL_P(r_zv) != 1) {
		d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
		c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
		if (index>=0 && index<Z_LVAL_P(c_zv)) {
			YII_NEW_LONG(index_zv, Z_LVAL_P(c_zv)-1);
			zend_update_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), index_zv TSRMLS_CC);
			
			if (index == Z_LVAL_P(index_zv)) {
				zval *retval;
				if (yii_call_user_fun_1("array_pop", &retval, d_zv) == SUCCESS) {
					RETVAL_ZVAL(retval, 1, 0);
					YII_PTR_DTOR(retval);
					YII_PTR_DTOR(index_zv);
					return;
				}
			}
			else {
				zval **item_zv, *length_zv;
				YII_PTR_DTOR(index_zv);
				if (zend_hash_index_find(Z_ARRVAL_P(d_zv), index, (void **)&item_zv) == SUCCESS) {
					RETVAL_ZVAL(*item_zv, 1, 0);
					
					YII_NEW_LONG(index_zv, index);
					YII_NEW_LONG(length_zv, 1);
					/* array_splice($this->_d,$index,1); */
					yii_call_user_fun_3_no("array_splice", d_zv, index_zv, length_zv);
					
					YII_PTR_DTOR(index_zv);
					YII_PTR_DTOR(length_zv);
					return;
				}
			}
		}
		else {
			YII_PTR_DTOR(index_zv);
			php_printf("'List index %d is out of bound.\n", index);
		}
	}
	else {
		php_printf("The list is read only.\n");
	}

}
/* }}} */

/** {{{ public CList::clear()
*/
PHP_METHOD(CList, clear){
	zval *c_zv, *i_zv; int i;
	c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);

	i = Z_LVAL_P(c_zv)-1;
	for(;i>=0; --i) {
		YII_NEW_LONG(i_zv, i);
		yii_call_class_method_1_no(getThis(), "removeAt", i_zv);
		YII_PTR_DTOR(i_zv);
	}
	return;
}
/* }}} */

/** {{{ public CList::contains()
*/
PHP_METHOD(CList, contains){
	zval *item_zv, *retval;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &item_zv) == FAILURE) {
		return;
	}
	
	if (yii_call_class_method_1(getThis(), "indexOf", &retval, item_zv) != SUCCESS) {
		return;
	}

	if (Z_LVAL_P(retval)>=0) RETVAL_TRUE;
	else RETVAL_FALSE;
	
	YII_PTR_DTOR(retval);
	return;
}
/* }}} */

/** {{{ public CList::indexOf()
*/
PHP_METHOD(CList, indexOf){
	zval *index_zv, *item_zv, *strict_zv, *d_zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &item_zv) == FAILURE) {
		return;
	}
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
	YII_NEW_BOOL(strict_zv, 1);
	if (yii_call_user_fun_3("array_search", &index_zv, item_zv, d_zv, strict_zv) == SUCCESS) {
		if (Z_TYPE_P(index_zv) != IS_BOOL) {
			RETVAL_ZVAL(index_zv, 1, 0);
			YII_PTR_DTOR(strict_zv);
			YII_PTR_DTOR(index_zv);
			return;
		}
	}
	YII_PTR_DTOR(strict_zv);
	YII_PTR_DTOR(index_zv);
	RETVAL_LONG(FAILURE);
	return;
}
/* }}} */

/** {{{ public CList::toArray()
*/
PHP_METHOD(CList, toArray){
	zval *d_zv;
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
	RETVAL_ZVAL(d_zv, 1, 0);
}
/* }}} */

/** {{{ public CList::copyFrom()
*/
PHP_METHOD(CList, copyFrom){
	zval *data_zv, *c_zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &data_zv) == FAILURE) {
		return;
	}

	if ( Z_TYPE_P(data_zv) != IS_ARRAY && Z_TYPE_P(data_zv) != IS_OBJECT && Z_TYPE_P(data_zv)!=IS_NULL) {
		php_printf("yii','List data must be an array or an object implementing Traversable.'\n");
		return;
	}
	else if (Z_TYPE_P(data_zv) == IS_OBJECT && Z_OBJ_HT_P(data_zv)->get_class_entry && !instanceof_function(Z_OBJCE_P(data_zv), zend_ce_traversable TSRMLS_CC)) {
		php_printf("yii','List data must be an array or an object implementing Traversable.'\n");
		return;
	}
	
	if (Z_TYPE_P(data_zv) == IS_OBJECT && Z_OBJ_HT_P(data_zv)->get_class_entry && instanceof_function(Z_OBJCE_P(data_zv), zend_ce_traversable TSRMLS_CC)) {
		c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
		if ( Z_LVAL_P(c_zv) > 0 ) {
			/* $this->clear(); */
			if (yii_call_class_method_0_no(getThis(), "clear") != SUCCESS) {
				return;
			}
		}
		if (Z_OBJ_HT_P(data_zv)->get_class_entry && instanceof_function(Z_OBJCE_P(data_zv), YII_CLASS_ENTRY(clist) TSRMLS_CC)) {
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
			        // 获取当前数据
			        zend_hash_get_current_data(Z_ARRVAL_P(data), (void**) &z_item);
					if (yii_call_class_method_1_no(getThis(), "add", *z_item) != SUCCESS) {
						return;
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
	        // 获取当前数据
	        zend_hash_get_current_data(Z_ARRVAL_P(data_zv), (void**) &z_item);
			if (yii_call_class_method_1_no(getThis(), "add", *z_item) != SUCCESS) {
				return;
			}
	        // 将数组中的内部指针向前移动一位
	        zend_hash_move_forward(Z_ARRVAL_P(data_zv));
	    }
	}

}
/* }}} */

/** {{{ public CList::mergeWith()
*/
PHP_METHOD(CList, mergeWith){
	zval *data_zv, *c_zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &data_zv) == FAILURE) {
		return;
	}

	if ( Z_TYPE_P(data_zv) != IS_ARRAY && Z_TYPE_P(data_zv) != IS_OBJECT ) {
		php_printf("yii','List data must be an array or an object implementing Traversable.'\n");
		return;
	}
	
	if (Z_TYPE_P(data_zv) == IS_OBJECT && Z_OBJ_HT_P(data_zv)->get_class_entry && instanceof_function(Z_OBJCE_P(data_zv), zend_ce_traversable TSRMLS_CC)) {
		c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);

		if (Z_OBJ_HT_P(data_zv)->get_class_entry && instanceof_function(Z_OBJCE_P(data_zv), YII_CLASS_ENTRY(clist) TSRMLS_CC)) {
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
			        // 获取当前数据
			        zend_hash_get_current_data(Z_ARRVAL_P(data), (void**) &z_item);
					if (yii_call_class_method_1_no(getThis(), "add", *z_item) != SUCCESS) {
						return;
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
	        // 获取当前数据
	        zend_hash_get_current_data(Z_ARRVAL_P(data_zv), (void**) &z_item);
			if (yii_call_class_method_1_no(getThis(), "add", *z_item) != SUCCESS) {
				return;
			}
	        // 将数组中的内部指针向前移动一位
	        zend_hash_move_forward(Z_ARRVAL_P(data_zv));
	    }
	}

	if (Z_TYPE_P(data_zv)!=IS_NULL) {
		php_printf("'List data must be an array or an object implementing Traversable in mergeWith\n");
	}
}
/* }}} */

/** {{{ public CList::offsetExists()
*/
PHP_METHOD(CList, offsetExists){
	zval *c_zv; int offset;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &offset) == FAILURE) {
		return;
	}
	c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
	if ( offset>=0 && offset<Z_LVAL_P(c_zv) ) {
		RETURN_TRUE;
	}
	else {
		RETURN_FALSE;
	}
}
/* }}} */

/** {{{ public CList::offsetGet()
*/
PHP_METHOD(CList, offsetGet){
	int offset; zval *offset_zv, *retval;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &offset) == FAILURE) {
		return;
	}
	YII_NEW_LONG(offset_zv, offset);
	if (yii_call_class_method_1(getThis(), "itemAt", &retval, offset_zv) != SUCCESS) {
		return;
	}
	RETVAL_ZVAL(retval, 1, 0);
	YII_PTR_DTOR(retval);
	YII_PTR_DTOR(offset_zv);
	return;
}
/* }}} */

/** {{{ public CList::offsetSet()
*/
PHP_METHOD(CList, offsetSet){
	zval *offset_zv, *item_zv, *c_zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &offset_zv, &item_zv) == FAILURE) {
		return;
	}
	c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
	if (Z_TYPE_P(offset_zv) == IS_NULL || (Z_TYPE_P(offset_zv) == IS_LONG && Z_LVAL_P(offset_zv) == Z_LVAL_P(c_zv))) {
		yii_call_class_method_2_no(getThis(), "insertAt", c_zv, item_zv);
	}
	else if ( Z_TYPE_P(offset_zv) == IS_LONG ) {
		yii_call_class_method_1_no(getThis(), "removeAt", offset_zv);
		yii_call_class_method_2_no(getThis(), "insertAt", offset_zv, item_zv);
	}
}
/* }}} */

/** {{{ public CList::offsetUnset()
*/
PHP_METHOD(CList, offsetUnset){
	int offset; zval *offset_zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &offset) == FAILURE) {
		return;
	}
	YII_NEW_LONG(offset_zv, offset);
	yii_call_class_method_1_no(getThis(), "removeAt", offset_zv);
	YII_PTR_DTOR(offset_zv);
}
/* }}} */


/** {{{ YII_CLASS_METHODS
*/
YII_CLASS_METHODS(clist) {
	PHP_ME(CList, __construct, arginfo_clist___construct, ZEND_ACC_PUBLIC)
	PHP_ME(CList, getReadOnly, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CList, setReadOnly, arginfo_clist_setReadOnly, ZEND_ACC_PUBLIC)
	PHP_ME(CList, getIterator, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CList, count, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CList, getCount, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CList, itemAt, arginfo_clist_itemAt, ZEND_ACC_PUBLIC)
	PHP_ME(CList, add, arginfo_clist_add, ZEND_ACC_PUBLIC)
	PHP_ME(CList, insertAt, arginfo_clist_insertAt, ZEND_ACC_PUBLIC)
	PHP_ME(CList, remove, arginfo_clist_remove, ZEND_ACC_PUBLIC)
	PHP_ME(CList, removeAt, arginfo_clist_removeAt, ZEND_ACC_PUBLIC)
	PHP_ME(CList, clear, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CList, contains, arginfo_clist_contains, ZEND_ACC_PUBLIC)
	PHP_ME(CList, indexOf, arginfo_clist_indexOf, ZEND_ACC_PUBLIC)
	PHP_ME(CList, toArray, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CList, copyFrom, arginfo_clist_copyFrom, ZEND_ACC_PUBLIC)
	PHP_ME(CList, mergeWith, arginfo_clist_mergeWith, ZEND_ACC_PUBLIC)
	PHP_ME(CList, offsetExists, arginfo_clist_offsetExists, ZEND_ACC_PUBLIC)
	PHP_ME(CList, offsetGet, arginfo_clist_offsetGet, ZEND_ACC_PUBLIC)
	PHP_ME(CList, offsetSet, arginfo_clist_offsetSet, ZEND_ACC_PUBLIC)
	PHP_ME(CList, offsetUnset, arginfo_clist_offsetUnset, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/** {{{ Class CList
*/
YII_CLASS_FUNCTION(clist) {
	//AUTO CALL CLASS METHOD
	YII_CLASS_DECLARE_EX(CList, clist, YII_CLASS_ENTRY(ccomponent), "CComponent", 0);
	
	zend_declare_property_null(YII_CLASS_ENTRY(clist), YII_SL("_d"), ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_long(YII_CLASS_ENTRY(clist), YII_SL("_c"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_bool(YII_CLASS_ENTRY(clist), YII_SL("_r"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(YII_CLASS_ENTRY(clist) TSRMLS_CC, 3, zend_ce_aggregate, zend_ce_arrayaccess, spl_ce_Countable);
	return SUCCESS;
}
/* }}} */
