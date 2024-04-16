#ifndef FM_COLABORADORES_H
#define FM_COLABORADORES_H

#include <QDialog>
#include "Colaborador.h"

namespace Ui {
class fm_colaboradores;
}

class fm_colaboradores : public QDialog
{
    Q_OBJECT

public:
    explicit fm_colaboradores(QWidget *parent = nullptr);
    ~fm_colaboradores();

    // MY METHODS
    void inicializa_fm_colaboradores();
    void carrega_combo_grupos();
    void atualiza_table_widget();
    void popula_table_widget(QVector<Colaborador> listaColaboradores);
    void limpa_formulario();

private slots:
    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_tableWidget_colaboradores_itemSelectionChanged();

    void on_pushButton_salvar_clicked();

    void on_pushButton_limpar_clicked();

    void on_pushButton_fechar_clicked();

private:
    Ui::fm_colaboradores *ui;
};

#endif // FM_COLABORADORES_H
