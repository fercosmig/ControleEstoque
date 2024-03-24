#ifndef FM_PRINCIPAL_H
#define FM_PRINCIPAL_H

#include <QMainWindow>
#include "Colaborador.h"
#include "QSqlDatabase"

QT_BEGIN_NAMESPACE
namespace Ui {
class fm_principal;
}
QT_END_NAMESPACE

class fm_principal : public QMainWindow
{
    Q_OBJECT

public:
    fm_principal(QWidget *parent = nullptr);
    ~fm_principal();

    // MINHAS VARIAVEIS PARA O FORMULARIO
    QIcon cadeado_fechado, cadeado_aberto;
    QString msgPermissao, msgLogin;

    // MINHAS FUNÇÕES PARA O FORMULARIO
    void configurar_login(bool valor);
    void inicializa_fm_principal();

private slots:
    void on_pushButton_bloquear_statusbar_clicked();

    void on_pushButton_nova_venda_clicked();

    void on_actionEstoque_triggered();

    void on_actionColaboradores_triggered();

    void on_actionVendas_triggered();

    void on_actionSair_triggered();

    void on_actionSobre_triggered();

    void on_pushButton_fechar_clicked();

    void on_actionFornecedores_triggered();

    void on_actionTipos_de_pagamento_triggered();

private:
    Ui::fm_principal *ui;
};
#endif // FM_PRINCIPAL_H
