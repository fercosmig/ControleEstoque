#ifndef FM_GESTAO_FORNECEDORES_H
#define FM_GESTAO_FORNECEDORES_H

#include <QDialog>
#include <QVector>
#include "Fornecedor.h"

namespace Ui {
class fm_gestao_fornecedores;
}

class fm_gestao_fornecedores : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestao_fornecedores(QWidget *parent = nullptr);
    ~fm_gestao_fornecedores();

    void limpa_formulario_fornecedor_novo();
    void limpa_formulario_fornecedor_edit();
    void limpa_formulario_fornecedor_pesquisa();
    void popula_tableWidget_fornecedores(QVector<Fornecedor> listaFornecedores);
    void inicializa_fm_gestao_fornecedores();

private slots:
    void on_pushButton_fechar_clicked();

    void on_pushButton_salvar_novo_clicked();

    void on_pushButton_limpar_formulario_novo_clicked();

    void on_pushButton_pesquisar_clicked();

    void on_tableWidget_fornecedores_itemSelectionChanged();

    void on_pushButton_cancelar_edit_clicked();

    void on_pushButton_excluir_edit_clicked();

    void on_pushButton_salvar_edit_clicked();

private:
    Ui::fm_gestao_fornecedores *ui;
};

#endif // FM_GESTAO_FORNECEDORES_H
