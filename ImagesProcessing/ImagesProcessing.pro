    HEADERS += \
    image.h \
    histogram.h \
    thresholding.h \
    imageexeption.h \
    filter.h \
    contrast.h \
    edge.h

SOURCES += \
    image.cpp \
    histogram.cpp \
    thresholding.cpp \
    main.cpp \
    imageexeption.cpp \
    filter.cpp \
    contrast.cpp \
    edge.cpp

QMAKE_CXXFLAGS += -DHAVE_CONFIG_H

unix:!macx:!symbian: LIBS += -ldcmimgle

unix:!macx:!symbian: LIBS += -ldcmdata

unix:!macx:!symbian: LIBS += -loflog

unix:!macx:!symbian: LIBS += -lofstd

unix:!macx:!symbian: LIBS += -lz
