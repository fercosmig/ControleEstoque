#include "fm_gestao_fornecedores.h"
#include <QMessageBox>
#include "Fornecedor.h"
#include "FornecedorController.h"
#include "global_functions.h"
#include "ui_fm_gestao_fornecedores.h"

fm_gestao_fornecedores::fm_gestao_fornecedores(QWidget *parent) : QDialog(parent), ui(new Ui::fm_gestao_fornecedores)
{
    ui->setupUi(this);

    inicializa_fm_gestao_fornecedores();
}

fm_gestao_fornecedores::~fm_gestao_fornecedores()
{
    delete ui;
}

/* ***********************************************************************************
 *
 * MINHAS FUNÇÕES LOCAIS
 *
 * ********************************************************************************* */

void fm_gestao_fornecedores::inicializa_fm_gestao_fornecedores()
{
    FornecedorController fornecedor_controller;
    QVector<Fornecedor> listaFornecedores;
    listaFornecedores = fornecedor_controller.buscaTodos();
    popula_tableWidget_fornecedores(listaFornecedores);

    QStringList cabecalho = {"ID", "Razão social", "Nome fantasia"};
    global_functions::formata_table_widget(ui->tableWidget_fornecedores,cabecalho);

}

void fm_gestao_fornecedores::popula_tableWidget_fornecedores(QVector<Fornecedor> listaFornecedores)
{
    global_functions::limpa_table_widget(ui->tableWidget_fornecedores);

    int contador = 0;

    for (Fornecedor fornecedor : listaFornecedores) {
        ui->tableWidget_fornecedores->insertRow(contador);
        ui->tableWidget_fornecedores->setItem(contador, 0, new QTableWidgetItem(QString::number(fornecedor.getId())));
        ui->tableWidget_fornecedores->setItem(contador, 1, new QTableWidgetItem(fornecedor.getRazaoSocial()));
        ui->tableWidget_fornecedores->setItem(contador, 2, new QTableWidgetItem(fornecedor.getNomeFantasia()));
        ui->tableWidget_fornecedores->setRowHeight(contador, 20);
        contador++;
    }
}

void fm_gestao_fornecedores::limpa_formulario_fornecedor_pesquisa()
{
    ui->lineEdit_pesquisa_nome_fantasia->clear();
    ui->lineEdit_pesquisa_nome_fantasia->setFocus();
}

void fm_gestao_fornecedores::limpa_formulario_fornecedor_edit()
{
    ui->lineEdit_id_edit->clear();
    ui->lineEdit_razao_social_edit->clear();
    ui->lineEdit_nome_fantasia_edit->clear();

    ui->pushButton_salvar_edit->setEnabled(false);
    ui->pushButton_excluir_edit->setEnabled(false);
    ui->pushButton_cancelar_edit->setEnabled(false);

    ui->lineEdit_razao_social->setFocus();
}

void fm_gestao_fornecedores::limpa_formulario_fornecedor_novo()
{
    ui->lineEdit_razao_social->clear();
    ui->lineEdit_nome_fantasia->clear();
    ui->lineEdit_razao_social->setFocus();
}

/* ***********************************************************************************
 *
 * SLOTS
 *
 * ********************************************************************************* */

void fm_gestao_fornecedores::on_pushButton_fechar_clicked()
{
    close();
}

void fm_gestao_fornecedores::on_pushButton_salvar_novo_clicked()
{
    QString razao_social, nome_fantasia;
    FornecedorController fornecedor_controller;
    QVector<Fornecedor> listaFornecedores;
    Fornecedor fornecedor;

    razao_social = ui->lineEdit_razao_social->text();
    nome_fantasia = ui->lineEdit_nome_fantasia->text();
    fornecedor.setRazaoSocial(razao_social);
    fornecedor.setNomeFantasia(nome_fantasia);
    
    if (global_functions::minCaracter(razao_social, 3) && global_functions::minCaracter(nome_fantasia, 3)) {
        if (fornecedor_controller.insere(fornecedor)) {
            listaFornecedores = fornecedor_controller.buscaTodos();
            popula_tableWidget_fornecedores(listaFornecedores);

            QMessageBox::information(this, "", "Salvo com sucesso!");
            limpa_formulario_fornecedor_novo();
        } else
            QMessageBox::warning(this, "", "Falha ao salvar!");
        limpa_formulario_fornecedor_novo();
    } else {
        QMessageBox::warning(this, "", "Mínimo 3 caracteres.");
        limpa_formulario_fornecedor_novo();
    }
}

void fm_gestao_fornecedores::on_pushButton_limpar_formulario_novo_clicked()
{
    limpa_formulario_fornecedor_novo();
}

