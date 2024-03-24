#include "fm_nova_venda.h"
#include <QMessageBox>
#include "ColaboradorController.h"
#include "FormaPagamento.h"
#include "FormaPagamentoController.h"
#include "ItemVenda.h"
#include "ItemVendaController.h"
#include "Produto.h"
#include "ProdutoController.h"
#include "Venda.h"
#include "VendaController.h"
#include "fm_editar_item_venda.h"
#include "global_functions.h"
#include "global_variables.h"
#include "ui_fm_nova_venda.h"

QString fm_nova_venda::descricao_edicao_itens_venda;
QString fm_nova_venda::valor_venda_edicao_itens_venda;
QString fm_nova_venda::quantidade_edicao_itens_venda;

fm_nova_venda::fm_nova_venda(QWidget *parent) : QDialog(parent), ui(new Ui::fm_nova_venda)
{
    ui->setupUi(this);

    ui->lineEdit_id_produto->setFocus();
    inicializa_fm_nova_venda();
}

fm_nova_venda::~fm_nova_venda()
{
    delete ui;
}

/* ***********************************************************************************
 *
 * MINHAS FUNÇÕES LOCAIS
 *
 * ********************************************************************************* */

void fm_nova_venda::inicializa_fm_nova_venda()
{
    popula_combobox_forma_pagamento();

    QStringList cabecalho = {"Codigo", "Descrição", "R$ un.", "Qtd.", "R$ total"};
    global_functions::formata_table_widget(ui->tableWidget_itens_venda, cabecalho);
}

void fm_nova_venda::popula_combobox_forma_pagamento()
{
    QVector<FormaPagamento> listaFormaPagamento;
    FormaPagamentoController forma_pagamento_controller;
    listaFormaPagamento = forma_pagamento_controller.buscaTodos();

    for (FormaPagamento forma_pagamento : listaFormaPagamento)
        ui->comboBox_forma_pagamento->addItem(forma_pagamento.getDescricao(), forma_pagamento.getId());
}

double fm_nova_venda::calcula_total_tableWidget(QTableWidget *tw, int coluna)
{
    int linhas = tw->rowCount();
    double total = 0;

    for (int i = 0; i < linhas; i++) {
        total += tw->item(i, coluna)->text().toDouble();
    }

    return total;
}

void fm_nova_venda::limpa_formulario_venda()
{
    ui->lineEdit_quantidade_produto->setText("1");
    ui->lineEdit_id_produto->clear();
    ui->lineEdit_id_produto->setFocus();
}

void fm_nova_venda::adiciona_item_tableWidget_itens_venda(ItemVenda item_venda)
{
    double valor_total = item_venda.getQuantidade() * item_venda.getValorVenda();

    int row = ui->tableWidget_itens_venda->rowCount();

    ui->tableWidget_itens_venda->insertRow(row);
    ui->tableWidget_itens_venda->setItem(row, 0, new QTableWidgetItem(QString::number(item_venda.getProduto().getId())));
    ui->tableWidget_itens_venda->setItem(row, 1, new QTableWidgetItem(item_venda.getProduto().getDescricao()));
    ui->tableWidget_itens_venda->setItem(row, 2, new QTableWidgetItem(global_functions::formata_double(item_venda.getValorVenda())));
    ui->tableWidget_itens_venda->setItem(row, 3, new QTableWidgetItem(QString::number(item_venda.getQuantidade())));
    ui->tableWidget_itens_venda->setItem(row, 4, new QTableWidgetItem(global_functions::formata_double(valor_total)));
    ui->tableWidget_itens_venda->setRowHeight(row, 20);

    lista_itens_venda.push_back(item_venda);

    ui->label_total_venda->setText("R$ " + global_functions::formata_double(calcula_total_tableWidget(ui->tableWidget_itens_venda, 4)));
}

/* ***********************************************************************************
 *
 * SLOTS
 *
 * ********************************************************************************* */

void fm_nova_venda::on_pushButton_fechar_clicked()
{
    close();
}

void fm_nova_venda::on_lineEdit_id_produto_returnPressed()
{
    int id_produto, quantidade;
    id_produto = ui->lineEdit_id_produto->text().toInt();
    quantidade = ui->lineEdit_quantidade_produto->text().toInt();
    ProdutoController produto_controller;
    Produto produto;
    ItemVenda item_venda;

    if (id_produto != 0 && quantidade != 0) {
        produto = produto_controller.buscaPorId(id_produto);
        if (produto.getId() != 0) {
            item_venda.setProduto(produto);
            item_venda.setQuantidade(quantidade);
            item_venda.setValorVenda(produto.getValorVenda());

            adiciona_item_tableWidget_itens_venda(item_venda);

            limpa_formulario_venda();

        } else {
            limpa_formulario_venda();
            QMessageBox::warning(this, "Produto", "Produto não encontrado");
        }
    } else
        QMessageBox::warning(this, "Tamanho do campo", "Mínimo 3 caracteres.");
}

