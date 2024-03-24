#include "fm_gestao_estoque.h"
#include <QMessageBox>
#include "Fornecedor.h"
#include "FornecedorController.h"
#include "Produto.h"
#include "ProdutoController.h"
#include "global_functions.h"
#include "ui_fm_gestao_estoque.h"

fm_gestao_estoque::fm_gestao_estoque(QWidget *parent) : QDialog(parent), ui(new Ui::fm_gestao_estoque)
{
    ui->setupUi(this);

    inicializa_fm_gestao_estoque();
}

fm_gestao_estoque::~fm_gestao_estoque()
{
    delete ui;
}

/* ***********************************************************************************
 *
 * MINHAS FUNÇÕES LOCAIS
 *
 * ********************************************************************************* */

void fm_gestao_estoque::popula_combobox_fornecedores()
{
    QVector<Fornecedor> listaFornecedores;
    FornecedorController fornecedor_controller;
    listaFornecedores = fornecedor_controller.buscaTodos();

    ui->comboBox_fornecedor->addItem("Selecione", 0);
    ui->comboBox_fornecedor_edit->addItem("Selecione", 0);

    for (Fornecedor fornecedor : listaFornecedores) {
        ui->comboBox_fornecedor->addItem(fornecedor.getNomeFantasia(), fornecedor.getId());
        ui->comboBox_fornecedor_edit->addItem(fornecedor.getNomeFantasia(), fornecedor.getId());
    }
}

void fm_gestao_estoque::inicializa_fm_gestao_estoque()
{
    ui->tabWidget_produtos->setCurrentIndex(0);

    popula_combobox_fornecedores();

    QStringList cabecalho = {"ID", "Descricao", "Qtd", "R$ compra", "R$ venda", "Fornecedor"};
    global_functions::formata_table_widget(ui->tableWidget_produtos, cabecalho);
}

void fm_gestao_estoque::popula_table_widget_produtos(QVector<Produto> lista_produtos)
{
    global_functions::limpa_table_widget(ui->tableWidget_produtos);

    int contador = 0;

    for (Produto produto : lista_produtos) {

        ui->tableWidget_produtos->insertRow(contador);

        ui->tableWidget_produtos->setItem(contador, 0, new QTableWidgetItem(QString::number(produto.getId())));
        ui->tableWidget_produtos->setItem(contador, 1, new QTableWidgetItem(produto.getDescricao()));
        ui->tableWidget_produtos->setItem(contador, 2, new QTableWidgetItem(QString::number(produto.getQuantidade())));
        ui->tableWidget_produtos->setItem(contador, 3, new QTableWidgetItem(global_functions::formata_double(produto.getValorCompra())));
        ui->tableWidget_produtos->setItem(contador, 4, new QTableWidgetItem(global_functions::formata_double(produto.getValorVenda())));
        ui->tableWidget_produtos->setItem(contador, 5, new QTableWidgetItem(produto.getFornecedor().getNomeFantasia()));

        ui->tableWidget_produtos->setRowHeight(contador, 20);
        contador++;
    }
}

void fm_gestao_estoque::limpa_formulario_edicao_produto()
{
    ui->lineEdit_id_produto_edit->clear();
    ui->lineEdit_descricao_produto_Edit->clear();
    ui->lineEdit_quantidade_produto_edit->clear();
    ui->lineEdit_valor_compra_produto_edit->clear();
    ui->lineEdit_valor_venda_produto_edit->clear();

    ui->pushButton_salvar_produto_edit->setEnabled(false);
    ui->pushButton_excluir_produto->setEnabled(false);
    ui->pushButton_cancelar_produto_Edit->setEnabled(false);

    ui->lineEdit_descricao_produto_Edit->setFocus();
}

