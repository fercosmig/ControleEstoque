#include "fm_principal.h"
#include "ui_fm_principal.h"

#include <QMessageBox>
#include "global.h"
#include "fm_autenticacao.h"
#include "fm_fornecedores.h"
#include "fm_grupos.h"
#include "fm_forma_pagamento.h"
#include "fm_colaboradores.h"
#include "fm_produtos.h"
#include "fm_vendas_nova.h"
#include "fm_vendas.h"

fm_principal::fm_principal(QWidget *parent) : QMainWindow(parent), ui(new Ui::fm_principal)
{
    ui->setupUi(this);

    fm_principal::inicializa_fm_principal();
}

fm_principal::~fm_principal()
{
    delete ui;
}

/* ***** ***** ***** ***** *****
 *  MY METHODS
 * ***** ***** ***** ***** *****/

void fm_principal::inicializa_fm_principal()
{
    global::initializeGlobalVariables();

    fm_principal::iconLocked.addFile(":/icons/images/lock.png");
    fm_principal::iconUnlocked.addFile(":/icons/images/unlock.png");

    fm_principal::configura_autenticacao();

    ui->label_versao->setText("Versão: " + global::version);
}

void fm_principal::configura_autenticacao()
{
    QString strLabel;

    ui->pushButton_autenticacao->setText("");

    if (global::isLogged) {
        ui->pushButton_autenticacao->setIcon(fm_principal::iconUnlocked);
        strLabel = global::colaboradorLogado.getGrupo().getSigla();
        strLabel += " | ";
        strLabel += global::colaboradorLogado.getNome();
    } else {
        ui->pushButton_autenticacao->setIcon(fm_principal::iconLocked);
        strLabel = "Autentique-se!";
    }

    ui->label_status_login->setText(strLabel);

    ui->statusbar->addWidget(ui->pushButton_autenticacao);
    ui->statusbar->addWidget(ui->label_status_login);
}

/* ***** ***** ***** ***** *****
 *  SLOTS
 * ***** ***** ***** ***** *****/

void fm_principal::on_pushButton_fechar_clicked()
{
    QApplication::quit();
}

void fm_principal::on_pushButton_autenticacao_clicked()
{
    fm_autenticacao f_autenticacao;

    if (global::isLogged)
        global::isLogged = false;
    else
        f_autenticacao.exec();

    fm_principal::configura_autenticacao();
}

void fm_principal::on_actionFornecedores_triggered()
{
    fm_fornecedores f_fornecedores;

    if (global::isLogged) {
        if (global::colaboradorLogado.getGrupo().getSigla() == "A")
            f_fornecedores.exec();
        else
            QMessageBox::warning(this, "", "Acesso negado!");
    } else
        QMessageBox::warning(this, "", "Autentique-se!");
}

void fm_principal::on_actionGrupos_triggered()
{
    fm_grupos f_grupos;

    if (global::isLogged) {
        if (global::colaboradorLogado.getGrupo().getSigla() == "A")
            f_grupos.exec();
        else
            QMessageBox::warning(this, "", "Acesso negado!");
    } else
        QMessageBox::warning(this, "", "Autentique-se!");
}

void fm_principal::on_actionSobre_triggered()
{
    QString informacoes;
    informacoes = "Sistema de controle de estoque\n\n";
    informacoes += "Desenvolvido por Fernando Costa Migliorini\n\n";
    informacoes += "entre 29/03/2024 e 07/04/2024.\n\n";
    informacoes +="Desenvolvido em C++ (QtCreator) & SQLITE\n\n";
    informacoes +="Versão: " + global::version;
    QMessageBox::information(this, "Controle de EStoque", informacoes);
}

void fm_principal::on_actionFormas_pagamento_triggered()
{
    fm_forma_pagamento f_forma_pagamento;

    if (global::isLogged) {
        if (global::colaboradorLogado.getGrupo().getSigla() == "A")
            f_forma_pagamento.exec();
        else
            QMessageBox::warning(this, "", "Acesso negado!");
    } else
        QMessageBox::warning(this, "", "Autentique-se!");
}

void fm_principal::on_actionColaboradores_triggered()
{
    fm_colaboradores f_colaboradores;

    if (global::isLogged) {
        if (global::colaboradorLogado.getGrupo().getSigla() == "A")
            f_colaboradores.exec();
        else
            QMessageBox::warning(this, "", "Acesso negado!");
    } else
        QMessageBox::warning(this, "", "Autentique-se!");
}

void fm_principal::on_actionProdutos_triggered()
{
    fm_produtos f_produtos;

    if (global::isLogged) {
        if (global::colaboradorLogado.getGrupo().getSigla() == "A")
            f_produtos.exec();
        else
            QMessageBox::warning(this, "", "Acesso negado!");
    } else
        QMessageBox::warning(this, "", "Autentique-se!");
}

void fm_principal::on_pushButton_clicked()
{
    fm_vendas_nova f_vendas_nova;

    if (global::isLogged) {
            f_vendas_nova.exec();
    } else
        QMessageBox::warning(this, "", "Autentique-se!");
}

void fm_principal::on_actionVendas_triggered()
{
    fm_vendas f_vendas;

    if (global::isLogged) {
        if (global::colaboradorLogado.getGrupo().getSigla() == "A")
            f_vendas.exec();
        else
            QMessageBox::warning(this, "", "Acesso negado!");
    } else
        QMessageBox::warning(this, "", "Autentique-se!");
}

