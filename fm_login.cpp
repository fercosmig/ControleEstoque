#include "fm_login.h"
#include <QMessageBox>
#include "ColaboradorController.h"
#include "fm_principal.h"
#include "global_functions.h"
#include "global_variables.h"
#include "ui_fm_login.h"

fm_login::fm_login(QWidget *parent) : QDialog(parent), ui(new Ui::fm_login)
{
    ui->setupUi(this);

    // GAMBIARRA
    ui->lineEdit_username_login->setText("fercosmig");
    ui->lineEdit_senha_login->setText("123");
}

fm_login::~fm_login()
{
    delete ui;
}

/* ***********************************************************************************
 *
 * MINHAS FUNÇÕES LOCAIS
 *
 * ********************************************************************************* */

void fm_login::limpa_campos_fm_login()
{
    ui->lineEdit_username_login->clear();
    ui->lineEdit_senha_login->clear();
    ui->lineEdit_username_login->setFocus();
}

/* ***********************************************************************************
 *
 * SLOTS
 *
 * ********************************************************************************* */

void fm_login::on_pushButton_fechar_clicked()
{
    global_variables::isLogged = false;
    close();
}

void fm_login::on_pushButton_login_clicked()
{
    QString username, senha;
    int id_colaborador;

    username = ui->lineEdit_username_login->text().trimmed();
    senha = ui->lineEdit_senha_login->text().trimmed();
    
    if (global_functions::minCaracter(username, 3) && global_functions::minCaracter(senha, 3)) {

        ColaboradorController colaborador_controller;
        id_colaborador = colaborador_controller.autentica(username, senha);

        if (id_colaborador > 0) {

            global_variables::isLogged = true;
            global_variables::colaboradorLogado = colaborador_controller.buscaPorId(id_colaborador);
            close();

        } else {

            QMessageBox::warning(this, "", "Dados inválidos!");
            limpa_campos_fm_login();
        }

    } else {
        QMessageBox::warning(this, "", "Mínimo 3 caracteres!");
        limpa_campos_fm_login();
    }
}