void fm_gestao_estoque::limpa_formulario_cadastro_produto()
{
    ui->lineEdit_id_produto->clear();
    ui->lineEdit_descricao_produto->clear();
    ui->lineEdit_quantidade_produto->clear();
    ui->lineEdit_valor_compra_produto->clear();
    ui->lineEdit_valor_venda_produto->clear();

    ui->lineEdit_id_produto->setFocus();
}

/* ***********************************************************************************
 *
 * SLOTS
 *
 * ********************************************************************************* */

void fm_gestao_estoque::on_pushButton_cancelar_produto_clicked()
{
    limpa_formulario_cadastro_produto();
}

void fm_gestao_estoque::on_pushButton_salvar_produto_clicked()
{
    QString descricao_produto;
    int id_produto, id_fornecedor, quantidade;
    double valor_compra, valor_venda;
    ProdutoController produto_controller;
    Produto produto;
    FornecedorController fornecedor_controller;

    id_produto = ui->lineEdit_id_produto->text().trimmed().toInt();
    descricao_produto = ui->lineEdit_descricao_produto->text().trimmed();
    id_fornecedor = ui->comboBox_fornecedor->currentData().toInt();
    quantidade = ui->lineEdit_quantidade_produto->text().trimmed().toInt();
    valor_compra = ui->lineEdit_valor_compra_produto->text().trimmed().replace(",", ".").toDouble();
    valor_venda = ui->lineEdit_valor_venda_produto->text().trimmed().replace(",", ".").toDouble();

    produto.setId(id_produto);
    produto.setDescricao(descricao_produto);
    produto.setFornecedor(fornecedor_controller.buscaPorId(id_fornecedor));
    produto.setQuantidade(quantidade);
    produto.setValorCompra(valor_compra);
    produto.setValorVenda(valor_venda);

    int duplicidade = produto_controller.buscaIdDuplicado(produto.getId());
    
    if (id_produto != 0 && global_functions::minCaracter(descricao_produto, 3)) {
        if (duplicidade == 0) {
            if (produto_controller.insere(produto)) {
                QMessageBox::information(this, "", "Produto inserido com sucesso!");
                limpa_formulario_cadastro_produto();
            }
        } else {
            QMessageBox::warning(this, "", "Já existe produto com este código!");
            limpa_formulario_cadastro_produto();
        }
    } else {
        QMessageBox::warning(this, "", "Mínimo de 3 caracteres");
        limpa_formulario_cadastro_produto();
    }
}

void fm_gestao_estoque::on_pushButton_fechar_clicked()
{
    close();
}

void fm_gestao_estoque::on_tabWidget_produtos_currentChanged(int index)
{
    if (index == 1) {
        ProdutoController produto_controller;
        QVector<Produto> lista_produtos = produto_controller.buscaTodos();
        popula_table_widget_produtos(lista_produtos);
    }
}

void fm_gestao_estoque::on_tableWidget_produtos_itemSelectionChanged()
{
    int row = ui->tableWidget_produtos->currentRow();
    int id = ui->tableWidget_produtos->item(row, 0)->text().toInt();

    ProdutoController produto_controller;
    Produto produto = produto_controller.buscaPorId(id);

    ui->lineEdit_id_produto_edit->setText(QString::number(produto.getId()));
    ui->lineEdit_descricao_produto_Edit->setText(produto.getDescricao());

    int index = ui->comboBox_fornecedor_edit->findData(produto.getFornecedor().getId());
    ui->comboBox_fornecedor_edit->setCurrentIndex(index);

    ui->lineEdit_quantidade_produto_edit->setText(QString::number(produto.getQuantidade()));
    ui->lineEdit_valor_compra_produto_edit->setText(QString::number(produto.getValorCompra()));
    ui->lineEdit_valor_venda_produto_edit->setText(QString::number(produto.getValorVenda()));

    ui->pushButton_salvar_produto_edit->setEnabled(true);
    ui->pushButton_excluir_produto->setEnabled(true);
    ui->pushButton_cancelar_produto_Edit->setEnabled(true);
}

