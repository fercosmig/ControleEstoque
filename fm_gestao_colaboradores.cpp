#include "fm_gestao_colaboradores.h"
#include <QMessageBox>
#include "Colaborador.h"
#include "ColaboradorController.h"
#include "Grupo.h"
#include "GrupoController.h"
#include "fm_colaborador_vendas.h"
#include "global_functions.h"
#include "ui_fm_gestao_colaboradores.h"

fm_gestao_colaboradores::fm_gestao_colaboradores(QWidget *parent) : QDialog(parent), ui(new Ui::fm_gestao_colaboradores)
{
    ui->setupUi(this);

    inicializa_fm_gestao_colaboradores();
}

fm_gestao_colaboradores::~fm_gestao_colaboradores()
{
    delete ui;
}

/* ***********************************************************************************
 *
 * MINHAS FUNÇÕES LOCAIS
 *
 * ********************************************************************************* */

void fm_gestao_colaboradores::popula_table_widget_colaboradores(QVector<Colaborador> listaColaboradores)
{
    ui->tableWidget_colaboradores->setRowCount(0);

    int contador = 0;

    for (Colaborador colaborador : listaColaboradores) {
        ui->tableWidget_colaboradores->insertRow(contador);
        ui->tableWidget_colaboradores->setItem(contador, 0, new QTableWidgetItem(QString::number(colaborador.getId())));
        ui->tableWidget_colaboradores->setItem(contador, 1, new QTableWidgetItem(colaborador.getNome()));
        ui->tableWidget_colaboradores->setItem(contador, 2, new QTableWidgetItem(colaborador.getNomeUsuario()));
        ui->tableWidget_colaboradores->setItem(contador, 3, new QTableWidgetItem(colaborador.getTelefone()));
        ui->tableWidget_colaboradores->setItem(contador, 4, new QTableWidgetItem(colaborador.getGrupo().getDescricao()));
        ui->tableWidget_colaboradores->setRowHeight(contador, 20);

        contador++;
    }
}

void fm_gestao_colaboradores::inicializa_fm_gestao_colaboradores()
{
    popula_combo_grupo(ui->comboBox_grupo);

    QStringList cabecalho = {"ID", "Nome", "Username", "Telefone", "Grupo"};
    global_functions::formata_table_widget(ui->tableWidget_colaboradores, cabecalho);
}

void fm_gestao_colaboradores::popula_combo_grupo(QComboBox *cb)
{
    cb->clear();

    QVector<Grupo> listaGrupos;
    GrupoController grupo_controller;

    listaGrupos = grupo_controller.buscaTodos();

    for (Grupo grupo : listaGrupos) {
        cb->addItem(grupo.getDescricao(), grupo.getId());
    }
}

void fm_gestao_colaboradores::limpa_formulario()
{
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->lineEdit_nome_de_usuario->clear();
    ui->lineEdit_senha->clear();
    ui->lineEdit_telefone->clear();
    ui->comboBox_grupo->setCurrentIndex(0);
    ui->lineEdit_nome->setFocus();
}

/* ***********************************************************************************
 *
 * SLOTS
 *
 * ********************************************************************************* */

void fm_gestao_colaboradores::on_pushButton_fechar_clicked()
{
    close();
}

void fm_gestao_colaboradores::on_pushButton_salvar_clicked()
{
    QString nome, username, senha, telefone, id_grupo;
    Colaborador colaborador;
    ColaboradorController colaborador_controller;
    GrupoController grupo_controller;

    nome = ui->lineEdit_nome->text();
    username = ui->lineEdit_nome_de_usuario->text();
    senha = ui->lineEdit_senha->text();
    telefone = ui->lineEdit_telefone->text();
    id_grupo = ui->comboBox_grupo->currentData().toString();

    colaborador.setNome(nome);
    colaborador.setNomeUsuario(username);
    colaborador.setSenha(senha);
    colaborador.setTelefone(telefone);
    colaborador.setGrupo(grupo_controller.buscaPorId(id_grupo));

    if (global_functions::minCaracter(nome, 3)
        && global_functions::minCaracter(username, 3)
        && global_functions::minCaracter(senha, 3)
        && global_functions::minCaracter(telefone, 11)) {
        if (id_grupo != "0") {
            if (colaborador_controller.insere(colaborador)) {
                QMessageBox::information(this, "", "Cadastrado com sucesso!");
                limpa_formulario();
            }
        } else
            QMessageBox::warning(this, "", "Selecione um grupo.");

    } else {
        QMessageBox::warning(this, "", "Mínimo 3 caracteres (Nome/Nome de usuário/senha)\nMínimo 11 caracteres (telefone)");
        limpa_formulario();
    }
}

void fm_gestao_colaboradores::on_pushButton_cancelar_clicked()
{
    limpa_formulario();
}

void fm_gestao_colaboradores::on_tableWidget_colaboradores_itemSelectionChanged()
{
    int row = ui->tableWidget_colaboradores->currentRow();
    int id = ui->tableWidget_colaboradores->item(row, 0)->text().toInt();

    //altera_formulario_cadastro_edicao("edicao");

    ColaboradorController colaborador_controller;
    Colaborador colaborador = colaborador_controller.buscaPorId(id);

    ui->lineEdit_id->setText(QString::number(colaborador.getId()));
    ui->lineEdit_nome->setText(colaborador.getNome());
    ui->lineEdit_nome_de_usuario->setText(colaborador.getNomeUsuario());
    ui->lineEdit_senha->setText(colaborador.getSenha());
    ui->lineEdit_telefone->setText(colaborador.getTelefone());

    popula_combo_grupo(ui->comboBox_grupo);

    ui->comboBox_grupo->setCurrentText(colaborador.getGrupo().getDescricao());

    altera_formulario_cadastro_edicao(true);
}

void fm_gestao_colaboradores::on_pushButton_cancelar_clicked()
{
    limpa_formulario_edicao();
    altera_formulario_cadastro_edicao(false);
}

void fm_gestao_colaboradores::on_pushButton_excluir_clicked()
{
    QMessageBox::StandardButton resposta;
    resposta = QMessageBox::question(this, "", "Deseja realmente excluir?", QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        int id, row;
        ColaboradorController colaborador_controller;

        row = ui->tableWidget_colaboradores->currentRow();
        id = ui->tableWidget_colaboradores->item(row, 0)->text().toInt();

        if (colaborador_controller.remove(id)) {
          ui->tableWidget_colaboradores->removeRow(row);
          limpa_formulario_edicao();
          altera_formulario_cadastro_edicao(false);
          QMessageBox::information(this, "", "Excluido com sucesso!");
        }
    }
}

void fm_gestao_colaboradores::on_pushButton_ver_vendas_clicked()
{
    int row, id;

    row = ui->tableWidget_colaboradores->currentRow();
    id = ui->tableWidget_colaboradores->item(row, 0)->text().toInt();

    fm_colaborador_vendas f_colaborador_vendas(this, id);
    f_colaborador_vendas.exec();
}

void fm_gestao_colaboradores::on_pushButton_pesquisar_clicked()
{
    QString pesquisar = ui->lineEdit_pesquisar->text();
    ui->lineEdit_pesquisar->clear();

    ColaboradorController colaborador_controller;
    QVector<Colaborador> listaColaboradores;

    if (global_functions::minCaracter(pesquisar, 3)) {
        listaColaboradores = colaborador_controller.buscaPorNome(pesquisar);
    } else
        listaColaboradores = colaborador_controller.buscaTodos();

    popula_table_widget_colaboradores(listaColaboradores);
}
