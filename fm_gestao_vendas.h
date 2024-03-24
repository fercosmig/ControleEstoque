#ifndef FM_GESTAO_VENDAS_H
#define FM_GESTAO_VENDAS_H

#include <QDialog>
#include "ItemVenda.h"
#include "Venda.h"

namespace Ui {
class fm_gestao_vendas;
}

class fm_gestao_vendas : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestao_vendas(QWidget *parent = nullptr);
    ~fm_gestao_vendas();

    // MINHAS VARIAVEIS
    QString data_inicial;
    QString data_final;

    // MINHAS FUNÇÕES LOCAIS
    void inicializa_fm_gestao_vendas();
    void popula_table_widget_vendas(QVector<Venda> listaVendas);
    void popula_table_widget_itens_venda(QVector<ItemVenda> listaItensVenda);

private slots:
    void on_pushButton_filtrar_clicked();

    void on_pushButton_listar_todos_clicked();

    void on_pushButton_pdf_clicked();

    void on_pushButton_fechar_clicked();

    void on_tableWidget_vendas_itemSelectionChanged();

private:
    Ui::fm_gestao_vendas *ui;
};

#endif // FM_GESTAO_VENDAS_H
