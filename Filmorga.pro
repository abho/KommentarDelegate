#-------------------------------------------------
#
# Project created by QtCreator 2011-01-08T20:20:33
#
#-------------------------------------------------

QT       += network sql

TARGET = Filmorga
TEMPLATE = app


SOURCES += main.cpp\
        filmorga.cpp \
    ../LiteTest/hdb.cpp \
    filminfoladedialog.cpp \
    ../GeFilmInfotManager/getfilminfomanager.cpp \
    ofdbaswahldia.cpp \
    ofdbauswahlbut.cpp

HEADERS  += filmorga.h \
    ../LiteTest/hdb.h \
    ../hfilm.h \
    filminfoladedialog.h \
    ../hfilm.h \
    ../GeFilmInfotManager/getfilminfomanager.h \
    ofdbaswahldia.h \
    ofdbauswahlbut.h \
    ../hkommentar.h

FORMS +=
