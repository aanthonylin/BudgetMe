QT       += core widgets charts
TARGET = ./bin/BudgetMe
INCLUDEPATH += -L/usr/include/mysql/mysql 
LIBS += -lmysqlclient -lcurl -lcurlpp
CONFIG += c++11
TEMPLATE = app
SOURCES += main.cpp mainwindow.cpp privacyview.cpp starterbudgetview.cpp budgetmemodel.cpp \
           SQLManager.cpp simplebudgetmanager.cpp \
					 ReportModel.cpp GraphModel.cpp baseview.cpp featuremodel.cpp ReportView.cpp \
					 entertransactionview.cpp smartbudgetview.cpp previewbudgetview.cpp  GraphView.cpp \
					 summaryspendingmodel.cpp summarybudgetmodel.cpp summarypreviewmodel.cpp \
					 compareavgmodel.cpp comparebudgetmodel.cpp comparepreviewmodel.cpp \
					 comparelocalmodel.cpp compareservermodel.cpp LoginLocalView.cpp submitview.cpp \
					 BudgetMeDataManager.cpp RequestManager.cpp StatsCanadaManager.cpp \
					 summaryoverspendingview.cpp maincontroller.cpp preferencesview.cpp \
					 preferencesmanager.cpp summarytransactionmodel.cpp summarytransactionview.cpp \
					 guestwindow.cpp
HEADERS += budgetmeconstants.h mainwindow.h privacyview.h starterbudgetview.h \
           budgetmemodel.h LocalStorageManager.h SQLManager.h budgetmanager.h \
					 simplebudgetmanager.h ReportModel.h GraphModel.h baseview.h featuremodel.h \
					 privacysettingsmodel.h mainwindowmodel.h ReportView.h starterbudgetmodel.h \
					 entertransactionmodel.h entertransactionview.h smartbudgetmodel.h smartbudgetview.h \
					 previewbudgetmodel.h previewbudgetview.h GraphView.h summaryspendingmodel.h \
					 summarybudgetmodel.h summarypreviewmodel.h compareavgmodel.h comparebudgetmodel.h \
					 comparepreviewmodel.h comparelocalmodel.h compareservermodel.h LoginLocalView.h \ 
					 LoginLocalModel.h submitview.h BudgetMeDataManager.h RequestManager.h \
					 StatsCanadaManager.h warningmanager.h summaryoverspendingview.h \
					 maincontroller.h preferencesview.h preferencesmodel.h preferencesmanager.h \
					 summarytransactionmodel.h summarytransactionview.h guestwindow.h
RESOURCES = application.qrc
VPATH += ./src 
