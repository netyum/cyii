#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h" /* for zend_alter_ini_entry */
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */

#include "php_yii.h"

#include "system/base/interface/yii_iauthmanager.h"

YII_CLASS_DECLARE_ENTRY(iauthmanager);

/** {{{ ARG_INFO
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_checkAccess, 0, 0, 2)
	ZEND_ARG_INFO(0, itemName)
	ZEND_ARG_INFO(0, userId)
	ZEND_ARG_ARRAY_INFO(1, params, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_createAuthItem, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, type)
	ZEND_ARG_INFO(0, description)
	ZEND_ARG_INFO(0, bizRule)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_removeAuthItem, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_getAuthItems, 0, 0, 0)
	ZEND_ARG_INFO(0, type)
	ZEND_ARG_INFO(0, userId)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_getAuthItem, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_saveAuthItem, 0, 0, 1)
	ZEND_ARG_INFO(0, item)
	ZEND_ARG_INFO(0, oldName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_addItemChild, 0, 0, 2)
	ZEND_ARG_INFO(0, itemName)
	ZEND_ARG_INFO(0, childName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_removeItemChild, 0, 0, 2)
	ZEND_ARG_INFO(0, itemName)
	ZEND_ARG_INFO(0, childName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_hasItemChild, 0, 0, 2)
	ZEND_ARG_INFO(0, itemName)
	ZEND_ARG_INFO(0, childName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_getItemChildren, 0, 0, 1)
	ZEND_ARG_INFO(0, itemName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_assign, 0, 0, 2)
	ZEND_ARG_INFO(0, itemName)
	ZEND_ARG_INFO(0, userId)
	ZEND_ARG_INFO(0, bizRule)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_revoke, 0, 0, 2)
	ZEND_ARG_INFO(0, itemName)
	ZEND_ARG_INFO(0, userId)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_isAssigned, 0, 0, 2)
	ZEND_ARG_INFO(0, itemName)
	ZEND_ARG_INFO(0, userId)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_getAuthAssignment, 0, 0, 2)
	ZEND_ARG_INFO(0, itemName)
	ZEND_ARG_INFO(0, userId)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_getAuthAssignments, 0, 0, 1)
	ZEND_ARG_INFO(0, userId)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_saveAuthAssignment, 0, 0, 1)
	ZEND_ARG_INFO(0, assignment)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_iauthmanager_executeBizRule, 0, 0, 3)
	ZEND_ARG_INFO(0, bizRule)
	ZEND_ARG_ARRAY_INFO(1, params, 0)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
/* }}} */

/** {{{ IAuthManager's methods 
*/
YII_CLASS_METHODS(iauthmanager){
	PHP_ABSTRACT_ME(IAuthManager, checkAccess, arginfo_iauthmanager_checkAccess)
	PHP_ABSTRACT_ME(IAuthManager, createAuthItem, arginfo_iauthmanager_createAuthItem)
	PHP_ABSTRACT_ME(IAuthManager, removeAuthItem, arginfo_iauthmanager_removeAuthItem)
	PHP_ABSTRACT_ME(IAuthManager, getAuthItems, arginfo_iauthmanager_getAuthItems)
	PHP_ABSTRACT_ME(IAuthManager, getAuthItem, arginfo_iauthmanager_getAuthItem)
	PHP_ABSTRACT_ME(IAuthManager, saveAuthItem, arginfo_iauthmanager_saveAuthItem)
	PHP_ABSTRACT_ME(IAuthManager, addItemChild, arginfo_iauthmanager_addItemChild)
	PHP_ABSTRACT_ME(IAuthManager, removeItemChild, arginfo_iauthmanager_removeItemChild)
	PHP_ABSTRACT_ME(IAuthManager, hasItemChild, arginfo_iauthmanager_hasItemChild)
	PHP_ABSTRACT_ME(IAuthManager, getItemChildren, arginfo_iauthmanager_getItemChildren)
	PHP_ABSTRACT_ME(IAuthManager, assign, arginfo_iauthmanager_assign)
	PHP_ABSTRACT_ME(IAuthManager, revoke, arginfo_iauthmanager_revoke)
	PHP_ABSTRACT_ME(IAuthManager, isAssigned, arginfo_iauthmanager_isAssigned)
	PHP_ABSTRACT_ME(IAuthManager, getAuthAssignment, arginfo_iauthmanager_getAuthAssignment)
	PHP_ABSTRACT_ME(IAuthManager, getAuthAssignments, arginfo_iauthmanager_getAuthAssignments)
	PHP_ABSTRACT_ME(IAuthManager, saveAuthAssignment, arginfo_iauthmanager_saveAuthAssignment)
	PHP_ABSTRACT_ME(IAuthManager, clearAll, NULL)
	PHP_ABSTRACT_ME(IAuthManager, clearAuthAssignments, NULL)
	PHP_ABSTRACT_ME(IAuthManager, save, NULL)
	PHP_ABSTRACT_ME(IAuthManager, executeBizRule, arginfo_iauthmanager_executeBizRule)
	PHP_FE_END
};

/** {{{ interface IAuthManager
*/
YII_CLASS_FUNCTION(iauthmanager){

	YII_CLASS_INTERFACE(IAuthManager, iauthmanager);

	return SUCCESS;
}
/* }}} */