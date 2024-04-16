#include "fm_fornecedores.h"
#include "ui_fm_fornecedores.h"

#include "global.h"
#include "FornecedorController.h"
#include <QMessageBox>

fm_fornecedores::fm_fornecedores(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_fornecedores)
{
    ui->setupUi(this);

    fm_fornecedores::inicializa_fm_fornecedores();
}

fm_fornecedores::~fm_fornecedores()
{
    delete ui;
}

/* ***** ***** ***** ***** *****
 *  MY METHODS
 * ***** ***** ***** ***** *****/

void fm_fornecedores::inicializa_fm_fornecedores()
{
    fm_fornecedores::atualiza_table_widget();

    ui->label_selected_row->setVisible(false);
}

void fm_fornecedores::atualiza_table_widget()
{
    QVector<Fornecedor> listaFornecedores;
    FornecedorController fornecedor_controller;

    listaFornecedores = fornecedor_controller.buscaTodos();
    fm_fornecedores::popula_table_widget(listaFornecedores);
}

void fm_fornecedores::popula_table_widget(QVector<Fornecedor> listaFornecedores)
{
    QStringList header;
    Fornecedor fornecedor;

    header = {"ID", "Razão social", "Nome fantasia"};
    global::formatTableWidget(ui->tableWidget_fornecedores, header);

    for (int i = 0; i < listaFornecedores.size(); ++i) {
        fornecedor = listaFornecedores[i];
        ui->tableWidget_fornecedores->insertRow(i);
        ui->tableWidget_fornecedores->setItem(i, 0, new QTableWidgetItem(QString::number(fornecedor.getId())));
        ui->tableWidget_fornecedores->setItem(i, 1, new QTableWidgetItem(fornecedor.getRazaoSocial()));
        ui->tableWidget_fornecedores->setItem(i, 2, new QTableWidgetItem(fornecedor.getNomeFantasia()));
        ui->tableWidget_fornecedores->setRowHeight(i, 20);
    }
}

void fm_fornecedores::limpa_formulario()
{
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_razao_social->clear();
    ui->lineEdit_nome_fantasia->clear();
    ui->lineEdit_pesquisar->setFocus();
    ui->label_selected_row->setText("-1");
}

/* ***** ***** ***** ***** *****
 *  SLOTS
 * ***** ***** ***** ***** *****/

void fm_fornecedores::on_tableWidget_fornecedores_itemSelectionChanged()
{
    int row, id;
    QString razao_social, nome_fantasia;

    row = ui->tableWidget_fornecedores->currentRow();
    ui->label_selected_row->setText(QString::number(row));

    id = ui->tableWidget_fornecedores->item(row, 0)->text().toInt();
    razao_social = ui->tableWidget_fornecedores->item(row, 1)->text();
    nome_fantasia = ui->tableWidget_fornecedores->item(row, 2)->text();

    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_razao_social->setText(razao_social);
    ui->lineEdit_nome_fantasia->setText(nome_fantasia);
}

void fm_fornecedores::on_pushButton_limpar_clicked()
{
    fm_fornecedores::limpa_formulario();
}

void fm_fornecedores::on_pushButton_fechar_clicked()
{
    close();
}

void fm_fornecedores::on_pushButton_salvar_clicked()
{
    int row, id;
    QString razao_social, nome_fantasia;
    Fornecedor fornecedor;
    FornecedorController fornecedor_controller;
    QMessageBox::StandardButton resposta;

    row = ui->label_selected_row->text().toInt();

    id = ui->lineEdit_id->text().toInt();
    razao_social = ui->lineEdit_razao_social->text().trimmed();
    nome_fantasia = ui->lineEdit_nome_fantasia->text().trimmed();

    if (global::minCharacters(razao_social, 3) && global::minCharacters(nome_fantasia, 3)){

        fornecedor.setId(id);
        fornecedor.setRazaoSocial(razao_social);
        fornecedor.setNomeFantasia(nome_fantasia);

        if (row >= 0) { // ALTERAÇÃO DE FORNECEDOR
            resposta = QMessageBox::question(this, "", "Tem certeza que deseja alterar?", QMessageBox::Yes | QMessageBox::No);
            if (resposta == QMessageBox::Yes) {
                if (fornecedor_controller.altera(fornecedor)) {
                    ui->tableWidget_fornecedores->item(row, 1)->setText(fornecedor.getRazaoSocial());
                    ui->tableWidget_fornecedores->item(row, 2)->setText(fornecedor.getNomeFantasia());
                    QMessageBox::information(this, "", "Alterado com sucesso!");
                } else
                    QMessageBox::warning(this, "", "Erro ao tentar alterar.");
            }
        } else { // CADASTRO DE FORNECEDOR
            resposta = QMessageBox::question(this, "", "Tem certeza que deseja cadastrar?", QMessageBox::Yes | QMessageBox::No);
            if (resposta == QMessageBox::Yes) {
                fornecedor =  fornecedor_controller.insere(fornecedor);
                row = ui->tableWidget_fornecedores->rowCount();
                ui->tableWidget_fornecedores->insertRow(row);
                ui->tableWidget_fornecedores->setItem(row, 0, new QTableWidgetItem(QString::number(fornecedor.getId())));
                ui->tableWidget_fornecedores->setItem(row, 1, new QTableWidgetItem(fornecedor.getRazaoSocial()));
                ui->tableWidget_fornecedores->setItem(row, 2, new QTableWidgetItem(fornecedor.getNomeFantasia()));
                ui->tableWidget_fornecedores->setRowHeight(row, 20);
                QMessageBox::information(this, "", "Cadastrado com sucesso!");
            }
        }
    }else
        QMessageBox::warning(this, "", "Razao Social e Nome Fantasia devem ter no mínimo 3 caracteres.");
}

void fm_fornecedores::on_pushButton_mostrar_todos_clicked()
{
    fm_fornecedores::atualiza_table_widget();
    fm_fornecedores::limpa_formulario();
    ui->pushButton_mostrar_todos->setEnabled(false);
}

void fm_fornecedores::on_pushButton_pesquisar_clicked()
{
    QString texto_pesquisar;
    Fornecedor fornecedor;
    FornecedorController fornecedor_controller;
    QVector<Fornecedor> listaFornecedores;

    texto_pesquisar = ui->lineEdit_pesquisar->text().trimmed();

    if (global::minCharacters(texto_pesquisar, 3)) {
        fornecedor.setRazaoSocial(texto_pesquisar);
        fornecedor.setNomeFantasia(texto_pesquisar);

        listaFornecedores = fornecedor_controller.buscaPorRazaoSocialNomeFantasia(fornecedor);
        fm_fornecedores::popula_table_widget(listaFornecedores);
    } else
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres.");

    fm_fornecedores::limpa_formulario();
    ui->pushButton_mostrar_todos->setEnabled(true);
}
