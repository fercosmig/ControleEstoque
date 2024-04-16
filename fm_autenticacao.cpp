#include "fm_autenticacao.h"
#include "ui_fm_autenticacao.h"

#include "global.h"
#include <QMessageBox>
#include "ColaboradorController.h"

fm_autenticacao::fm_autenticacao(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_autenticacao)
{
    ui->setupUi(this);

    fm_autenticacao::inicializa_fm_autenticacao();
}

fm_autenticacao::~fm_autenticacao()
{
    delete ui;
}

/* ***** ***** ***** ***** *****
 *  MY METHODS
 * ***** ***** ***** ***** *****/

void fm_autenticacao::inicializa_fm_autenticacao()
{
    // ui->lineEdit_email->setText("fercosmig@gmail.com");
    // ui->lineEdit_senha->setText("123");
}

/* ***** ***** ***** ***** *****
 *  SLOTS
 * ***** ***** ***** ***** *****/

void fm_autenticacao::on_pushButton_cancelar_clicked()
{
    close();
}

void fm_autenticacao::on_pushButton_autenticar_clicked()
{
    QString email, senha;
    Colaborador colaborador;
    ColaboradorController colaborador_controller;

    email = ui->lineEdit_email->text().trimmed();
    senha = ui->lineEdit_senha->text().trimmed();

    if (global::minCharacters(email, 7) && global::minCharacters(senha, 3) ) {

        colaborador.setId(0);
        colaborador.setEmail(email);
        colaborador.setSenha(senha);

        colaborador = colaborador_controller.autenticar(colaborador);

        if (colaborador.getId() > 0) {
            global::colaboradorLogado = colaborador;
            global::isLogged = true;
            close();
        } else
            QMessageBox::warning(this, "", "E-mail ou Senha inválidos");
    } else
        QMessageBox::warning(this, "", "E-mail: mínimo 7 caracteres.\n\nSenha: minimo 3 caracteres.");
}
