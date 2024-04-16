#include "fm_colaboradores.h"
#include "ui_fm_colaboradores.h"

#include <QMessageBox>
#include "global.h"
#include "ColaboradorController.h"
#include "GrupoController.h"

fm_colaboradores::fm_colaboradores(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_colaboradores)
{
    ui->setupUi(this);

    fm_colaboradores::inicializa_fm_colaboradores();
}

fm_colaboradores::~fm_colaboradores()
{
    delete ui;
}

/* ***** ***** ***** ***** *****
 *  MY METHODS
 * ***** ***** ***** ***** *****/

void fm_colaboradores::inicializa_fm_colaboradores()
{
    ui->label_selected_row->setVisible(false);
    fm_colaboradores::atualiza_table_widget();
    fm_colaboradores::carrega_combo_grupos();
}

void fm_colaboradores::carrega_combo_grupos()
{
    QVector<Grupo> listaGrupos;
    Grupo grupo;
    GrupoController grupo_controller;

    ui->comboBox_grupo->addItem("Selecione", 0);

    listaGrupos = grupo_controller.buscaTodos();

    for (int i = 0; i < listaGrupos.size(); ++i) {
        grupo = listaGrupos[i];
        ui->comboBox_grupo->addItem(grupo.getSigla() + "-" + grupo.getDescricao(), grupo.getId());
    }
}

void fm_colaboradores::atualiza_table_widget()
{
    QVector<Colaborador> listaColaboradores;
    ColaboradorController colaborador_controller;

    listaColaboradores = colaborador_controller.buscaTodos();
    fm_colaboradores::popula_table_widget(listaColaboradores);
}

void fm_colaboradores::popula_table_widget(QVector<Colaborador> listaColaboradores)
{
    QStringList header;
    Colaborador colaborador;

    header = {"ID", "Nome", "E-mail", "Senha", "ID Grupo", "Grupo", "Sigla"};
    global::formatTableWidget(ui->tableWidget_colaboradores, header);

    for (int i = 0; i < listaColaboradores.size(); ++i) {
        colaborador = listaColaboradores[i];
        ui->tableWidget_colaboradores->insertRow(i);
        ui->tableWidget_colaboradores->setItem(i, 0, new QTableWidgetItem(QString::number(colaborador.getId())));
        ui->tableWidget_colaboradores->setItem(i, 1, new QTableWidgetItem(colaborador.getNome()));
        ui->tableWidget_colaboradores->setItem(i, 2, new QTableWidgetItem(colaborador.getEmail()));
        ui->tableWidget_colaboradores->setItem(i, 3, new QTableWidgetItem(colaborador.getSenha()));
        ui->tableWidget_colaboradores->setItem(i, 4, new QTableWidgetItem(QString::number(colaborador.getGrupo().getId())));
        ui->tableWidget_colaboradores->setItem(i, 5, new QTableWidgetItem(colaborador.getGrupo().getDescricao()));
        ui->tableWidget_colaboradores->setItem(i, 6, new QTableWidgetItem(colaborador.getGrupo().getSigla()));
        ui->tableWidget_colaboradores->setColumnHidden(3, true);
        ui->tableWidget_colaboradores->setColumnHidden(4, true);
        ui->tableWidget_colaboradores->setRowHeight(i, 20);
    }
}

void fm_colaboradores::limpa_formulario()
{
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_senha->clear();
    ui->comboBox_grupo->setCurrentIndex(0);
    ui->lineEdit_pesquisar->setFocus();
    ui->label_selected_row->setText("-1");
}

/* ***** ***** ***** ***** *****
 *  SLOTS
 * ***** ***** ***** ***** *****/

void fm_colaboradores::on_pushButton_pesquisar_clicked()
{
    QString texto_pesquisa;
    Colaborador colaborador;
    QVector<Colaborador> listaColaboradores;
    ColaboradorController colaborador_controller;

    texto_pesquisa = ui->lineEdit_pesquisar->text().trimmed();

    if (!global::minCharacters(texto_pesquisa, 3)) {
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres");
        return;
    }

    colaborador.setNome(texto_pesquisa);
    colaborador.setEmail(texto_pesquisa);
    listaColaboradores = colaborador_controller.buscaPorNomeEmail(colaborador);
    fm_colaboradores::popula_table_widget(listaColaboradores);
    ui->pushButton_mostrar_todos->setEnabled(true);
}

void fm_colaboradores::on_pushButton_mostrar_todos_clicked()
{
    fm_colaboradores::atualiza_table_widget();
    fm_colaboradores::limpa_formulario();
    ui->pushButton_mostrar_todos->setEnabled(false);
}

