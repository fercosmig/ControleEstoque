QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fm_autenticacao.cpp \
    fm_colaboradores.cpp \
    fm_forma_pagamento.cpp \
    fm_fornecedores.cpp \
    fm_grupos.cpp \
    fm_produtos.cpp \
    fm_vendas.cpp \
    fm_vendas_nova.cpp \
    global.cpp \
    main.cpp \
    fm_principal.cpp

HEADERS += \
    Colaborador.h \
    ColaboradorController.h \
    Conexao.h \
    FormaPagamento.h \
    FormaPagamentoController.h \
    Fornecedor.h \
    FornecedorController.h \
    Grupo.h \
    GrupoController.h \
    ItemVenda.h \
    ItemVendaController.h \
    Produto.h \
    ProdutoController.h \
    Venda.h \
    VendaController.h \
    fm_autenticacao.h \
    fm_colaboradores.h \
    fm_forma_pagamento.h \
    fm_fornecedores.h \
    fm_grupos.h \
    fm_principal.h \
    fm_produtos.h \
    fm_vendas.h \
    fm_vendas_nova.h \
    global.h

FORMS += \
    fm_autenticacao.ui \
    fm_colaboradores.ui \
    fm_forma_pagamento.ui \
    fm_fornecedores.ui \
    fm_grupos.ui \
    fm_principal.ui \
    fm_produtos.ui \
    fm_vendas.ui \
    fm_vendas_nova.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource_files.qrc
