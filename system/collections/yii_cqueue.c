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
#include "system/collections/yii_cqueue.h"
#include "system/collections/yii_cqueueiterator.h"

YII_CLASS_DECLARE_ENTRY(cqueue);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_cqueue___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cqueue_copyFrom, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cqueue_contains, 0, 0, 1)
	ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cqueue_enqueue, 0, 0, 1)
	ZEND_ARG_INFO(0, item)
ZEND_END_ARG_INFO()
/* }}} */

/** {{{ public CQueue::__construct()
*/
PHP_METHOD(CQueue, __construct){
	zval *data_zv=NULL, *d_zv;
	int init_flag = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &data_zv) == FAILURE) {
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
		init_flag = 1;
		YII_NEW_NULL(data_zv);
	}

	if (Z_TYPE_P(data_zv) != IS_NULL) {
		if (yii_call_class_method_1_no(getThis(), "copyFrom", data_zv) != SUCCESS) {
			return;
		}
	}
	
	if (init_flag==1) {
		YII_PTR_DTOR(data_zv);
	}

}
/* }}} */

/** {{{ public CQueue::toArray()
*/
PHP_METHOD(CQueue, toArray){
	zval *d_zv;
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
	RETVAL_ZVAL(d_zv, 1, 0);
	return;
}
/* }}} */

/** {{{ public CQueue::copyFrom()
*/
PHP_METHOD(CQueue, copyFrom){
	zval *data_zv, *d_zv, *c_zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &data_zv) == FAILURE) {
		return;
	}

	if ( Z_TYPE_P(data_zv) != IS_ARRAY && Z_TYPE_P(data_zv) != IS_OBJECT && Z_TYPE_P(data_zv)!=IS_NULL) {
		php_printf("yii','Queue data must be an array or an object implementing Traversable.'\n");
		return;
	}
	else if (Z_TYPE_P(data_zv) == IS_OBJECT && Z_OBJ_HT_P(data_zv)->get_class_entry && !instanceof_function(Z_OBJCE_P(data_zv), zend_ce_traversable TSRMLS_CC)) {
		php_printf("yii','Queue data must be an array or an object implementing Traversable.'\n");
		return;	
	}
	
	if (yii_call_class_method_0_no(getThis(), "clear") != SUCCESS) {
		return;
	}
	
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
	c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
	
	
	if (Z_TYPE_P(data_zv) == IS_OBJECT && Z_OBJ_HT_P(data_zv)->get_class_entry && instanceof_function(Z_OBJCE_P(data_zv), zend_ce_traversable TSRMLS_CC)) {
		zval *data;
		yii_call_class_method_0(data_zv, "toArray", &data);
		if (Z_TYPE_P(data) == IS_ARRAY) {
			int count, i;
			zval **z_item, *item_zv;
			// 获取数组大小
		    count = zend_hash_num_elements(Z_ARRVAL_P(data));
		    // 将数组的内部指针指向第一个单元
		    zend_hash_internal_pointer_reset(Z_ARRVAL_P(data));
		    for (i = 0; i < count; i ++) {
		        // 获取当前数据
		        zend_hash_get_current_data(Z_ARRVAL_P(data), (void**) &z_item);
				ALLOC_INIT_ZVAL(item_zv);
				ZVAL_ZVAL(item_zv, *z_item, 1, 0);
				
				YII_ADD_NEXT_ARRAY(d_zv, item_zv);
				Z_LVAL_P(c_zv)++;
				
				if (Z_TYPE_P(item_zv) != IS_ARRAY && Z_TYPE_P(item_zv) != IS_OBJECT) {
					YII_PTR_DTOR(item_zv);
				}
				
		        // 将数组中的内部指针向前移动一位
		        zend_hash_move_forward(Z_ARRVAL_P(data));
		    }
		}
		YII_PTR_DTOR(data);
	}


	if (Z_TYPE_P(data_zv) == IS_ARRAY) {
		int count, i;
		zval **z_item, *item_zv;
		// 获取数组大小
	    count = zend_hash_num_elements(Z_ARRVAL_P(data_zv));
	    // 将数组的内部指针指向第一个单元
	    zend_hash_internal_pointer_reset(Z_ARRVAL_P(data_zv));
	    for (i = 0; i < count; i ++) {
	        // 获取当前数据
	        zend_hash_get_current_data(Z_ARRVAL_P(data_zv), (void**) &z_item);
	
			ALLOC_INIT_ZVAL(item_zv);
			ZVAL_ZVAL(item_zv, *z_item, 1, 0);

			YII_ADD_NEXT_ARRAY(d_zv, item_zv);
			Z_LVAL_P(c_zv)++;
			
			if (Z_TYPE_P(item_zv) != IS_ARRAY && Z_TYPE_P(item_zv) != IS_OBJECT) {
				YII_PTR_DTOR(item_zv);
			}
	        // 将数组中的内部指针向前移动一位
	        zend_hash_move_forward(Z_ARRVAL_P(data_zv));
	    }
	}

	//zend_update_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), d_zv TSRMLS_CC);
	zend_update_property_long(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), Z_LVAL_P(c_zv) TSRMLS_CC);
}
/* }}} */

