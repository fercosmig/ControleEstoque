QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fm_colaborador_vendas.cpp \
    fm_editar_item_venda.cpp \
    fm_gestao_colaboradores.cpp \
    fm_gestao_estoque.cpp \
    fm_gestao_fornecedores.cpp \
    fm_gestao_tipo_pagamento.cpp \
    fm_gestao_vendas.cpp \
    fm_login.cpp \
    fm_nova_venda.cpp \
    global_functions.cpp \
    global_variables.cpp \
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
    fm_colaborador_vendas.h \
    fm_editar_item_venda.h \
    fm_gestao_colaboradores.h \
    fm_gestao_estoque.h \
    fm_gestao_fornecedores.h \
    fm_gestao_tipo_pagamento.h \
    fm_gestao_vendas.h \
    fm_login.h \
    fm_nova_venda.h \
    fm_principal.h \
    global_functions.h \
    global_variables.h

FORMS += \
    fm_colaborador_vendas.ui \
    fm_editar_item_venda.ui \
    fm_gestao_colaboradores.ui \
    fm_gestao_estoque.ui \
    fm_gestao_fornecedores.ui \
    fm_gestao_tipo_pagamento.ui \
    fm_gestao_vendas.ui \
    fm_login.ui \
    fm_nova_venda.ui \
    fm_principal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource_files.qrc
