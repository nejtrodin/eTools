QT += quick quickcontrols2
QT += xml svg
QT += printsupport
QT += widgets

CONFIG += c++11
CONFIG += qtquickcompiler

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050F00

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# for Windows
VERSION = 0.0.0.1
QMAKE_TARGET_COMPANY = SVD Company
QMAKE_TARGET_PRODUCT = eTools
QMAKE_TARGET_DESCRIPTION = eTools
QMAKE_TARGET_COPYRIGHT = (c) Vyasheslav Sinishenko
RC_ICONS = images/eTools.ico

INCLUDEPATH += core
INCLUDEPATH += eagle/common
INCLUDEPATH += eagle/sch
INCLUDEPATH += eagle/brd

SOURCES += \
    bomlistmodel.cpp \
    core/layer.cpp \
    core/schSettings.cpp \
    documenttreemodel.cpp \
    eagle/eattribute.cpp \
    eagle/ecircle.cpp \
    eagle/ecommon.cpp \
    eagle/drawingtext.cpp \
    eagle/elayer.cpp \
    eagle/erectangle.cpp \
    eagle/etext.cpp \
    eagle/evalueattribute.cpp \
    eagle/ewire.cpp \
    eagle/brd/eelement.cpp \
    eagle/brd/eboard.cpp \
    eagle/brd/edesignrules.cpp \
    eagle/brd/ebrdplain.cpp \
    eagle/brd/ebrdvia.cpp \
    eagle/brd/esignal.cpp \
    eagle/lbr/edevice.cpp \
    eagle/lbr/edeviceset.cpp \
    eagle/lbr/egate.cpp \
    eagle/lbr/elibrary.cpp \
    eagle/lbr/epackage.cpp \
    eagle/lbr/epad.cpp \
    eagle/lbr/epin.cpp \
    eagle/lbr/esymbol.cpp \
    eagle/lbr/etechnology.cpp \
    eagle/sch/eschcore.cpp \
    eagle/sch/eschematic.cpp \
    eagle/sch/eschinstance.cpp \
    eagle/sch/eschnet.cpp \
    eagle/sch/eschpart.cpp \
    eagle/sch/eschplain.cpp \
    eagle/sch/eschsheet.cpp \
    eagle/sch/esegment.cpp \
    folderlistmodel.cpp \
    layerlistmodel.cpp \
    schviewitem.cpp \
    tools/bom/bomparser.cpp \
    tools/bom/bomprinter.cpp \
    tools/drillreporter.cpp \
    tools/efileinfo.cpp \
    tools/schexport.cpp \
    main.cpp

HEADERS += \
    bomlistmodel.h \
    core/layer.h \
    core/schSettings.h \
    documenttreemodel.h \
    eagle/eattribute.h \
    eagle/ecircle.h \
    eagle/ecommon.h \
    eagle/drawingtext.h \
    eagle/elayer.h \
    eagle/erectangle.h \
    eagle/etext.h \
    eagle/evalueattribute.h \
    eagle/ewire.h \
    eagle/brd/eelement.h \
    eagle/brd/edesignrules.h \
    eagle/brd/eboard.h \
    eagle/brd/ebrdplain.h \
    eagle/brd/ebrdvia.h \
    eagle/brd/esignal.h \
    eagle/lbr/edevice.h \
    eagle/lbr/edeviceset.h \
    eagle/lbr/egate.h \
    eagle/lbr/elibrary.h \
    eagle/lbr/epackage.h \
    eagle/lbr/epad.h \
    eagle/lbr/epin.h \
    eagle/lbr/esymbol.h \
    eagle/lbr/etechnology.h \
    eagle/sch/eschcore.h \
    eagle/sch/eschematic.h \
    eagle/sch/eschinstance.h \
    eagle/sch/eschnet.h \
    eagle/sch/eschpart.h \
    eagle/sch/eschplain.h \
    eagle/sch/eschsheet.h \
    eagle/sch/esegment.h \
    folderlistmodel.h \
    layerlistmodel.h \
    schviewitem.h \
    tools/bom/bomentry.h \
    tools/bom/bomparser.h \
    tools/bom/bomprinter.h \
    tools/drillreporter.h \
    tools/efileinfo.h \
    tools/schexport.h

equals(QT_MAJOR_VERSION, 5) {
    RESOURCES += qml_qt5/qml.qrc \
} else {
    RESOURCES += qml/qml.qrc \
}

RESOURCES += fonts.qrc \
    images.qrc \

TRANSLATIONS += \
    eTools_ru_RU.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    todo.md \
    README.md

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
