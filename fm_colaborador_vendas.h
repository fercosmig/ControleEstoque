#ifndef FM_COLABORADOR_VENDAS_H
#define FM_COLABORADOR_VENDAS_H

#include <QDialog>
#include "ItemVenda.h"
#include "Venda.h"

namespace Ui {
class fm_colaborador_vendas;
}

class fm_colaborador_vendas : public QDialog
{
    Q_OBJECT

public:
    explicit fm_colaborador_vendas(QWidget *parent = nullptr, int id = 0);
    ~fm_colaborador_vendas();

    // MINHAS VARIÁVEIS PARA O FORMULARIO
    int id_colaborador;
    Colaborador colaborador;
    QString data_inicial;
    QString data_final;

    // MINHAS FUNÇÕES LOCAIS
    void inicializa_fm_colaborador_vendas();
    void popula_table_widget_vendas(QVector<Venda> listaVendas);
    void popula_table_widget_itens_venda(QVector<ItemVenda> listaItensVenda);

private slots:
    void on_pushButton_fechar_clicked();

    void on_tableWidget_vendas_itemSelectionChanged();

    void on_pushButton_filtrar_clicked();

private:
    Ui::fm_colaborador_vendas *ui;
};

#endif // FM_COLABORADOR_VENDAS_H