void fm_gestao_fornecedores::on_pushButton_pesquisar_clicked()
{
    QString pesquisar;
    FornecedorController fornecedor_controller;
    QVector<Fornecedor> listaFornecedores;

    pesquisar = ui->lineEdit_pesquisa_nome_fantasia->text();
    if (global_functions::minCaracter(pesquisar, 3)) {
        if (ui->radioButton_razao_social->isChecked()) {
            listaFornecedores = fornecedor_controller.buscaPorRazaoSocial(pesquisar);
            popula_tableWidget_fornecedores(listaFornecedores);
            limpa_formulario_fornecedor_pesquisa();
        }

        if (ui->radioButton_nome_fantasia->isChecked()) {
            listaFornecedores = fornecedor_controller.buscaPorNomeFantasia(pesquisar);
            popula_tableWidget_fornecedores(listaFornecedores);
            limpa_formulario_fornecedor_pesquisa();
        }
    } else {
        listaFornecedores = fornecedor_controller.buscaTodos();
        popula_tableWidget_fornecedores(listaFornecedores);
        limpa_formulario_fornecedor_pesquisa();
    }
}

void fm_gestao_fornecedores::on_tableWidget_fornecedores_itemSelectionChanged()
{
    int row = ui->tableWidget_fornecedores->currentRow();

    int id_forncedor;
    QString razao_social, nome_fantasia;

    id_forncedor = ui->tableWidget_fornecedores->item(row, 0)->text().toInt();
    razao_social = ui->tableWidget_fornecedores->item(row, 1)->text();
    nome_fantasia = ui->tableWidget_fornecedores->item(row, 2)->text();

    ui->lineEdit_id_edit->setText(QString::number(id_forncedor));
    ui->lineEdit_razao_social_edit->setText(razao_social);
    ui->lineEdit_nome_fantasia_edit->setText(nome_fantasia);

    ui->pushButton_salvar_edit->setEnabled(true);
    ui->pushButton_excluir_edit->setEnabled(true);
    ui->pushButton_cancelar_edit->setEnabled(true);
}

void fm_gestao_fornecedores::on_pushButton_cancelar_edit_clicked()
{
    limpa_formulario_fornecedor_edit();
}

void fm_gestao_fornecedores::on_pushButton_excluir_edit_clicked()
{
    QMessageBox::StandardButton resposta;
    resposta = QMessageBox::question(this, "", "Deseja realmente excluir?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        FornecedorController fornecedor_controller;
        int row, id_fornecedor;

        row = ui->tableWidget_fornecedores->currentRow();
        id_fornecedor = ui->tableWidget_fornecedores->item(row, 0)->text().toInt();
        if (fornecedor_controller.remove(id_fornecedor)) {
            ui->tableWidget_fornecedores->removeRow(row);

            QMessageBox::information(this, "", "Excluido!");
            limpa_formulario_fornecedor_edit();
        } else {
            QMessageBox::warning(this, "", "Erro ao excluir.");
            limpa_formulario_fornecedor_edit();
        }
    }
}

void fm_gestao_fornecedores::on_pushButton_salvar_edit_clicked()
{
    int id_fornecedor, row;
    QString razao_social, nome_fantasia;
    FornecedorController fornecedor_controller;

    row = ui->tableWidget_fornecedores->currentRow();
    id_fornecedor = ui->lineEdit_id_edit->text().trimmed().toInt();
    razao_social = ui->lineEdit_razao_social_edit->text().trimmed();
    nome_fantasia = ui->lineEdit_nome_fantasia_edit->text().trimmed();
    
    if (global_functions::minCaracter(razao_social, 3) && global_functions::minCaracter(nome_fantasia, 3)) {
        Fornecedor fornecedor;
        fornecedor.setId(id_fornecedor);
        fornecedor.setRazaoSocial(razao_social);
        fornecedor.setNomeFantasia(nome_fantasia);

        if (fornecedor_controller.altera(fornecedor)) {
            ui->tableWidget_fornecedores->item(row, 1)->setText(fornecedor.getRazaoSocial());
            ui->tableWidget_fornecedores->item(row, 2)->setText(fornecedor.getNomeFantasia());

            QMessageBox::information(this, "", "Alterado com sucesso!");
            limpa_formulario_fornecedor_edit();
        } else {
            QMessageBox::warning(this, "", "Erro ao alterar.");
            limpa_formulario_fornecedor_edit();
        }
    } else {
        QMessageBox::warning(this, "", "Mínimo 3 caracteres.");
        limpa_formulario_fornecedor_edit();
    }
}
