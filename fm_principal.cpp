#include "fm_principal.h"
#include <QMessageBox>
#include "fm_gestao_colaboradores.h"
#include "fm_gestao_estoque.h"
#include "fm_gestao_fornecedores.h"
#include "fm_gestao_tipo_pagamento.h"
#include "fm_gestao_vendas.h"
#include "fm_login.h"
#include "fm_nova_venda.h"
#include "global_variables.h"
#include "ui_fm_principal.h"

fm_principal::fm_principal(QWidget *parent) : QMainWindow(parent), ui(new Ui::fm_principal)
{
    ui->setupUi(this);

    inicializa_fm_principal();
}

fm_principal::~fm_principal()
{
    delete ui;
}

/* ***********************************************************************************
 *
 * MINHAS FUNÇÕES LOCAIS
 *
 * ********************************************************************************* */

void fm_principal::inicializa_fm_principal()
{
    global_variables::isLogged = false;

    QString local_db = qApp->applicationDirPath();
    QString nome_db = "/db/controle_estoque.db";
    QString banco = local_db + nome_db;

    global_variables::bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    global_variables::bancoDeDados.setDatabaseName(banco);

    msgLogin = "Favor realizar a autenticação no sistema.";
    msgPermissao = "Desculpe, você não tem permissão para acessar esta funcionalidade.";

    configurar_login(global_variables::isLogged);
}

void fm_principal::configurar_login(bool valor)
{
    cadeado_fechado.addFile(":/icon/images/lock.svg");
    cadeado_aberto.addFile(":/icon/images/unlock.svg");

    ui->pushButton_bloquear_statusbar->setText("");
    ui->statusbar->addWidget(ui->pushButton_bloquear_statusbar);
    ui->label_dados_statusbar->setText("");
    ui->statusbar->addWidget(ui->label_dados_statusbar);

    if (valor) {

        QString texto = global_variables::colaboradorLogado.getGrupo().getSigla() + "|" + global_variables::colaboradorLogado.getNome();
        ui->pushButton_bloquear_statusbar->setIcon(cadeado_aberto);
        ui->label_dados_statusbar->setText(texto);

    } else
        ui->pushButton_bloquear_statusbar->setIcon(cadeado_fechado);
}

/* ***********************************************************************************
 *
 * SLOTS
 *
 * ********************************************************************************* */

void fm_principal::on_pushButton_bloquear_statusbar_clicked()
{
    fm_login f_login;

    if (global_variables::isLogged) {

        global_variables::isLogged = false;
        configurar_login(false);

    } else {

        f_login.exec();

        if (global_variables::isLogged)

            configurar_login(true);

    }
}

void fm_principal::on_pushButton_nova_venda_clicked()
{
    if (global_variables::isLogged) {

        fm_nova_venda f_nova_venda;
        f_nova_venda.exec();

    } else
        QMessageBox::warning(this,"", msgLogin);
}

void fm_principal::on_actionEstoque_triggered()
{
    if (global_variables::isLogged) {

        if (global_variables::colaboradorLogado.getGrupo().getSigla() == "A") {

            fm_gestao_estoque f_gestao_estoque;
            f_gestao_estoque.exec();

        } else
            QMessageBox::warning(this, "", msgPermissao);
    } else
        QMessageBox::warning(this, "", msgLogin);
}

void fm_principal::on_actionColaboradores_triggered()
{
    if (global_variables::isLogged) {
        if (global_variables::colaboradorLogado.getGrupo().getSigla() == "A") {

            fm_gestao_colaboradores f_gestao_colaboradores;
            f_gestao_colaboradores.exec();

        } else
            QMessageBox::warning(this, "", msgPermissao);
    } else
        QMessageBox::warning(this, "", msgLogin);
}

void fm_principal::on_actionVendas_triggered()
{
    if (global_variables::isLogged) {
        if (global_variables::colaboradorLogado.getGrupo().getSigla() == "A") {

            fm_gestao_vendas f_gestao_vendas;
            f_gestao_vendas.exec();

        } else
            QMessageBox::warning(this, "", msgPermissao);
    } else
        QMessageBox::warning(this, "", msgLogin);
}

void fm_principal::on_actionFornecedores_triggered()
{
    if (global_variables::isLogged) {
        if (global_variables::colaboradorLogado.getGrupo().getSigla() == "A") {

            fm_gestao_fornecedores f_gestao_fornecedores;
            f_gestao_fornecedores.exec();

        } else
            QMessageBox::warning(this, "", msgPermissao);
    } else
        QMessageBox::warning(this, "", msgLogin);
}

void fm_principal::on_actionTipos_de_pagamento_triggered()
{
    if (global_variables::isLogged) {
        if (global_variables::colaboradorLogado.getGrupo().getSigla() == "A") {

            fm_gestao_tipo_pagamento f_gestao_tipo_pagamento;
            f_gestao_tipo_pagamento.exec();

        } else
            QMessageBox::warning(this, "", msgPermissao);
    } else
        QMessageBox::warning(this, "", msgLogin);
}

void fm_principal::on_actionSobre_triggered()
{
    QMessageBox::aboutQt(this);
}

void fm_principal::on_actionSair_triggered()
{
    QApplication::quit();
}

void fm_principal::on_pushButton_fechar_clicked()
{
    QApplication::quit();
}
