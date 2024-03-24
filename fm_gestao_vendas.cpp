#include "fm_gestao_vendas.h"
#include "Colaborador.h"
#include "ColaboradorController.h"
#include "FormaPagamento.h"
#include "FormaPagamentoController.h"
#include "ItemVenda.h"
#include "ItemVendaController.h"
#include "Produto.h"
#include "ProdutoController.h"
#include "Venda.h"
#include "VendaController.h"
#include "global_functions.h"
#include "ui_fm_gestao_vendas.h"
#include <QPrinter>
#include <QPainter>
#include <QDir>
#include <QMessageBox>
#include <QDesktopServices>

fm_gestao_vendas::fm_gestao_vendas(QWidget *parent) : QDialog(parent), ui(new Ui::fm_gestao_vendas)
{
    ui->setupUi(this);

    inicializa_fm_gestao_vendas();
}

fm_gestao_vendas::~fm_gestao_vendas()
{
    delete ui;
}

/* ***********************************************************************************
 *
 * MINHAS FUNÇÕES LOCAIS
 *
 * ********************************************************************************* */

void fm_gestao_vendas::inicializa_fm_gestao_vendas()
{
    QDate df, di;
    df = QDate::currentDate();
    di.setDate(df.year(), df.month(), 1);

    data_final = df.toString("dd/MM/yyyy");
    data_inicial = di.toString("dd/MM/yyyy");

    ui->dateEdit_inicial->setDate(di);
    ui->dateEdit_final->setDate(df);

    QStringList cabecalho1 = {"ID", "Data", "Hora", "Colaborador", "Valor", "Forma pagamento"};
    global_functions::formata_table_widget(ui->tableWidget_vendas, cabecalho1);

    QStringList cabecalho2 = {"Produto", "Qtde", "Valor", "Total"};
    global_functions::formata_table_widget(ui->tableWidget_itens_venda, cabecalho2);

    QVector<Venda> listaVendas;
    VendaController venda_controller;
    listaVendas = venda_controller.buscaTodasPeriodo(data_inicial, data_final);

    popula_table_widget_vendas(listaVendas);
}

void fm_gestao_vendas::popula_table_widget_vendas(QVector<Venda> listaVendas)
{
    global_functions::limpa_table_widget(ui->tableWidget_vendas);

    int contador = 0;

    for (Venda venda : listaVendas) {
        ui->tableWidget_vendas->insertRow(contador);
        ui->tableWidget_vendas->setItem(contador, 0, new QTableWidgetItem(QString::number(venda.getId())));
        ui->tableWidget_vendas->setItem(contador, 1, new QTableWidgetItem(venda.getData()));
        ui->tableWidget_vendas->setItem(contador, 2, new QTableWidgetItem(venda.getHora()));
        ui->tableWidget_vendas->setItem(contador, 3, new QTableWidgetItem(venda.getColaborador().getNome()));
        ui->tableWidget_vendas->setItem(contador, 4, new QTableWidgetItem(global_functions::formata_double(venda.getValorTotal())));
        ui->tableWidget_vendas->setItem(contador, 5, new QTableWidgetItem(venda.getFormaPagamento().getDescricao()));
        ui->tableWidget_vendas->setRowHeight(contador, 20);
        contador++;
    }
}

void fm_gestao_vendas::popula_table_widget_itens_venda(QVector<ItemVenda> listaItensVenda)
{
    global_functions::limpa_table_widget(ui->tableWidget_itens_venda);

    int contador = 0;
    double total;
    Produto produto;
    ProdutoController produto_controller;

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

/* ***********************************************************************************
 *
 * SLOTS
 *
 * ********************************************************************************* */

void fm_gestao_vendas::on_pushButton_listar_todos_clicked()
{
    QVector<Venda> listaVendas;
    VendaController venda_controller;

    listaVendas = venda_controller.buscaTodasPeriodo(data_inicial, data_final);

    popula_table_widget_vendas(listaVendas);
}

void fm_gestao_vendas::on_pushButton_fechar_clicked()
{
    close();
}

void fm_gestao_vendas::on_tableWidget_vendas_itemSelectionChanged()
{
    global_functions::limpa_table_widget(ui->tableWidget_itens_venda);

    int row, id_venda;

    row = ui->tableWidget_vendas->currentRow();
    id_venda = ui->tableWidget_vendas->item(row, 0)->text().toInt();

    QVector<ItemVenda> listaItensVenda;
    ItemVendaController item_venda_controller;

    listaItensVenda = item_venda_controller.buscaPorIdVenda(id_venda);

    popula_table_widget_itens_venda(listaItensVenda);
}

void fm_gestao_vendas::on_pushButton_filtrar_clicked() {
    data_inicial = ui->dateEdit_inicial->text();
    data_final = ui->dateEdit_final->text();

    QVector<Venda> listaVendas;
    VendaController venda_controller;

    listaVendas = venda_controller.buscaTodasPeriodo(data_inicial, data_final);

    popula_table_widget_vendas(listaVendas);
}

void fm_gestao_vendas::on_pushButton_pdf_clicked()
{

    // montagem do nome do arquivo
    QString data_venda, id_venda, nome_do_arquivo, caminho;
    QStringList aux;
    int row;

    row = ui->tableWidget_vendas->currentRow();
    id_venda = ui->tableWidget_vendas->item(row, 0)->text();
    data_venda = ui->tableWidget_vendas->item(row, 1)->text();
    aux = data_venda.split("/");
    data_venda = aux[2] + aux[1] + aux[0];
    caminho = QDir::currentPath();
    nome_do_arquivo = caminho + "/" + data_venda + "_venda_" + id_venda + ".pdf";

    // QPrinter
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(nome_do_arquivo);

    // Conteudo do arquivo
    QPainter painter;
    if(!painter.begin(&printer)){
        qDebug() << "Erro ao abrir o arquivo.";
        return;
    }
    painter.drawPixmap(10, 10, QPixmap(":/icon/images/Barbara1.png"));
    int linha, salto;
    linha = 250;
    salto = 20;
    painter.drawText(25, 200, "ID: " + id_venda);
    painter.drawText(25, 200, "ID: " + ui->tableWidget_vendas->item(row, 1)->text());

    // o for está crachando o sistema
    // for(int i = 0; i < ui->tableWidget_itens_venda->rowCount(); i++){
    //     painter.drawText(25, linha, ui->tableWidget_vendas->item(i, 0)->text());
    //     painter.drawText(75, linha, ui->tableWidget_vendas->item(i, 1)->text());
    //     painter.drawText(125, linha, ui->tableWidget_vendas->item(i, 2)->text());
    //     painter.drawText(175, linha, ui->tableWidget_vendas->item(i, 3)->text());
    //     painter.drawText(225, linha, ui->tableWidget_vendas->item(i, 4)->text());
    //     painter.drawText(275, linha, ui->tableWidget_vendas->item(i, 5)->text());
    //     linha += salto;
    // }
    printer.newPage();
    painter.drawText(30, 10, "Pagina 2 - FCM");
    painter.end();
    QDesktopServices::openUrl(QUrl("file:///" + nome_do_arquivo));
    QMessageBox::information(this, "", "Arquivo gerado com sucesso!");
}
