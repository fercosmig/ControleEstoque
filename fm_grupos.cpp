#include "fm_grupos.h"
#include "ui_fm_grupos.h"

#include "global.h"
#include "GrupoController.h"
#include <QMessageBox>

fm_grupos::fm_grupos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_grupos)
{
    ui->setupUi(this);

    fm_grupos::inicializa_fm_grupos();
}

fm_grupos::~fm_grupos()
{
    delete ui;
}

/* ***** ***** ***** ***** *****
 *  MY METHODS
 * ***** ***** ***** ***** *****/

void fm_grupos::inicializa_fm_grupos()
{
    fm_grupos::carrega_combo_siglas();
    fm_grupos::atualiza_table_widget();

    ui->label_selected_row->setVisible(false);
}

void fm_grupos::carrega_combo_siglas()
{
    int i = 0;
    QString letras[] {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

    ui->comboBox_sigla->addItem("Selecione", i);
    for (QString sigla : letras){
        i++;
        ui->comboBox_sigla->addItem(sigla, i);
    }
}

void fm_grupos::atualiza_table_widget()
{
    QVector<Grupo> listaGrupos;
    GrupoController grupo_controller;

    listaGrupos = grupo_controller.buscaTodos();
    fm_grupos::popula_table_widget(listaGrupos);
}

void fm_grupos::popula_table_widget(QVector<Grupo> listaGrupos)
{
    QStringList header;
    Grupo grupo;

    header = {"ID", "Descrição", "Sigla"};
    global::formatTableWidget(ui->tableWidget_grupos, header);

    for (int i = 0; i < listaGrupos.size(); ++i) {
        grupo = listaGrupos[i];
        ui->tableWidget_grupos->insertRow(i);
        ui->tableWidget_grupos->setItem(i, 0, new QTableWidgetItem(QString::number(grupo.getId())));
        ui->tableWidget_grupos->setItem(i, 1, new QTableWidgetItem(grupo.getDescricao()));
        ui->tableWidget_grupos->setItem(i, 2, new QTableWidgetItem(grupo.getSigla()));
        ui->tableWidget_grupos->setRowHeight(i, 20);
    }
}

void fm_grupos::limpa_formulario()
{
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_descricao->clear();
    ui->comboBox_sigla->setCurrentIndex(0);
    ui->lineEdit_pesquisar->setFocus();
    ui->label_selected_row->setText("-1");
}

/* ***** ***** ***** ***** *****
 *  SLOTS
 * ***** ***** ***** ***** *****/

void fm_grupos::on_pushButton_fechar_clicked()
{
    close();
}

void fm_grupos::on_pushButton_limpar_clicked()
{
    fm_grupos::limpa_formulario();
}

void fm_grupos::on_pushButton_mostrar_todos_clicked()
{
    fm_grupos::atualiza_table_widget();
    fm_grupos::limpa_formulario();
    ui->pushButton_mostrar_todos->setEnabled(false);
}

void fm_grupos::on_pushButton_pesquisar_clicked()
{
    QString texto_pesquisa;
    Grupo grupo;
    QVector<Grupo> listaGrupos;
    GrupoController grupo_controller;

    texto_pesquisa = ui->lineEdit_pesquisar->text().trimmed();
    if (global::minCharacters(texto_pesquisa, 3)) {

        grupo.setDescricao(texto_pesquisa);
        listaGrupos = grupo_controller.buscaPorDescricao(grupo);

        fm_grupos::popula_table_widget(listaGrupos);
        ui->pushButton_mostrar_todos->setEnabled(true);

    } else
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres");
    fm_grupos::limpa_formulario();
}

void fm_grupos::on_pushButton_salvar_clicked()
{
    int row, id, combo_index;
    QString descricao, sigla, sigla_antes;
    Grupo grupo;
    GrupoController grupo_controller;
    QMessageBox::StandardButton resposta;

    row = ui->label_selected_row->text().toInt();
    id = ui->lineEdit_id->text().toInt();
    descricao = ui->lineEdit_descricao->text().trimmed();
    sigla = ui->comboBox_sigla->currentText();

    combo_index = ui->comboBox_sigla->currentIndex();

    if (!global::minCharacters(descricao, 3)) {
        QMessageBox::warning(this, "", "Descrição deve conter no mínimo 3 caracteres.");
        return;
    }

    if (combo_index == 0) {
        QMessageBox::warning(this, "", "Selecione um grupo.");
        return;
    }

    grupo.setId(id);
    grupo.setDescricao(descricao);
    grupo.setSigla(sigla);

    if (row == -1) { // INCLUSÃO

        if (grupo_controller.buscaSiglaDuplicada(grupo)) {
            QMessageBox::warning(this, "", "Sigla já utilizada.");
            return;
        }
        resposta = QMessageBox::question(this, "", "Tem certeza que deseja cadastrar?", QMessageBox::Yes | QMessageBox::No);
        if (resposta == QMessageBox::Yes) {
            grupo = grupo_controller.insere(grupo);
            row = ui->tableWidget_grupos->rowCount();
            ui->tableWidget_grupos->insertRow(row);
            ui->tableWidget_grupos->setItem(row, 0, new QTableWidgetItem(QString::number(grupo.getId())));
            ui->tableWidget_grupos->setItem(row, 1, new QTableWidgetItem(grupo.getDescricao()));
            ui->tableWidget_grupos->setItem(row, 2, new QTableWidgetItem(grupo.getSigla()));
            ui->tableWidget_grupos->setRowHeight(row, 20);
            QMessageBox::information(this, "", "Cadastrado com sucesso.");
            fm_grupos::limpa_formulario();
        }

    } else { // ALTERAÇÃO

        sigla_antes = ui->tableWidget_grupos->item(row, 2)->text();

        if (sigla != sigla_antes) {
            if (grupo_controller.buscaSiglaDuplicada(grupo)) {
                QMessageBox::warning(this, "", "Sigla já utilizada.");
                return;
            }
        }
        resposta = QMessageBox::question(this, "", "Tem certeza que deseja alterar?", QMessageBox::Yes | QMessageBox::No);
        if (resposta == QMessageBox::Yes) {
            if (grupo_controller.altera(grupo)) {
                ui->tableWidget_grupos->item(row, 1)->setText(grupo.getDescricao());
                ui->tableWidget_grupos->item(row, 2)->setText(grupo.getSigla());
                QMessageBox::information(this, "", "Alterado com sucesso.");
                fm_grupos::limpa_formulario();
            } else
                QMessageBox::warning(this, "", "Erro ao tentar alterar.");
        }
    }
}

void fm_grupos::on_tableWidget_grupos_itemSelectionChanged()
{
    int row, id, grupo_index;
    QString descricao, sigla;

    row = ui->tableWidget_grupos->currentRow();
    ui->label_selected_row->setText(QString::number(row));

    id = ui->tableWidget_grupos->item(row, 0)->text().toInt();
    descricao = ui->tableWidget_grupos->item(row, 1)->text();
    sigla = ui->tableWidget_grupos->item(row, 2)->text();

    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_descricao->setText(descricao);
    grupo_index = ui->comboBox_sigla->findText(sigla);
    ui->comboBox_sigla->setCurrentIndex(grupo_index);
}
