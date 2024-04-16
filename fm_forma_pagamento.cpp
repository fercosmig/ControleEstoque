#include "fm_forma_pagamento.h"
#include "ui_fm_forma_pagamento.h"

#include "FormaPagamentoController.h"
#include "global.h"
#include <QMessageBox>

fm_forma_pagamento::fm_forma_pagamento(QWidget *parent) : QDialog(parent), ui(new Ui::fm_forma_pagamento)
{
    ui->setupUi(this);

    fm_forma_pagamento::inicializa_fm_forma_pagamento();
}

fm_forma_pagamento::~fm_forma_pagamento()
{
    delete ui;
}

/* ***** ***** ***** ***** *****
 *  MY METHODS
 * ***** ***** ***** ***** *****/

void fm_forma_pagamento::inicializa_fm_forma_pagamento()
{
    fm_forma_pagamento::atualiza_table_widget();
    ui->label_selected_row->setVisible(false);
}

void fm_forma_pagamento::atualiza_table_widget()
{
    QVector<FormaPagamento> listaFormasPagamento;
    FormaPagamentoController forma_pagamento_controller;

    listaFormasPagamento = forma_pagamento_controller.buscaTodos();
    fm_forma_pagamento::popula_table_widget(listaFormasPagamento);
}

void fm_forma_pagamento::popula_table_widget(QVector<FormaPagamento> ListaFormasPagamento)
{
    QStringList header;
    FormaPagamento forma_pagamento;

    header = {"ID", "Descricao"};
    global::formatTableWidget(ui->tableWidget_forma_pagamento, header);

    for (int i = 0; i < ListaFormasPagamento.size(); ++i) {
        forma_pagamento = ListaFormasPagamento[i];
        ui->tableWidget_forma_pagamento->insertRow(i);
        ui->tableWidget_forma_pagamento->setItem(i, 0, new QTableWidgetItem(QString::number(forma_pagamento.getId())));
        ui->tableWidget_forma_pagamento->setItem(i, 1, new QTableWidgetItem(forma_pagamento.getDescricao()));
        ui->tableWidget_forma_pagamento->setRowHeight(i, 20);
    }
}

void fm_forma_pagamento::limpa_formulario()
{
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_descricao->clear();
    ui->lineEdit_pesquisar->setFocus();
    ui->label_selected_row->setText("-1");
}

/* ***** ***** ***** ***** *****
 *  SLOTS
 * ***** ***** ***** ***** *****/

void fm_forma_pagamento::on_pushButton_pesquisar_clicked()
{
    QString texto_pesquisar;
    FormaPagamento forma_pagamento;
    QVector<FormaPagamento> listaFormasPagamento;
    FormaPagamentoController forma_pagamento_controller;

    texto_pesquisar = ui->lineEdit_pesquisar->text().trimmed();

    if (global::minCharacters(texto_pesquisar, 3)) {
        forma_pagamento.setDescricao(texto_pesquisar);

        listaFormasPagamento = forma_pagamento_controller.buscaPorDescricao(forma_pagamento);
        fm_forma_pagamento::popula_table_widget(listaFormasPagamento);
    } else
        QMessageBox::warning(this, "", "Mínimo de 3 caracteres.");

    fm_forma_pagamento::limpa_formulario();
    ui->pushButton_mostrar_todos->setEnabled(true);
}

void fm_forma_pagamento::on_pushButton_mostrar_todos_clicked()
{
    fm_forma_pagamento::atualiza_table_widget();
    fm_forma_pagamento::limpa_formulario();
    ui->pushButton_mostrar_todos->setEnabled(false);
}

void fm_forma_pagamento::on_tableWidget_forma_pagamento_itemSelectionChanged()
{
    int row, id;
    QString descricao;

    row = ui->tableWidget_forma_pagamento->currentRow();
    ui->label_selected_row->setText(QString::number(row));

    id = ui->tableWidget_forma_pagamento->item(row, 0)->text().toInt();
    descricao = ui->tableWidget_forma_pagamento->item(row, 1)->text();

    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_descricao->setText(descricao);
}

void fm_forma_pagamento::on_pushButton_salvar_clicked()
{
    int row, id;
    QString descricao;
    FormaPagamento forma_pagamento;
    FormaPagamentoController forma_pagamento_controller;

    id = ui->lineEdit_id->text().toInt();
    descricao = ui->lineEdit_descricao->text().trimmed();

    if (!global::minCharacters(descricao, 3)) {
        QMessageBox::warning(this, "", "Mínimo de 3 caracteres.");
        return;
    }

    forma_pagamento.setId(id);
    forma_pagamento.setDescricao(descricao);

    row = ui->label_selected_row->text().toInt();

    if (row == -1) { // INCLUSÃO

        forma_pagamento = forma_pagamento_controller.insere(forma_pagamento);
        row = ui->tableWidget_forma_pagamento->rowCount();
        ui->tableWidget_forma_pagamento->insertRow(row);
        ui->tableWidget_forma_pagamento->setItem(row, 0, new QTableWidgetItem(QString::number(forma_pagamento.getId())));
        ui->tableWidget_forma_pagamento->setItem(row, 1, new QTableWidgetItem(forma_pagamento.getDescricao()));
        ui->tableWidget_forma_pagamento->setRowHeight(row, 20);
        QMessageBox::information(this, "", "Cadastrado com sucesso!");
        fm_forma_pagamento::limpa_formulario();

    } else { // ALTERAÇÃO

        if (forma_pagamento_controller.altera(forma_pagamento)){
            ui->tableWidget_forma_pagamento->item(row, 1)->setText(forma_pagamento.getDescricao());
            QMessageBox::information(this, "", "Alterado com sucesso!");
            fm_forma_pagamento::limpa_formulario();
        } else
            QMessageBox::warning(this, "", "Problema ao tentar alterar.");
    }
}

void fm_forma_pagamento::on_pushButton_limpar_clicked()
{
    fm_forma_pagamento::limpa_formulario();
}

void fm_forma_pagamento::on_pushButton_fechar_clicked()
{
    close();
}
