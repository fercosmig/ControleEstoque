#ifndef FM_GRUPOS_H
#define FM_GRUPOS_H

#include <QDialog>
#include "Grupo.h"

namespace Ui {
class fm_grupos;
}

class fm_grupos : public QDialog
{
    Q_OBJECT

public:
    explicit fm_grupos(QWidget *parent = nullptr);
    ~fm_grupos();

    // MY METHODS
    void inicializa_fm_grupos();
    void carrega_combo_siglas();
    void atualiza_table_widget();
    void popula_table_widget(QVector<Grupo> listaGrupos);
    void limpa_formulario();

private slots:
    void on_pushButton_fechar_clicked();

    void on_pushButton_limpar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_pushButton_pesquisar_clicked();

    void on_pushButton_salvar_clicked();

    void on_tableWidget_grupos_itemSelectionChanged();

private:
    Ui::fm_grupos *ui;
};

#endif // FM_GRUPOS_H