void fm_colaboradores::on_tableWidget_colaboradores_itemSelectionChanged()
{
    int row, id, id_grupo, index_grupo;
    QString nome, email, senha;

    row = ui->tableWidget_colaboradores->currentRow();
    ui->label_selected_row->setText(QString::number(row));

    id = ui->tableWidget_colaboradores->item(row, 0)->text().toInt();
    nome = ui->tableWidget_colaboradores->item(row, 1)->text();
    email = ui->tableWidget_colaboradores->item(row, 2)->text();
    senha = ui->tableWidget_colaboradores->item(row, 3)->text();
    id_grupo = ui->tableWidget_colaboradores->item(row, 4)->text().toInt();

    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_nome->setText(nome);
    ui->lineEdit_email->setText(email);
    ui->lineEdit_senha->setText(senha);
    index_grupo = ui->comboBox_grupo->findData(id_grupo);
    ui->comboBox_grupo->setCurrentIndex(index_grupo);
}

void fm_colaboradores::on_pushButton_salvar_clicked()
{
    int row, id, id_grupo;
    QString nome, email, senha, descricao, sigla, mensagem, email_antes;
    QStringList sigla_descricao;
    Grupo grupo;
    Colaborador colaborador;
    ColaboradorController colaborador_controller;

    row = ui->label_selected_row->text().toInt();

    id = ui->lineEdit_id->text().toInt();
    nome = ui->lineEdit_nome->text().trimmed();
    email = ui->lineEdit_email->text().trimmed();
    senha = ui->lineEdit_senha->text().trimmed();
    id_grupo = ui->comboBox_grupo->currentData().toInt();
    sigla_descricao = ui->comboBox_grupo->currentText().split("-");
    descricao = sigla_descricao[1];
    sigla = sigla_descricao[0];

    if (!global::minCharacters(nome, 3) || !global::minCharacters(email, 7) || !global::minCharacters(senha, 3 || !(id_grupo > 0))) {
        mensagem = "Nome, Senha devem ter no mínimo 3 caracteres.\n";
        mensagem += "E-mail deve ter no mínimo 7 caracteres.\n";
        mensagem += "Um grupo deve estar selecionado.";
        QMessageBox::warning(this, "", mensagem);
    }

    grupo.setId(id_grupo);
    grupo.setDescricao(descricao);
    grupo.setSigla(sigla);

    colaborador.setId(id);
    colaborador.setNome(nome);
    colaborador.setEmail(email);
    colaborador.setSenha(senha);
    colaborador.setGrupo(grupo);

    if (row == -1) { // INCLUSÃO

        if (colaborador_controller.verificaDuplicidadeEmail(colaborador)) {
            QMessageBox::warning(this, "", "E-mail já cadastrado no bando de dados.");
            return;
        }
        colaborador = colaborador_controller.insere(colaborador);

        row = ui->tableWidget_colaboradores->rowCount();

        ui->tableWidget_colaboradores->insertRow(row);
        ui->tableWidget_colaboradores->setItem(row, 0, new QTableWidgetItem(QString::number(colaborador.getId())));
        ui->tableWidget_colaboradores->setItem(row, 1, new QTableWidgetItem(colaborador.getNome()));
        ui->tableWidget_colaboradores->setItem(row, 2, new QTableWidgetItem(colaborador.getEmail()));
        ui->tableWidget_colaboradores->setItem(row, 3, new QTableWidgetItem(colaborador.getSenha()));
        ui->tableWidget_colaboradores->setItem(row, 4, new QTableWidgetItem(QString::number(colaborador.getGrupo().getId())));
        ui->tableWidget_colaboradores->setItem(row, 5, new QTableWidgetItem(colaborador.getGrupo().getDescricao()));
        ui->tableWidget_colaboradores->setItem(row, 6, new QTableWidgetItem(colaborador.getGrupo().getSigla()));
        ui->tableWidget_colaboradores->setRowHeight(row, 20);
        QMessageBox::information(this, "", "Cadastrado com sucesso!");
        fm_colaboradores::limpa_formulario();

    } else { // ALTERAÇÃO

        email_antes = ui->tableWidget_colaboradores->item(row, 2)->text();

        if (email != email_antes) {
            if (colaborador_controller.verificaDuplicidadeEmail(colaborador)) {
                QMessageBox::warning(this, "", "E-mail já cadastrado no bando de dados.");
                return;
            }
        }

        if (colaborador_controller.altera(colaborador)) {
            ui->tableWidget_colaboradores->item(row, 1)->setText(colaborador.getNome());
            ui->tableWidget_colaboradores->item(row, 2)->setText(colaborador.getEmail());
            ui->tableWidget_colaboradores->item(row, 3)->setText(colaborador.getSenha());
            ui->tableWidget_colaboradores->item(row, 4)->setText(QString::number(colaborador.getGrupo().getId()));
            ui->tableWidget_colaboradores->item(row, 5)->setText(colaborador.getGrupo().getDescricao());
            ui->tableWidget_colaboradores->item(row, 6)->setText(colaborador.getGrupo().getSigla());
            QMessageBox::information(this, "", "Alterado com sucesso!");
            fm_colaboradores::limpa_formulario();
        } else
            QMessageBox::warning(this, "", "Erro ao tentar alterar!");
    }
}

void fm_colaboradores::on_pushButton_limpar_clicked()
{
    fm_colaboradores::limpa_formulario();
}

void fm_colaboradores::on_pushButton_fechar_clicked()
{
    close();
}