void fm_nova_venda::on_tableWidget_itens_venda_itemSelectionChanged()
{
    ui->pushButton_excluir_item->setEnabled(true);
    ui->pushButton_editar_item->setEnabled(true);
}

void fm_nova_venda::on_pushButton_excluir_item_clicked()
{
    /*
     * ui->tableWidget_itens_venda->currentColumn() retorna -1 caso não exista uma linha seleciona do tableWidget.
     */

    QMessageBox::StandardButton resposta;
    resposta = QMessageBox::question(this, "", "Deseja realmente excluir?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        int row = ui->tableWidget_itens_venda->currentRow();
        ui->tableWidget_itens_venda->removeRow(row);

        ui->label_total_venda->setText( "R$ " + QString::number(calcula_total_tableWidget(ui->tableWidget_itens_venda, 4)));
        ui->lineEdit_id_produto->setFocus();
    }
}

void fm_nova_venda::on_pushButton_editar_item_clicked()
{
    int selecao = ui->tableWidget_itens_venda->currentColumn();
    int row = ui->tableWidget_itens_venda->currentRow();
    if (selecao != -1) {
        descricao_edicao_itens_venda = ui->tableWidget_itens_venda->item(row, 1)->text();
        valor_venda_edicao_itens_venda = ui->tableWidget_itens_venda->item(row, 2)->text();
        quantidade_edicao_itens_venda = ui->tableWidget_itens_venda->item(row, 3)->text();
    }
    fm_editar_item_venda f_editar_item_venda;
    f_editar_item_venda.exec();

    ui->tableWidget_itens_venda->item(row, 2)->setText(valor_venda_edicao_itens_venda); // valor_venda
    ui->tableWidget_itens_venda->item(row, 3)->setText(quantidade_edicao_itens_venda); // quantidade

    double valor_total = valor_venda_edicao_itens_venda.toDouble() * quantidade_edicao_itens_venda.toInt();

    ui->tableWidget_itens_venda->item(row, 4)->setText(QString::number(valor_total)); // valor_total

    ui->label_total_venda->setText("R$ " + QString::number(calcula_total_tableWidget(ui->tableWidget_itens_venda, 4)));
    ui->lineEdit_id_produto->setFocus();
}

void fm_nova_venda::on_pushButton_finalizar_venda_clicked()
{
    if (ui->tableWidget_itens_venda->rowCount() > 0) {
        QString data, hora, forma_pagamento;
        int id_colaborador, id_forma_pagamento, id_venda;
        double valor_total;

        // recupera informações dos campso do formulário
        data = QDate::currentDate().toString("dd/MM/yyyy");
        hora = QTime::currentTime().toString("hh:mm:ss");
        valor_total = calcula_total_tableWidget(ui->tableWidget_itens_venda, 4);
        id_forma_pagamento = ui->comboBox_forma_pagamento->currentData().toInt();
        id_colaborador = global_variables::colaboradorLogado.getId();

        forma_pagamento = ui->comboBox_forma_pagamento->currentText();

        ColaboradorController colaborador_controller;
        FormaPagamentoController forma_pagamento_controller;
        VendaController venda_controller;

        // cria o objeto venda
        Venda venda;
        venda.setData(data);
        venda.setHora(hora);
        venda.setValorTotal(valor_total);
        venda.setFormaPagamento(forma_pagamento_controller.buscaPorId(id_forma_pagamento));
        venda.setColaborador(colaborador_controller.buscaPorId(id_colaborador));

        // insere a venda na tabela
        id_venda = venda_controller.insere(venda);
        venda.setId(id_venda);

        ItemVendaController item_venda_controller;
        ProdutoController produto_controller;
        Produto produto;
        ItemVenda item_venda;

        // cria uma lista de itens da venda
        int quantidade_itens = ui->tableWidget_itens_venda->rowCount();

        for (int i = 0; i < quantidade_itens; i++) {

            produto = produto_controller.buscaPorId(ui->tableWidget_itens_venda->item(i, 0)->text().toInt());

            item_venda.setQuantidade(ui->tableWidget_itens_venda->item(i, 3)->text().toInt());
            item_venda.setValorVenda(ui->tableWidget_itens_venda->item(i, 2)->text().replace(",", ".").toDouble());
            item_venda.setVenda(venda);
            item_venda.setProduto(produto);
            item_venda_controller.insere(item_venda);
        }
        QString msg = "Venda Finalizada!\n\n";
        msg += "Id da venda: " + QString::number(id_venda) + "\n\n";
        msg += "Valor total : R$ " + global_functions::formata_double(valor_total) + "\n\n";
        msg += "Forma de pagamento: " + forma_pagamento;

        QMessageBox::information(this, "", msg);

    } else
        QMessageBox::warning(this, "", "Lista vazia.");

    global_functions::limpa_table_widget(ui->tableWidget_itens_venda);
    limpa_formulario_venda();
    ui->label_total_venda->setText("R$ 0,00");
}
