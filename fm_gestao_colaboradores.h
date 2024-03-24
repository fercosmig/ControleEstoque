#ifndef FM_GESTAO_COLABORADORES_H
#define FM_GESTAO_COLABORADORES_H

#include <QComboBox>
#include <QDialog>
#include <QVector>
#include <Colaborador.h>

namespace Ui {
class fm_gestao_colaboradores;
}

class fm_gestao_colaboradores : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestao_colaboradores(QWidget *parent = nullptr);
    ~fm_gestao_colaboradores();

    // MINHAS FUNÇÕES
    void limpa_formulario();
    void popula_combo_grupo(QComboBox *cb);
    void inicializa_fm_gestao_colaboradores();
    void popula_table_widget_colaboradores(QVector<Colaborador> lista_colaboradores);
    void limpa_formulario_edicao();
    void altera_formulario_cadastro_edicao(bool acao);

private slots:
    void on_pushButton_fechar_clicked();

    void on_pushButton_salvar_clicked();

    void on_pushButton_cancelar_clicked();

    void on_tableWidget_colaboradores_itemSelectionChanged();

    void on_pushButton_excluir_clicked();

    void on_pushButton_ver_vendas_clicked();

    void on_pushButton_pesquisar_clicked();

private:
    Ui::fm_gestao_colaboradores *ui;
};

#endif // FM_GESTAO_COLABORADORES_H
