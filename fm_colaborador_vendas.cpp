#include "fm_colaborador_vendas.h"
#include <QDebug>
#include "Colaborador.h"
#include "ColaboradorController.h"
#include "ItemVenda.h"
#include "ItemVendaController.h"
#include "VendaController.h"
#include "global_functions.h"
#include "ui_fm_colaborador_vendas.h"

fm_colaborador_vendas::fm_colaborador_vendas(QWidget *parent, int id) : QDialog(parent), ui(new Ui::fm_colaborador_vendas)
{
    ui->setupUi(this);

    id_colaborador = id;
    inicializa_fm_colaborador_vendas();
}

fm_colaborador_vendas::~fm_colaborador_vendas()
{
    delete ui;
}

/* ***********************************************************************************
 *
 * MINHAS FUNÇÕES LOCAIS
 *
 * ********************************************************************************* */

void fm_colaborador_vendas::popula_table_widget_itens_venda(QVector<ItemVenda> listaItensVenda)
{
    ui->tableWidget_itens_venda->setRowCount(0);

    int contador = 0;
    double total;

    for (ItemVenda item_venda : listaItensVenda) {
        ui->tableWidget_itens_venda->insertRow(contador);
        ui->tableWidget_itens_venda->setItem(contador, 0, new QTableWidgetItem(item_venda.getProduto().getDescricao()));
        ui->tableWidget_itens_venda->setItem(contador, 1, new QTableWidgetItem(QString::number(item_venda.getQuantidade())));
        ui->tableWidget_itens_venda->setItem(contador, 2, new QTableWidgetItem(global_functions::formata_double(item_venda.getValorVenda())));

        total = item_venda.getQuantidade() * item_venda.getValorVenda();

        ui->tableWidget_itens_venda->setItem(contador, 3, new QTableWidgetItem(global_functions::formata_double(total)));
        ui->tableWidget_itens_venda->setRowHeight(contador, 20);
        contador++;
    }
}

void fm_colaborador_vendas::popula_table_widget_vendas(QVector<Venda> listaVendas)
{
    ui->tableWidget_vendas->setRowCount(0);

    int contador = 0;

    for (Venda venda : listaVendas) {
        ui->tableWidget_vendas->insertRow(contador);
        ui->tableWidget_vendas->setItem(contador, 0, new QTableWidgetItem(QString::number(venda.getId())));
        ui->tableWidget_vendas->setItem(contador, 1, new QTableWidgetItem(venda.getData()));
        ui->tableWidget_vendas->setItem(contador, 2, new QTableWidgetItem(venda.getHora()));
        ui->tableWidget_vendas->setItem(contador, 3, new QTableWidgetItem(global_functions::formata_double(venda.getValorTotal())));
        ui->tableWidget_vendas->setItem(contador, 4, new QTableWidgetItem(venda.getFormaPagamento().getDescricao()));
        ui->tableWidget_vendas->setRowHeight(contador, 20);
        contador++;
    }
}

void fm_colaborador_vendas::inicializa_fm_colaborador_vendas()
{
    {
        // configura data inicial e final do campo pesquisa
        QDate df, di;
        df = QDate::currentDate();
        di.setDate(df.year(), df.month(),1);

        data_final = df.toString("dd/MM/yyyy");
        data_inicial = di.toString("dd/MM/yyyy");

        ui->dateEdit_inicial->setDate(di);
        ui->dateEdit_final->setDate(df);

        // configura o colaborador escolhido
        ui->lineEdit_id_colaborador->setText(QString::number(id_colaborador));
        ColaboradorController colaborador_controller;
        colaborador = colaborador_controller.buscaPorId(id_colaborador);
        ui->lineEdit_colaborador->setText(colaborador.getNome());

        // formata tableWidget de vendas
        QStringList cabecalho1 = {"ID", "Data", "Hora", "Valor", "Forma pagamento"};
        global_functions::formata_table_widget(ui->tableWidget_vendas, cabecalho1);

        // formata tableWidget de itens das vendas
        QStringList cabecalho2 = {"Produto", "Qtde", "Valor", "Total"};
        global_functions::formata_table_widget(ui->tableWidget_itens_venda, cabecalho2);

        // popula tableWidget de vendas
        QVector<Venda> listaVendas;
        VendaController venda_controller;
        listaVendas = venda_controller.buscaPorIdColaboradorPeriodo(colaborador.getId(), data_inicial, data_final);
        popula_table_widget_vendas(listaVendas);
    }
}
/* ***********************************************************************************
 *
 * SLOTS
 *
 * ********************************************************************************* */

void fm_colaborador_vendas::on_pushButton_fechar_clicked()
{
    close();
}

void fm_colaborador_vendas::on_tableWidget_vendas_itemSelectionChanged()
{
    ui->tableWidget_itens_venda->setRowCount(0);
    int row, id;

    row = ui->tableWidget_vendas->currentRow();
    id = ui->tableWidget_vendas->item(row, 0)->text().toInt();

    QVector<ItemVenda> itensVenda;
    ItemVendaController item_venda_controller;

    itensVenda = item_venda_controller.buscaPorIdVenda(id);

    popula_table_widget_itens_venda(itensVenda);
}

void fm_colaborador_vendas::on_pushButton_filtrar_clicked()
{
    QString data_inicial, data_final;

    data_inicial = ui->dateEdit_inicial->text();
    data_final = ui->dateEdit_final->text();

    QVector<Venda> listaVendas;
    VendaController venda_controller;

    listaVendas = venda_controller.buscaPorIdColaboradorPeriodo(id_colaborador, data_inicial, data_final);

    popula_table_widget_vendas(listaVendas);
}