void fm_gestao_estoque::on_pushButton_cancelar_produto_Edit_clicked()
{
    limpa_formulario_edicao_produto();
}

void fm_gestao_estoque::on_pushButton_salvar_produto_edit_clicked()
{
    QString descricao_produto;
    int id_produto, id_fornecedor, quantidade;
    double valor_compra, valor_venda;
    ProdutoController produto_controller;
    Produto produto;
    FornecedorController fornecedor_controller;

    int row = ui->tableWidget_produtos->currentRow();
    id_produto = ui->tableWidget_produtos->item(row, 0)->text().toInt();

    descricao_produto = ui->lineEdit_descricao_produto_Edit->text().trimmed();
    id_fornecedor = ui->comboBox_fornecedor_edit->currentData().toInt();
    quantidade = ui->lineEdit_quantidade_produto_edit->text().trimmed().toInt();
    valor_compra = ui->lineEdit_valor_compra_produto_edit->text().trimmed().replace(",", ".").toDouble();
    valor_venda = ui->lineEdit_valor_venda_produto_edit->text().trimmed().replace(",", ".").toDouble();

    produto.setId(id_produto);
    produto.setDescricao(descricao_produto);
    produto.setFornecedor(fornecedor_controller.buscaPorId(id_fornecedor));
    produto.setQuantidade(quantidade);
    produto.setValorCompra(valor_compra);
    produto.setValorVenda(valor_venda);
    
    if (id_produto != 0 && global_functions::minCaracter(descricao_produto, 3)) {
        if (produto_controller.altera(produto)) {
            ui->tableWidget_produtos->item(row, 1)->setText(produto.getDescricao());
            ui->tableWidget_produtos->item(row, 2)->setText(QString::number(produto.getQuantidade()));
            ui->tableWidget_produtos->item(row, 3)->setText(QString::number(produto.getValorCompra()));
            ui->tableWidget_produtos->item(row, 4)->setText(QString::number(produto.getValorVenda()));
            ui->tableWidget_produtos->item(row, 5)->setText(produto.getFornecedor().getNomeFantasia());

            QMessageBox::information(this, "", "Produto alterado com sucesso!");
            limpa_formulario_edicao_produto();
        } else
            QMessageBox::warning(this, "", "Falha ao tentar alterar produto!");
    } else {
        QMessageBox::warning(this, "", "Mínimo 3 caracteres.");
    }
}

void fm_gestao_estoque::on_pushButton_excluir_produto_clicked()
{
    QMessageBox::StandardButton resposta;
    resposta = QMessageBox::question(this, "Confirmação", "Deseja realmente excluir?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        QString id_produto;
        ProdutoController produto_controller;

        int row = ui->tableWidget_produtos->currentRow();
        id_produto = ui->tableWidget_produtos->item(row, 0)->text();

        if (produto_controller.remove(id_produto)) {
            ui->tableWidget_produtos->removeRow(row);
            limpa_formulario_edicao_produto();
            QMessageBox::information(this, "", "Produto removido com sucesso!");
        }
    }
}

void fm_gestao_estoque::on_pushButton_pesquisar_produto_clicked()
{
    QString pesquisar = ui->lineEdit_pesquisar_produto->text();
    ui->lineEdit_pesquisar_produto->clear();

    ProdutoController produto_controller;
    Produto produto;
    QVector<Produto> lista_produtos;
    
    if (global_functions::minCaracter(pesquisar, 3)) {

        if (ui->radioButton_id_produto->isChecked()) {
            produto = produto_controller.buscaPorId(pesquisar.toInt());
            lista_produtos.push_back(produto);
        }

        if (ui->radioButton_descricao_produto->isChecked())
            lista_produtos = produto_controller.buscaPorDescricao(pesquisar);

    } else
        lista_produtos = produto_controller.buscaTodos();

    popula_table_widget_produtos(lista_produtos);
}
