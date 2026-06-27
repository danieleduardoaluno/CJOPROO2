QT += core gui widgets
CONFIG += c++17
CONFIG -= app_bundle

TARGET = ATM_Project
TEMPLATE = app

# Lista de todos os arquivos de código-fonte
SOURCES += \
    account.cpp \
    bankdatabase.cpp \
    main.cpp \
    mainwindow.cpp

# Lista de todos os cabeçalhos
HEADERS += \
    account.h \
    bankdatabase.h \
    mainwindow.h
