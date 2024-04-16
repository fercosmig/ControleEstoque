#include "fm_vendas.h"
#include "ui_fm_vendas.h"

#include <QMessageBox>
#include "global.h"
#include "VendaController.h"
#include "ItemVendaController.h"

fm_vendas::fm_vendas(QWidget *parent) : QDialog(parent), ui(new Ui::fm_vendas)
{
    ui->setupUi(this);

    fm_vendas::inicializa_fm_vendas();
}

fm_vendas::~fm_vendas()
{
    delete ui;
}

/* ***** ***** ***** ***** *****
 *  MY METHODS
 * ***** ***** ***** ***** *****/

void fm_vendas::inicializa_fm_vendas()
{
    fm_vendas::configurar_datas();
    fm_vendas::atualiza_table_widget_vendas();
}

void fm_vendas::configurar_datas()
{
    int dias;
    QDate data_inicial, data_final;

    data_final = QDate::currentDate();

    dias = (data_final.day() - 1) * (-1);
    data_inicial = data_final.addDays(dias);

    ui->dateEdit_data_inicial->setDate(data_inicial);
    ui->dateEdit_data_final->setDate(data_final);
}

void fm_vendas::popula_table_widget_vendas(QVector<Venda> listaVendas)
{
    QStringList header;
    Venda venda;

    header = {"ID", "Data", "Hora", "Valor", "Forma Pagamento", "Vendedor"};
    global::formatTableWidget(ui->tableWidget_vendas, header);

    for (int i = 0; i < listaVendas.size(); ++i) {
        venda = listaVendas[i];
        ui->tableWidget_vendas->insertRow(i);
        ui->tableWidget_vendas->setItem(i, 0, new QTableWidgetItem(QString::number(venda.getId())));
        ui->tableWidget_vendas->setItem(i, 1, new QTableWidgetItem(venda.getData()));
        ui->tableWidget_vendas->setItem(i, 2, new QTableWidgetItem(venda.getHora()));
        ui->tableWidget_vendas->setItem(i, 3, new QTableWidgetItem(global::formatDoubleToString(venda.getValor())));
        ui->tableWidget_vendas->setItem(i, 4, new QTableWidgetItem(venda.getFormaPagamento().getDescricao()));
        ui->tableWidget_vendas->setItem(i, 5, new QTableWidgetItem(venda.getColaborador().getNome()));
        ui->tableWidget_vendas->setRowHeight(i, 20);
    }
}

void fm_vendas::atualiza_table_widget_vendas()
{
    QStringList header;
    QVector<Venda> listaVendas;
    VendaController venda_controller;
    QString data_inicial, data_final;

    data_inicial = ui->dateEdit_data_inicial->text();
    data_final = ui->dateEdit_data_final->text();

    listaVendas = venda_controller.buscaPorPeriodo(data_inicial, data_final);
    fm_vendas::popula_table_widget_vendas(listaVendas);

    header = {"ID", "Quantidade", "Valor", "Produto", "Sub-total"};
    global::formatTableWidget(ui->tableWidget_itens_venda, header);
}

void fm_vendas::popula_table_widget_itens_venda(QVector<ItemVenda> listaItensVenda)
{
    QStringList header;
    ItemVenda item_venda;
    double subtotal;

    header = {"ID", "Quantidade", "Valor", "Produto", "Sub-total"};
    global::formatTableWidget(ui->tableWidget_itens_venda, header);

    for (int i = 0; i < listaItensVenda.size(); ++i) {
        item_venda = listaItensVenda[i];
        ui->tableWidget_itens_venda->insertRow(i);
        ui->tableWidget_itens_venda->setItem(i, 0, new QTableWidgetItem(QString::number(item_venda.getId())));
        ui->tableWidget_itens_venda->setItem(i, 1, new QTableWidgetItem(global::formatDoubleToString(item_venda.getQuantidade())));
        ui->tableWidget_itens_venda->setItem(i, 2, new QTableWidgetItem(global::formatDoubleToString(item_venda.getValor())));
        ui->tableWidget_itens_venda->setItem(i, 3, new QTableWidgetItem(item_venda.getProduto().getDescricao()));
        subtotal = item_venda.getQuantidade() * item_venda.getValor();
        ui->tableWidget_itens_venda->setItem(i, 4, new QTableWidgetItem(global::formatDoubleToString(subtotal)));
        ui->tableWidget_itens_venda->setRowHeight(i, 20);
    }
}

void fm_vendas::atualiza_table_widget_itens_venda(int id_venda)
{
    QVector<ItemVenda> listaItensVenda;
    ItemVendaController item_venda_controller;

    listaItensVenda = item_venda_controller.buscaPorIdVenda(id_venda);
    fm_vendas::popula_table_widget_itens_venda(listaItensVenda);
}
/* ***** ***** ***** ***** *****
 *  SLOTS
 * ***** ***** ***** ***** *****/

void fm_vendas::on_pushButton_fechar_clicked()
{
    close();
}

void fm_vendas::on_pushButton_filtrar_clicked()
{
    fm_vendas::atualiza_table_widget_vendas();
}

void fm_vendas::on_tableWidget_vendas_itemSelectionChanged()
{
    int row, id_venda;

    row = ui->tableWidget_vendas->currentRow();

    id_venda = ui->tableWidget_vendas->item(row, 0)->text().toInt();
    fm_vendas::atualiza_table_widget_itens_venda(id_venda);
}
