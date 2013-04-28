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
#include "system/collections/yii_clistiterator.h"

YII_CLASS_DECLARE_ENTRY(clistiterator);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_clistiterator___construct, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(1, data, 0)
ZEND_END_ARG_INFO()
/* }}} */


/** {{{ public CListIterator::__construct()
*/
PHP_METHOD(CListIterator, __construct){
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

/** {{{ public CListIterator::rewind()
*/
PHP_METHOD(CListIterator, rewind){
	zend_update_property_long(Z_OBJCE_P(getThis()), getThis(), YII_SL("_i"), 0 TSRMLS_CC);
}
/* }}} */

/** {{{ public CListIterator::key()
*/
PHP_METHOD(CListIterator, key){
	zval *i_zv;
	i_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_i"), 0 TSRMLS_CC);
	RETURN_ZVAL(i_zv, 1, 0);
}
/* }}} */

/** {{{ public CListIterator::current()
*/
PHP_METHOD(CListIterator, current){
	zval *i_zv, *d_zv, **retval;
	i_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_i"), 0 TSRMLS_CC);
	d_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_d"), 0 TSRMLS_CC);

	if (zend_hash_index_find(Z_ARRVAL_P(d_zv), Z_LVAL_P(i_zv), (void **)&retval) == SUCCESS) {
		RETVAL_ZVAL(*retval, 1, 0);
		return;
	}
}
/* }}} */

/** {{{ public CListIterator::next()
*/
PHP_METHOD(CListIterator, next){
	zval *i_zv;
	i_zv = zend_read_property(Z_OBJCE_P(getThis()), getThis(), YII_SL("_i"), 0 TSRMLS_CC);
	Z_LVAL_P(i_zv) = Z_LVAL_P(i_zv)+1;
}
/* }}} */

/** {{{ public CListIterator::valid()
*/
PHP_METHOD(CListIterator, valid){
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
YII_CLASS_METHODS(clistiterator) {
	PHP_ME(CListIterator, __construct, arginfo_clistiterator___construct, ZEND_ACC_PUBLIC)
	PHP_ME(CListIterator, rewind, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CListIterator, key, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CListIterator, current, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CListIterator, next, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(CListIterator, valid, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/** {{{ Class CList
*/
YII_CLASS_FUNCTION(clistiterator) {
	//AUTO CALL CLASS METHOD
	YII_CLASS_DECLARE(CListIterator, clistiterator, 0);
	zend_declare_property_null(YII_CLASS_ENTRY(clistiterator), YII_SL("_d"), ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_long(YII_CLASS_ENTRY(clistiterator), YII_SL("_c"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_long(YII_CLASS_ENTRY(clistiterator), YII_SL("_i"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(YII_CLASS_ENTRY(clistiterator) TSRMLS_CC, 1, zend_ce_iterator);
	return SUCCESS;
}
/* }}} */
