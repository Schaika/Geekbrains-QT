QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogshortcuts.cpp \
    filestatus.cpp \
    main.cpp \
    mainwindow.cpp \
    qmdisubwindo_custom.cpp \
    qtextedit_custom.cpp

HEADERS += \
    dialogshortcuts.h \
    filestatus.h \
    mainwindow.h \
    qmdisubwindo_custom.h \
    qtextedit_custom.h

FORMS += \
    dialogshortcuts.ui \
    mainwindow.ui

TRANSLATIONS += \
    notepad_multitab_en_US.ts \
    notepad_multitab_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
