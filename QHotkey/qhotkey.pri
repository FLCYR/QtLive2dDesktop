CONFIG += C++11

PUBLIC_HEADERS += $$PWD/QHotkey/qhotkey.h \
	$$PWD/QHotkey/QHotkey

HEADERS += $$PUBLIC_HEADERS \
	$$PWD/QHotkey/qhotkey_p.h

SOURCES += $$PWD/QHotkey/qhotkey.cpp

win32: SOURCES += $$PWD/QHotkey/qhotkey_win.cpp


INCLUDEPATH += $$PWD/QHotkey

#include($$PWD/qhotkey.prc)
