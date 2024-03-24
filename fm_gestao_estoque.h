#ifndef FM_GESTAO_ESTOQUE_H
#define FM_GESTAO_ESTOQUE_H

#include <QDialog>
#include "Produto.h"

namespace Ui {
class fm_gestao_estoque;
}

class fm_gestao_estoque : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestao_estoque(QWidget *parent = nullptr);
    ~fm_gestao_estoque();

    // MINHAS FUNÇÕES PARA O FORMULARIO
    void limpa_formulario_cadastro_produto();
    void limpa_formulario_edicao_produto();
    void popula_table_widget_produtos(QVector<Produto> lista_produtos);
    void inicializa_fm_gestao_estoque();
    void popula_combobox_fornecedores();

private slots:
    void on_pushButton_cancelar_produto_clicked();

    void on_pushButton_salvar_produto_clicked();

    void on_pushButton_fechar_clicked();

    void on_tabWidget_produtos_currentChanged(int index);

    void on_tableWidget_produtos_itemSelectionChanged();

    void on_pushButton_cancelar_produto_Edit_clicked();

    void on_pushButton_salvar_produto_edit_clicked();

    void on_pushButton_excluir_produto_clicked();

    void on_pushButton_pesquisar_produto_clicked();

private:
    Ui::fm_gestao_estoque *ui;
};

#endif // FM_GESTAO_ESTOQUE_H
