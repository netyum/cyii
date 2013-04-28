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
#include "system/collections/yii_cqueueiterator.h"

YII_CLASS_DECLARE_ENTRY(cqueueiterator);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_cqueueiterator___construct, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(1, data, 0)
ZEND_END_ARG_INFO()
/* }}} */


/** {{{ public CQueueIterator::__construct()
*/
PHP_METHOD(CQueueIterator, __construct){
	zval *data_zv, *d_zv;
	int count;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &data_zv) == FAILURE) {
		return;
	}
	count = zend_hash_num_elements(Z_ARRVAL_P(data_zv));
	
	zend_update_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), data_zv TSRMLS_CC);
	zend_update_property_long(Z_OBJCE_P(getThis()), getThis(), YII_SL("_i"), 0 TSRMLS_CC);
	zend_update_property_long(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), count TSRMLS_CC);
}
/* }}} */

/** {{{ public CQueueIterator::rewind()
*/
PHP_METHOD(CQueueIterator, rewind){
	zend_update_property_long(Z_OBJCE_P(getThis()), getThis(), YII_SL("_i"), 0 TSRMLS_CC);
}
/* }}} */

/** {{{ public CQueueIterator::key()
*/
PHP_METHOD(CQueueIterator, key){
	zval *i_zv;
	i_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_i"), 0 TSRMLS_CC);
	RETURN_ZVAL(i_zv, 1, 0);
}
/* }}} */

/** {{{ public CQueueIterator::current()
*/
PHP_METHOD(CQueueIterator, current){
	zval *i_zv, *d_zv, **retval;
	i_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_i"), 0 TSRMLS_CC);
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);

	if (zend_hash_index_find(Z_ARRVAL_P(d_zv), Z_LVAL_P(i_zv), (void **)&retval) == SUCCESS) {
		RETVAL_ZVAL(*retval, 1, 0);
		return;
	}
}
/* }}} */

/** {{{ public CQueueIterator::next()
*/
PHP_METHOD(CQueueIterator, next){
	zval *i_zv;
	i_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_i"), 0 TSRMLS_CC);
	Z_LVAL_P(i_zv) = Z_LVAL_P(i_zv)+1;
}
/* }}} */

/** {{{ public CQueueIterator::valid()
*/
PHP_METHOD(CQueueIterator, valid){
	zval *i_zv, *c_zv;
	i_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_i"), 0 TSRMLS_CC);
	c_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_c"), 0 TSRMLS_CC);
	if (Z_LVAL_P(i_zv)<Z_LVAL_P(c_zv)) {
		RETURN_TRUE;
	}
	else {
		RETURN_FALSE;
	}
}
/* }}} */

/** {{{ YII_CLASS_METHODS
*/
YII_CLASS_METHODS(cqueueiterator) {
	PHP_ME(CQueueIterator, __construct, arginfo_cqueueiterator___construct, ZEND_ACC_PUBLIC)
	PHP_ME(CQueueIterator, rewind, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CQueueIterator, key, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CQueueIterator, current, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CQueueIterator, next, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CQueueIterator, valid, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/** {{{ Class CQueueIterator
*/
YII_CLASS_FUNCTION(cqueueiterator) {
	//AUTO CALL CLASS METHOD
	YII_CLASS_DECLARE(CQueueIterator, cqueueiterator, 0);
	zend_declare_property_null(YII_CLASS_ENTRY(cqueueiterator), YII_SL("_d"), ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_long(YII_CLASS_ENTRY(cqueueiterator), YII_SL("_c"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_long(YII_CLASS_ENTRY(cqueueiterator), YII_SL("_i"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(YII_CLASS_ENTRY(cqueueiterator) TSRMLS_CC, 1, zend_ce_iterator);
	return SUCCESS;
}
/* }}} */
