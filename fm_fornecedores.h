#ifndef FM_FORNECEDORES_H
#define FM_FORNECEDORES_H

#include <QDialog>
#include "Fornecedor.h"
#include <QTableWidget>

namespace Ui {
class fm_fornecedores;
}

class fm_fornecedores : public QDialog
{
    Q_OBJECT

public:
    explicit fm_fornecedores(QWidget *parent = nullptr);
    ~fm_fornecedores();

    // MY METHODS
    void inicializa_fm_fornecedores();
    void atualiza_table_widget();
    void popula_table_widget(QVector<Fornecedor> listaFornecedores);
    void limpa_formulario();

private slots:
    void on_tableWidget_fornecedores_itemSelectionChanged();

    void on_pushButton_limpar_clicked();

    void on_pushButton_fechar_clicked();

    void on_pushButton_salvar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_pushButton_pesquisar_clicked();

private:
    Ui::fm_fornecedores *ui;
};

#endif // FM_FORNECEDORES_H
