#ifndef FM_EDITAR_ITEM_VENDA_H
#define FM_EDITAR_ITEM_VENDA_H

#include <QDialog>

namespace Ui {
class fm_editar_item_venda;
}

class fm_editar_item_venda : public QDialog
{
    Q_OBJECT

public:
    explicit fm_editar_item_venda(QWidget *parent = nullptr);
    ~fm_editar_item_venda();

    // MINHAS FUNÇÕES LOCAIS
    void inicializa_fm_editar_item_venda();

private slots:
    void on_pushButton_salvar_clicked();

    void on_pushButton_cancelar_clicked();

private:
    Ui::fm_editar_item_venda *ui;
};

#endif // FM_EDITAR_ITEM_VENDA_H
