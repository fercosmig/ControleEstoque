#ifndef FM_VENDAS_H
#define FM_VENDAS_H

#include <QDialog>
#include "Venda.h"
#include "ItemVenda.h"

namespace Ui {
class fm_vendas;
}

class fm_vendas : public QDialog
{
    Q_OBJECT

public:
    explicit fm_vendas(QWidget *parent = nullptr);
    ~fm_vendas();

    // MY METHODS
    void inicializa_fm_vendas();
    void configurar_datas();
    void popula_table_widget_vendas(QVector<Venda> listaVendas);
    void atualiza_table_widget_vendas();
    void popula_table_widget_itens_venda(QVector<ItemVenda> listaItensVenda);
    void atualiza_table_widget_itens_venda(int id_venda);

private slots:
    void on_pushButton_fechar_clicked();

    void on_pushButton_filtrar_clicked();

    void on_tableWidget_vendas_itemSelectionChanged();

private:
    Ui::fm_vendas *ui;
};

#endif // FM_VENDAS_H
