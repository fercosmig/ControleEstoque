#ifndef FM_PRODUTOS_H
#define FM_PRODUTOS_H

#include <QDialog>
#include "Produto.h"

namespace Ui {
class fm_produtos;
}

class fm_produtos : public QDialog
{
    Q_OBJECT

public:
    explicit fm_produtos(QWidget *parent = nullptr);
    ~fm_produtos();

    // MY METHODS
    void inicializa_fm_produtos();
    void atualiza_table_widget();
    void popula_table_widget(QVector<Produto> listaProdutos);
    void carrega_combo_fornecedores();
    void limpa_formulario();

private slots:
    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_tableWidget_produtos_itemSelectionChanged();

    void on_pushButton_salvar_clicked();

    void on_pushButton_limpar_clicked();

    void on_pushButton_fechar_clicked();

private:
    Ui::fm_produtos *ui;
};

#endif // FM_PRODUTOS_H
