QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StudentManager
TEMPLATE = app

CONFIG += c++17

SOURCES += \
    main.cpp \
    src/models/Student.cpp \
    src/models/UndergraduateStudent.cpp \
    src/models/GraduateStudent.cpp \
    src/models/PhDStudent.cpp \
    src/services/StudentManager.cpp \
    src/persistence/PersistenceManager.cpp \
    src/gui/MainWindow.cpp \
    src/gui/StudentDialog.cpp

HEADERS += \
    src/models/Student.h \
    src/models/UndergraduateStudent.h \
    src/models/GraduateStudent.h \
    src/models/PhDStudent.h \
    src/services/StudentManager.h \
    src/persistence/PersistenceManager.h \
    src/exceptions/StudentExceptions.h \
    src/gui/MainWindow.h \
    src/gui/StudentDialog.h