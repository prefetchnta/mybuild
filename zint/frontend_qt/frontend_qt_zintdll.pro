TEMPLATE = app
TARGET = qtZint
QT += uitools
QT += widgets
QT += svg

# Input
HEADERS += barcodeitem.h \
         cliwindow.h \
         datawindow.h \
         exportwindow.h \
         mainwindow.h \
         scalewindow.h \
         sequencewindow.h

FORMS += extCLI.ui \
         extData.ui \
         extExport.ui \
         extSequence.ui \
         extScale.ui \
         grpAztec.ui \
         grpC11.ui \
         grpC128.ui \
         grpC16k.ui \
         grpC25.ui \
         grpC39.ui \
         grpC49.ui \
         grpC93.ui \
         grpChannel.ui \
         grpCodabar.ui \
         grpCodablockF.ui \
         grpCodeOne.ui \
         grpDAFT.ui \
         grpDBExtend.ui \
         grpDM.ui \
         grpDotCode.ui \
         grpDPD.ui \
         grpGrid.ui \
         grpHX.ui \
         grpITF14.ui \
         grpMailmark2D.ui \
         grpMaxicode.ui \
         grpMicroPDF.ui \
         grpMQR.ui \
         grpMSICheck.ui \
         grpPDF417.ui \
         grpPZN.ui \
         grpQR.ui \
         grpRMQR.ui \
         grpUltra.ui \
         grpUPCA.ui \
         grpUPCEAN.ui \
         grpUPNQR.ui \
         grpVIN.ui \
         mainWindow.ui

SOURCES += barcodeitem.cpp \
        cliwindow.cpp \
        datawindow.cpp \
        exportwindow.cpp \
        main.cpp \
        mainwindow.cpp \
        scalewindow.cpp \
        sequencewindow.cpp

RESOURCES += resources.qrc

RC_FILE += res/qtZint.rc

INCLUDEPATH += ../backend_qt ../backend

LIBS += -lQtZintDLL -lzint
QMAKE_LIBDIR += ../backend_qt/release
QMAKE_LIBDIR += ../win32/Release
