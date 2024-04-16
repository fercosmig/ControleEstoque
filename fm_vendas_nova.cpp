#include "fm_vendas_nova.h"
#include "ui_fm_vendas_nova.h"

#include <QMessageBox>

#include "global.h"
#include "ProdutoController.h"
#include <QMessageBox>
#include "FormaPagamentoController.h"
#include "VendaController.h"
#include "ItemVendaController.h"

fm_vendas_nova::fm_vendas_nova(QWidget *parent) : QDialog(parent), ui(new Ui::fm_vendas_nova)
{
    ui->setupUi(this);

    fm_vendas_nova::inicializa_fm_vendas_nova();
}

fm_vendas_nova::~fm_vendas_nova()
{
    delete ui;
}

/* ***** ***** ***** ***** *****
 *  MY METHODS
 * ***** ***** ***** ***** *****/

void fm_vendas_nova::inicializa_fm_vendas_nova()
{
    fm_vendas_nova::configura_table_widget();
    ui->label_selected_row->setVisible(false);
    fm_vendas_nova::carrega_combo_forma_pagamento();
}

void fm_vendas_nova::configura_table_widget()
{
    QStringList header;
    header = {"Quantidade", "ID produto", "Descricao", "Qtd. Estoque", "Custo", "Valor", "ID Fornecedor", "Razao Social", "Nome Fantasia", "Sub-Total"};
    global::formatTableWidget(ui->tableWidget_itens_venda, header);
    ui->tableWidget_itens_venda->setColumnHidden(4, true);
    ui->tableWidget_itens_venda->setColumnHidden(6, true);
    ui->tableWidget_itens_venda->setColumnHidden(7, true);
    ui->tableWidget_itens_venda->setColumnHidden(8, true);
}

void fm_vendas_nova::adiciona_produto_table_widget(int quantidade, Produto produto)
{
    int row;
    double subtotal;

    row = ui->tableWidget_itens_venda->rowCount();

    ui->tableWidget_itens_venda->insertRow(row);
    ui->tableWidget_itens_venda->setItem(row, 0, new QTableWidgetItem(global::formatDoubleToString(quantidade)));
    ui->tableWidget_itens_venda->setItem(row, 1, new QTableWidgetItem(produto.getId()));
    ui->tableWidget_itens_venda->setItem(row, 2, new QTableWidgetItem(produto.getDescricao()));
    ui->tableWidget_itens_venda->setItem(row, 3, new QTableWidgetItem(global::formatDoubleToString(produto.getQuantidade())));
    ui->tableWidget_itens_venda->setItem(row, 4, new QTableWidgetItem(global::formatDoubleToString(produto.getCusto())));
    ui->tableWidget_itens_venda->setItem(row, 5, new QTableWidgetItem(global::formatDoubleToString(produto.getValor())));
    ui->tableWidget_itens_venda->setItem(row, 6, new QTableWidgetItem(QString::number(produto.getFornecedor().getId())));
    ui->tableWidget_itens_venda->setItem(row, 7, new QTableWidgetItem(produto.getFornecedor().getRazaoSocial()));
    ui->tableWidget_itens_venda->setItem(row, 8, new QTableWidgetItem(produto.getFornecedor().getNomeFantasia()));
    subtotal = quantidade * produto.getValor();
    ui->tableWidget_itens_venda->setItem(row, 9, new QTableWidgetItem(global::formatDoubleToString(subtotal)));
    ui->tableWidget_itens_venda->setRowHeight(row, 20);
}

void fm_vendas_nova::limpa_formulario()
{
    ui->lineEdit_quantidade->setText("1");
    ui->lineEdit_id_produto->clear();
    ui->lineEdit_id_produto->setFocus();
    ui->comboBox_forma_pagamento->setCurrentIndex(0);
}

double fm_vendas_nova::calcula_total(QTableWidget *table_widget, int column)
{
    int row;
    double soma;

    row = table_widget->rowCount();
    soma = 0;

    if (row > 0) {
        for (int i = 0; i < row; ++i) {
            soma += table_widget->item(i, column)->text().toDouble();
        }
    }
    return soma;
}

void fm_vendas_nova::atualiza_total()
{
    double soma;
    soma = fm_vendas_nova::calcula_total(ui->tableWidget_itens_venda, 9);
    ui->lineEdit_valor_total->setText(global::formatDoubleToString(soma));
}
void fm_vendas_nova::carrega_combo_forma_pagamento()
{
    FormaPagamento forma_pagamento;
    QVector<FormaPagamento> listaFormasPagamento;
    FormaPagamentoController forma_pagamento_controller;

    listaFormasPagamento = forma_pagamento_controller.buscaTodos();

    ui->comboBox_forma_pagamento->addItem("Selecione", 0);

    for (int i = 0; i < listaFormasPagamento.size(); ++i) {
        forma_pagamento = listaFormasPagamento[i];
        ui->comboBox_forma_pagamento->addItem(forma_pagamento.getDescricao(), forma_pagamento.getId());
    }
}

void fm_vendas_nova::habilita_edicao_item_venda(bool editar)
{

    if(!editar)
    {
        ui->label_descricao->setText("");
        ui->lineEdit_quantidade_edicao->clear();
        ui->lineEdit_valor->clear();
    }
    ui->lineEdit_quantidade_edicao->setEnabled(editar);
    ui->lineEdit_valor->setEnabled(editar);
    ui->pushButton_salvar->setEnabled(editar);
    ui->pushButton_cancelar->setEnabled(editar);
}
/* ***** ***** ***** ***** *****
 *  SLOTS
 * ***** ***** ***** ***** *****/

void fm_vendas_nova::on_pushButton_fechar_clicked()
{
    close();
}

