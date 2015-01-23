TEMPLATE = vcapp
TARGET = qtZint
CONFIG += 	warn_on \
			thread \
			qt \
			uitools \
			release

FORMS = mainWindow.ui \
		extSequence.ui \ 
		extExport.ui \
		extData.ui

HEADERS = 	mainwindow.h \
			barcodeitem.h \
			datawindow.h \
			exportwindow.h \
			sequencewindow.h

SOURCES = 	main.cpp \ 
			mainwindow.cpp \
			barcodeitem.cpp \
			datawindow.cpp \
			exportwindow.cpp \
			sequencewindow.cpp

RESOURCES = resources.qrc

INCLUDEPATH += ../backend_qt4 ../backend
# QMAKE_LIBDIR= path to libpng and zlib libraries
# QMAKE_LIBDIR not needed for Framework downloaded from official site
QMAKE_LIBDIR += e:/opt/lib

CONFIG(debug, debug|release) {
QMAKE_LIBDIR +=	../backend_qt4/debug
}

CONFIG(release, debug|release) {
QMAKE_LIBDIR +=	../backend_qt4/release
}

RC_FILE = ./res/qtZint.rc
# Remove pngMT.lib zlibMT.lib if qt is downloaded from official site
LIBS = QtZint2.lib pngMT.lib zlibMT.lib
