#ifndef FM_FORMA_PAGAMENTO_H
#define FM_FORMA_PAGAMENTO_H

#include <QDialog>
#include "FormaPagamento.h"

namespace Ui {
class fm_forma_pagamento;
}

class fm_forma_pagamento : public QDialog
{
    Q_OBJECT

public:
    explicit fm_forma_pagamento(QWidget *parent = nullptr);
    ~fm_forma_pagamento();

    // MY METHODS
    void inicializa_fm_forma_pagamento();
    void atualiza_table_widget();
    void popula_table_widget(QVector<FormaPagamento> ListaFormasPagamento);
    void limpa_formulario();

private slots:
    void on_pushButton_pesquisar_clicked();

    void on_pushButton_mostrar_todos_clicked();

    void on_tableWidget_forma_pagamento_itemSelectionChanged();

    void on_pushButton_salvar_clicked();

    void on_pushButton_limpar_clicked();

    void on_pushButton_fechar_clicked();

private:
    Ui::fm_forma_pagamento *ui;
};

#endif // FM_FORMA_PAGAMENTO_H
