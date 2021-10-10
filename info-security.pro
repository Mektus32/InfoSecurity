QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    forms/admin.cpp \
    forms/admin_change_user.cpp \
    forms/main_window.cpp \
    forms/promt.cpp \
    forms/update_user.cpp \
    forms/user_promt.cpp \
    main.cpp \
    users/user.cpp \
    utils/utils.cpp

HEADERS += \
    forms/admin.hpp \
    forms/admin_change_user.hpp \
    forms/main_window.hpp \
    forms/promt.hpp \
    forms/update_user.hpp \
    forms/user_promt.h \
    users/user.hpp \
    utils/utils.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
