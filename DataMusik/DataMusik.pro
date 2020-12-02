#-------------------------------------------------
#
# Project created by QtCreator 2017-08-14T00:18:39
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataMusik
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    ../Classes/Banco.cpp \
    ../Classes/Acessorio.cpp \
    ../Classes/Instrumento.cpp \
    ../Classes/Midia.cpp \
    ../Classes/Usuario.cpp \
    ../Classes/Sessao.cpp \
    ../Classes/ClasseGenerica.cpp \
    ../Forms/CadastroAcessorios.cpp \
    ../Forms/CadastroInstrumentos.cpp \
    ../Forms/CadastroMidias.cpp \
    ../Forms/CadastroUsuario.cpp \
    ../Forms/Consulta.cpp \
    ../Forms/Logon.cpp \
    ../Forms/TelaPrincipal.cpp \
    ../Forms/TelaSessao.cpp \
    ../Forms/SessaoAtual.cpp \
    ../Forms/SplashScreen.cpp

HEADERS += \
    ../Classes/Banco.h \
    ../Classes/Acessorio.h \
    ../Classes/Instrumento.h \
    ../Classes/Midia.h \
    ../Classes/Usuario.h \
    ../Classes/Sessao.h \
    ../Classes/ClasseGenerica.h \
    ../Forms/CadastroAcessorios.h \
    ../Forms/CadastroInstrumentos.h \
    ../Forms/CadastroMidias.h \
    ../Forms/CadastroUsuario.h \
    ../Forms/Consulta.h \
    ../Forms/Logon.h \
    ../Forms/TelaPrincipal.h \
    ../Forms/TelaSessao.h \
    ../Forms/SessaoAtual.h \
    ../Forms/SplashScreen.h \
    ../Classes/Produto.h

FORMS += \
    ../UIs/frmCadastroAcessorios.ui \
    ../UIs/frmCadastroInstrumentos.ui \
    ../UIs/frmCadastroUsuario.ui \
    ../UIs/frmConsulta.ui \
    ../UIs/frmLogon.ui \
    ../UIs/frmCadastroMidias.ui \
    ../UIs/frmTelaSessao.ui \
    ../UIs/frmTelaPrincipal.ui \
    ../UIs/frmSessaoAtual.ui \
    ../UIs/frmSplashScreen.ui

RESOURCES += \
    imagens.qrc
