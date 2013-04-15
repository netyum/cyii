PHP_ARG_ENABLE(yii, whether to enable yii framework, [ --enable-yii   Enable yii framework])

if test "$PHP_YII" = "yes"; then
  AC_DEFINE(HAVE_YII, 1, [Whether you have Yii Framework])
 
  PHP_NEW_EXTENSION(yii, 
    yii.c \
	func.c \
	\
	system/base/interface/yii_iapplicationcomponent.c \
	system/base/interface/yii_iaction.c \
	system/base/interface/yii_iauthmanager.c \
	system/base/interface/yii_ibehavior.c \
	system/base/interface/yii_icache.c \
	system/base/interface/yii_icachedependency.c \
	system/base/interface/yii_idataprovider.c \
	system/base/interface/yii_ifilter.c \
	system/base/interface/yii_ilogfilter.c \
	system/base/interface/yii_istatepersister.c \
	system/base/interface/yii_iuseridentity.c \
	system/base/interface/yii_iviewrenderer.c \
	system/base/interface/yii_iwebserviceprovider.c \
	system/base/interface/yii_iwebuser.c \
	system/base/interface/yii_iwidgetfactory.c \
	\
	system/base/yii_ccomponent.c \
	system/base/yii_cevent.c \
	\
	system/collections/yii_clist.c \
	system/collections/yii_clistiterator.c \
	\
	system/yii_yiibase.c,            
  $ext_shared)
fi
