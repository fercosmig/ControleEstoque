#ifndef FM_VENDAS_NOVA_H
#define FM_VENDAS_NOVA_H

#include <QDialog>
#include "Produto.h"
#include <QTableWidget>

namespace Ui {
class fm_vendas_nova;
}

class fm_vendas_nova : public QDialog
{
    Q_OBJECT

public:
    explicit fm_vendas_nova(QWidget *parent = nullptr);
    ~fm_vendas_nova();

    // MY METHODS
    void inicializa_fm_vendas_nova();
    void configura_table_widget();
    void adiciona_produto_table_widget(int quantidade, Produto produto);
    void limpa_formulario();
    double calcula_total(QTableWidget *table_widget, int column);
    void atualiza_total();
    void carrega_combo_forma_pagamento();
    void habilita_edicao_item_venda(bool editar);

private slots:
    void on_pushButton_fechar_clicked();

    void on_lineEdit_id_produto_returnPressed();

    void on_tableWidget_itens_venda_itemSelectionChanged();

    void on_pushButton_editar_clicked();

    void on_pushButton_excluir_clicked();

    void on_pushButton_finalizar_clicked();

    void on_pushButton_salvar_clicked();

    void on_pushButton_cancelar_clicked();

private:
    Ui::fm_vendas_nova *ui;
};

#endif // FM_VENDAS_NOVA_H
