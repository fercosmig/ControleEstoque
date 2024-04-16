#ifndef FM_PRINCIPAL_H
#define FM_PRINCIPAL_H

#include <QMainWindow>

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

    // MY VARIABLES
    QIcon iconLocked, iconUnlocked;

    // MY METHODS
    void inicializa_fm_principal();
    void configura_autenticacao();

private slots:
    void on_pushButton_fechar_clicked();

    void on_pushButton_autenticacao_clicked();

    void on_actionFornecedores_triggered();

    void on_actionGrupos_triggered();

    void on_actionSobre_triggered();

    void on_actionFormas_pagamento_triggered();

    void on_actionColaboradores_triggered();

    void on_actionProdutos_triggered();

    void on_pushButton_clicked();

    void on_actionVendas_triggered();

private:
    Ui::fm_principal *ui;
};
#endif // FM_PRINCIPAL_H
