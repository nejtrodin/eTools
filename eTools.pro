QT += quick quickcontrols2
QT += xml svg

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

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

SOURCES += \
    documenttreemodel.cpp \
    eagle/brdparser.cpp \
    eagle/ecommon.cpp \
    eagle/edesignrules.cpp \
    eagle/eelement.cpp \
    eagle/elibrary.cpp \
    eagle/epackage.cpp \
    eagle/eboard.cpp \
    eagle/eplain.cpp \
    eagle/esignal.cpp \
    tools/drillreporter.cpp \
    tools/efileinfo.cpp \
    main.cpp

HEADERS += \
    documenttreemodel.h \
    eagle/brdparser.h \
    eagle/ecommon.h \
    eagle/edesignrules.h \
    eagle/eelement.h \
    eagle/elibrary.h \
    eagle/epackage.h \
    eagle/eboard.h \
    eagle/eplain.h \
    eagle/esignal.h \
    tools/drillreporter.h \
    tools/efileinfo.h

RESOURCES += qml/qml.qrc \
    images.qrc

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
