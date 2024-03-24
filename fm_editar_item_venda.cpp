#include "fm_editar_item_venda.h"
#include "fm_nova_venda.h"
#include "ui_fm_editar_item_venda.h"

fm_editar_item_venda::fm_editar_item_venda(QWidget *parent) : QDialog(parent), ui(new Ui::fm_editar_item_venda)
{
    ui->setupUi(this);

    inicializa_fm_editar_item_venda();
}

fm_editar_item_venda::~fm_editar_item_venda()
{
    delete ui;
}

/* ***********************************************************************************
 *
 * MINHAS FUNÇÕES LOCAIS
 *
 * ********************************************************************************* */
void fm_editar_item_venda::inicializa_fm_editar_item_venda()
{
    ui->lineEdit_descricao->setText(fm_nova_venda::descricao_edicao_itens_venda);
    ui->lineEdit_valor_venda->setText(fm_nova_venda::valor_venda_edicao_itens_venda);
    ui->lineEdit_quantidade->setText(fm_nova_venda::quantidade_edicao_itens_venda);
}

/* ***********************************************************************************
 *
 * SLOTS
 *
 * ********************************************************************************* */

void fm_editar_item_venda::on_pushButton_salvar_clicked()
{
    fm_nova_venda::valor_venda_edicao_itens_venda = ui->lineEdit_valor_venda->text().replace(",", ".");
    fm_nova_venda::quantidade_edicao_itens_venda = ui->lineEdit_quantidade->text();
    close();
}

void fm_editar_item_venda::on_pushButton_cancelar_clicked()
{
    close();
}
