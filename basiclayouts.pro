QT += widgets

HEADERS     = \
    mainwindow.h \
    meaningobject.h
SOURCES     = \
              main.cpp \
    mainwindow.cpp \
    meaningobject.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/layouts/basiclayouts
INSTALLS += target

FORMS += \
    mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    qrcFile.qrc