void fm_vendas_nova::on_lineEdit_id_produto_returnPressed()
{
    double quantidade;
    QString id;
    Produto produto;
    ProdutoController produto_controller;

    quantidade = ui->lineEdit_quantidade->text().toDouble();
    id = ui->lineEdit_id_produto->text().trimmed();

    produto.setId(id);
    produto = produto_controller.buscaPorId(produto);
    if (produto.getId() == "0") {
        QMessageBox::warning(this, "", "Produto não encontrado!");
        return;
    } else {
        fm_vendas_nova::adiciona_produto_table_widget(quantidade, produto);
        fm_vendas_nova::limpa_formulario();
    }
    fm_vendas_nova::atualiza_total();
}

void fm_vendas_nova::on_tableWidget_itens_venda_itemSelectionChanged()
{
    int row;
    row = ui->tableWidget_itens_venda->currentRow();
    ui->label_selected_row->setText(QString::number(row));
}

void fm_vendas_nova::on_pushButton_editar_clicked()
{
    QString descricao;
    double quantidade, valor;
    bool editar;

    int row = ui->tableWidget_itens_venda->currentRow();
    if (row < 0)
        QMessageBox::warning(this, "", "Selecione um item");
    else {

        editar = true;
        fm_vendas_nova::habilita_edicao_item_venda(editar);
        descricao = ui->tableWidget_itens_venda->item(row, 2)->text();
        quantidade = ui->tableWidget_itens_venda->item(row, 0)->text().toDouble();
        valor = ui->tableWidget_itens_venda->item(row, 5)->text().toDouble();

        ui->label_descricao->setText(descricao);
        ui->lineEdit_quantidade_edicao->setText(QString::number(quantidade));
        ui->lineEdit_valor->setText(QString::number(valor));
    }
}

void fm_vendas_nova::on_pushButton_excluir_clicked()
{
    QString descricao;
    QMessageBox::StandardButton resposta;

    int row = ui->tableWidget_itens_venda->currentRow();
    if (row < 0)
        QMessageBox::warning(this, "", "Selecione um item");
    else {
        descricao = ui->tableWidget_itens_venda->item(row, 2)->text();
        resposta = QMessageBox::question(this, "", "Tem certeza que quer excluir" + descricao, QMessageBox::Yes | QMessageBox::No);
        if (resposta == QMessageBox::Yes) {
            ui->tableWidget_itens_venda->removeRow(row);
            fm_vendas_nova::atualiza_total();
            QMessageBox::warning(this, "", descricao = " removido com sucesso!");
        }
    }
}

void fm_vendas_nova::on_pushButton_finalizar_clicked()
{
    int id_forma_pagamento, quantidade_itens;
    double valor_total, quantidade, valor;
    QString descricao, mensagem;
    Venda venda;
    VendaController venda_controller;
    FormaPagamento forma_pagamento;
    ItemVenda item_venda;
    ItemVendaController item_venda_controller;
    Produto produto;

    quantidade_itens = ui->tableWidget_itens_venda->rowCount();
    if (quantidade_itens <= 0) {
        QMessageBox::warning(this, "", "Adicione itens a venda.");
        return;
    }

    id_forma_pagamento = ui->comboBox_forma_pagamento->currentData().toInt();
    descricao = ui->comboBox_forma_pagamento->currentText();

    if (id_forma_pagamento == 0) {
        QMessageBox::warning(this, "", "Selecione uma forma de pagamento.");
        return;
    }

    forma_pagamento.setId(id_forma_pagamento);
    forma_pagamento.setDescricao(descricao);

    valor_total = fm_vendas_nova::calcula_total(ui->tableWidget_itens_venda, 9);

    venda.setValor(valor_total);
    venda.setFormaPagamento(forma_pagamento);
    venda.setColaborador(global::colaboradorLogado);
    venda = venda_controller.insere(venda);

     item_venda.setVenda(venda);

    for (int i = 0; i < quantidade_itens; ++i) {

        quantidade = ui->tableWidget_itens_venda->item(i, 0)->text().toDouble();
        valor = ui->tableWidget_itens_venda->item(i, 5)->text().toDouble();
        produto.setId(ui->tableWidget_itens_venda->item(i, 1)->text());

        item_venda.setQuantidade(quantidade);
        item_venda.setValor(valor);
        item_venda.setProduto(produto);

        item_venda_controller.insere(item_venda);
    }
    mensagem = "Venda finalizada com sucesso!\n";
    mensagem += "ID da venda: " + QString::number(venda.getId()) + "\n";
    mensagem += "Valor total da venda: " + QString::number(valor_total);
    QMessageBox::information(this, "", mensagem);

    fm_vendas_nova::limpa_formulario();
    fm_vendas_nova::configura_table_widget();
    fm_vendas_nova::atualiza_total();
}

void fm_vendas_nova::on_pushButton_salvar_clicked()
{
    int row;
    double quantidade, valor, subtotal;
    bool editar;

    quantidade = ui->lineEdit_quantidade_edicao->text().replace(",", ".").toDouble();
    valor = ui->lineEdit_valor->text().replace(",", ".").toDouble();
    row = ui->label_selected_row->text().toInt();

    ui->tableWidget_itens_venda->item(row, 0)->setText(global::formatDoubleToString(quantidade));
    ui->tableWidget_itens_venda->item(row, 5)->setText(global::formatDoubleToString(valor));
    subtotal = quantidade * valor;
    ui->tableWidget_itens_venda->item(row, 9)->setText(global::formatDoubleToString(subtotal));
    fm_vendas_nova::atualiza_total();
    editar = false;
    fm_vendas_nova::habilita_edicao_item_venda(editar);
}

void fm_vendas_nova::on_pushButton_cancelar_clicked()
{
    bool editar;

    editar = false;
    fm_vendas_nova::habilita_edicao_item_venda(editar);
}
