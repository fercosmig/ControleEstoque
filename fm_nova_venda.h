#ifndef FM_NOVA_VENDA_H
#define FM_NOVA_VENDA_H

#include <QDialog>
#include <QTableWidget>
#include "ItemVenda.h"

namespace Ui {
class fm_nova_venda;
}

class fm_nova_venda : public QDialog
{
    Q_OBJECT

public:
    explicit fm_nova_venda(QWidget *parent = nullptr);
    ~fm_nova_venda();

    // MINHAS VARIAVEIS PARA O FORMULÁRIO
    QVector<ItemVenda> lista_itens_venda;

    // MINHAS VARIAVEIS GLOBAIS PARA EDIÇÃO DE ITEM DE VENDA
    static QString descricao_edicao_itens_venda, valor_venda_edicao_itens_venda, quantidade_edicao_itens_venda;

    // MINHAS FUNÇÕES PARA O FORMULÁRIO
    void adiciona_item_tableWidget_itens_venda(ItemVenda item_venda);
    void limpa_formulario_venda();
    double calcula_total_tableWidget(QTableWidget *tw, int coluna);
    void popula_combobox_forma_pagamento();
    void inicializa_fm_nova_venda();

private slots:
    void on_pushButton_fechar_clicked();

    void on_lineEdit_id_produto_returnPressed();

    void on_tableWidget_itens_venda_itemSelectionChanged();

    void on_pushButton_excluir_item_clicked();

    void on_pushButton_editar_item_clicked();

    void on_pushButton_finalizar_venda_clicked();

private:
    Ui::fm_nova_venda *ui;
};

#endif // FM_NOVA_VENDA_H