/** {{{ public CQueue::clear()
*/
PHP_METHOD(CQueue, clear){
	zval *d_zv, *c_zv;
	YII_NEW_ARRAY(d_zv);
	zend_update_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), d_zv TSRMLS_CC);
	zend_update_property_long(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
	YII_PTR_DTOR(d_zv);
}
/* }}} */

/** {{{ public CQueue::contains()
*/
PHP_METHOD(CQueue, contains){
	zval *index_zv, *item_zv, *strict_zv, *d_zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &item_zv) == FAILURE) {
		return;
	}
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);

	YII_NEW_BOOL(strict_zv, 1);
	if (yii_call_user_fun_3("array_search", &index_zv, item_zv, d_zv, strict_zv) == SUCCESS) {
		if (Z_TYPE_P(index_zv) != IS_BOOL) {
			RETVAL_TRUE;
			YII_PTR_DTOR(strict_zv);
			YII_PTR_DTOR(index_zv);
			return;
		}
	}
	YII_PTR_DTOR(strict_zv);
	YII_PTR_DTOR(index_zv);
	RETVAL_FALSE;
	return;
}
/* }}} */

/** {{{ public CQueue::peek()
*/
PHP_METHOD(CQueue, peek){
	zval *c_zv, *d_zv, **find_zv;
	c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
	
	if (Z_LVAL_P(c_zv) == 0) {
		php_printf("'The queue is empty.'\n");
	}
	else {
		d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
		if (zend_hash_index_find(Z_ARRVAL_P(d_zv), 0, (void **)&find_zv) == SUCCESS) {
			RETVAL_ZVAL(*find_zv, 1, 0);
			return;
		}
	}
	return;
}
/* }}} */

/** {{{ public CQueue::dequeue()
*/
PHP_METHOD(CQueue, dequeue){
	zval *c_zv, *d_zv, *item_zv;
	c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
	
	if (Z_LVAL_P(c_zv) == 0) {
		php_printf("'The queue is empty.'\n");
	}
	else {
		zend_update_property_long(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), Z_LVAL_P(c_zv)-1 TSRMLS_CC);
		d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
		if (yii_call_user_fun_1("array_shift", &item_zv, d_zv) == SUCCESS) {
			RETVAL_ZVAL(item_zv, 1, 0);
			return;
		}
	}
	return;
}
/* }}} */

/** {{{ public CQueue::enqueue()
*/
PHP_METHOD(CQueue, enqueue){
	zval *c_zv, *d_zv, *item_zv;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &item_zv) == FAILURE) {
		return;
	}
	
	c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
	zend_update_property_long(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), Z_LVAL_P(c_zv)+1 TSRMLS_CC);
	
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
	YII_ADD_NEXT_ARRAY(d_zv, item_zv);
	return;
}
/* }}} */

/** {{{ public CQueue::getIterator()
*/
PHP_METHOD(CQueue, getIterator){
	zval *retval, *d_zv;
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);
	if (yii_new_class_instance_1(&retval, "CQueueIterator", d_zv) == SUCCESS) {
		RETVAL_ZVAL(retval, 1, 0);
		YII_PTR_DTOR(retval);
		return;
	}
	YII_PTR_DTOR(retval);
	return;
}
/* }}} */

/** {{{ public CQueue::getCount()
*/
PHP_METHOD(CQueue, getCount){
	zval *c_zv;
	c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
	RETVAL_ZVAL(c_zv, 1, 0);
	return;
}
/* }}} */

/** {{{ public CQueue::count()
*/
PHP_METHOD(CQueue, count){
	zval *retval;
	yii_call_class_method_0(getThis(), "getCount", &retval);
	RETVAL_LONG(Z_LVAL_P(retval));
	YII_PTR_DTOR(retval);
	return;
}
/* }}} */

/** {{{ YII_CLASS_METHODS
*/
YII_CLASS_METHODS(cqueue) {
	PHP_ME(CQueue, __construct, arginfo_cqueue___construct, ZEND_ACC_PUBLIC)
	PHP_ME(CQueue, toArray, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CQueue, copyFrom, arginfo_cqueue_copyFrom, ZEND_ACC_PUBLIC)
	PHP_ME(CQueue, clear, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CQueue, contains, arginfo_cqueue_contains, ZEND_ACC_PUBLIC)
	PHP_ME(CQueue, peek, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CQueue, dequeue, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CQueue, enqueue, arginfo_cqueue_enqueue, ZEND_ACC_PUBLIC)
	PHP_ME(CQueue, getIterator, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CQueue, getCount, NULL, ZEND_ACC_PUBLIC)	
	PHP_ME(CQueue, count, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/** {{{ Class CList
*/
YII_CLASS_FUNCTION(cqueue) {
	//AUTO CALL CLASS METHOD
	YII_CLASS_DECLARE_EX(CQueue, cqueue, YII_CLASS_ENTRY(ccomponent), "CComponent", 0);

	zend_declare_property_null(YII_CLASS_ENTRY(cqueue), YII_SL("_d"), ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_long(YII_CLASS_ENTRY(cqueue), YII_SL("_c"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(YII_CLASS_ENTRY(cqueue) TSRMLS_CC, 2, zend_ce_aggregate, spl_ce_Countable);
	return SUCCESS;
}
/* }}} */
