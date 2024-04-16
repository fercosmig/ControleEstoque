#include "fm_produtos.h"
#include "ui_fm_produtos.h"

#include "ProdutoController.h"
#include "FornecedorController.h"
#include <QMessageBox>

fm_produtos::fm_produtos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_produtos)
{
    ui->setupUi(this);

    fm_produtos::inicializa_fm_produtos();
}

fm_produtos::~fm_produtos()
{
    delete ui;
}

/* ***** ***** ***** ***** *****
 *  MY METHODS
 * ***** ***** ***** ***** *****/

void fm_produtos::inicializa_fm_produtos()
{
    fm_produtos::atualiza_table_widget();
    fm_produtos::carrega_combo_fornecedores();
}

void fm_produtos::atualiza_table_widget()
{

    ProdutoController produto_controller;
    QVector<Produto> listaProdutos;

    listaProdutos = produto_controller.buscaTodos();
    fm_produtos::popula_table_widget(listaProdutos);
}

void fm_produtos::popula_table_widget(QVector<Produto> listaProdutos)
{
    QStringList header;
    Produto produto;

    header = {"ID", "Descrição", "Quantidade", "Custo", "Valor", "ID Fornecedor", "Razao Social", "Nome Fantasia"};
    global::formatTableWidget(ui->tableWidget_produtos, header);

    for (int i = 0; i < listaProdutos.size(); ++i) {
        produto = listaProdutos[i];
        ui->tableWidget_produtos->insertRow(i);
        ui->tableWidget_produtos->setItem(i, 0, new QTableWidgetItem(produto.getId()));
        ui->tableWidget_produtos->setItem(i, 1, new QTableWidgetItem(produto.getDescricao()));
        ui->tableWidget_produtos->setItem(i, 2, new QTableWidgetItem(global::formatDoubleToString(produto.getQuantidade())));
        ui->tableWidget_produtos->setItem(i, 3, new QTableWidgetItem(global::formatDoubleToString(produto.getCusto())));
        ui->tableWidget_produtos->setItem(i, 4, new QTableWidgetItem(global::formatDoubleToString(produto.getValor())));
        ui->tableWidget_produtos->setItem(i, 5, new QTableWidgetItem(QString::number(produto.getFornecedor().getId())));
        ui->tableWidget_produtos->setItem(i, 6, new QTableWidgetItem(produto.getFornecedor().getRazaoSocial()));
        ui->tableWidget_produtos->setItem(i, 7, new QTableWidgetItem(produto.getFornecedor().getNomeFantasia()));
        ui->tableWidget_produtos->setRowHeight(i, 20);
        ui->tableWidget_produtos->setColumnHidden(5, true);
        ui->tableWidget_produtos->setColumnHidden(6, true);
    }
}

void fm_produtos::carrega_combo_fornecedores()
{
    Fornecedor fornecedor;
    FornecedorController fornecedor_controller;
    QVector<Fornecedor> listaFornecedores;

    ui->comboBox_fornecedores->addItem("Selecione", 0);

    listaFornecedores = fornecedor_controller.buscaTodos();
    for (int i = 0; i < listaFornecedores.size(); ++i) {
        fornecedor = listaFornecedores[i];
        ui->comboBox_fornecedores->addItem(fornecedor.getNomeFantasia() + "-" + fornecedor.getRazaoSocial(), fornecedor.getId());
    }
}

void fm_produtos::limpa_formulario()
{
    ui->lineEdit_pesquisar->clear();
    ui->lineEdit_id->clear();
    ui->lineEdit_descricao->clear();
    ui->lineEdit_quantidade->clear();
    ui->lineEdit_custo->clear();
    ui->lineEdit_valor->clear();
    ui->lineEdit_pesquisar->setFocus();
    ui->label_selected_row->setText("-1");
    ui->lineEdit_id->setEnabled(true);
    ui->comboBox_fornecedores->setCurrentIndex(0);
}

/* ***** ***** ***** ***** *****
 *  SLOTS
 * ***** ***** ***** ***** *****/

void fm_produtos::on_pushButton_pesquisar_clicked()
{
    QString texto_pesquisar;
    QVector<Produto> listaProdutos;
    ProdutoController produto_controller;
    Produto produto;

    texto_pesquisar = ui->lineEdit_pesquisar->text().trimmed();

    if (global::minCharacters(texto_pesquisar, 3)) {
        produto.setDescricao(texto_pesquisar);
        listaProdutos = produto_controller.buscaPorDescricao(produto);
        fm_produtos::popula_table_widget(listaProdutos);
        fm_produtos::limpa_formulario();
        ui->pushButton_mostrar_todos->setEnabled(true);
    } else
        QMessageBox::warning(this, "", "Digite pelo menos 3 caracteres.");
}

void fm_produtos::on_pushButton_mostrar_todos_clicked()
{
    fm_produtos::atualiza_table_widget();
    fm_produtos::limpa_formulario();
    ui->pushButton_mostrar_todos->setEnabled(false);
}

void fm_produtos::on_tableWidget_produtos_itemSelectionChanged()
{
    int row, index_combo;
    QString id, descricao;
    double quantidade, custo, valor, id_fornecedor;

    row = ui->tableWidget_produtos->currentRow();
    ui->label_selected_row->setText(QString::number(row));

    id = ui->tableWidget_produtos->item(row, 0)->text();
    descricao = ui->tableWidget_produtos->item(row, 1)->text();
    quantidade = ui->tableWidget_produtos->item(row, 2)->text().toDouble();
    custo = ui->tableWidget_produtos->item(row, 3)->text().toDouble();
    valor = ui->tableWidget_produtos->item(row, 4)->text().toDouble();
    id_fornecedor = ui->tableWidget_produtos->item(row, 5)->text().toInt();

    ui->lineEdit_id->setText(id);
    ui->lineEdit_descricao->setText(descricao);
    ui->lineEdit_quantidade->setText(QString::number(quantidade));
    ui->lineEdit_custo->setText(QString::number(custo));
    ui->lineEdit_valor->setText(QString::number(valor));
    index_combo = ui->comboBox_fornecedores->findData(id_fornecedor);
    ui->comboBox_fornecedores->setCurrentIndex(index_combo);
    ui->lineEdit_id->setEnabled(false);
}

void fm_produtos::on_pushButton_salvar_clicked()
{
    int row, id_fornecedor;
    QString id, descricao, razao_social, nome_fantasia, mensagem;
    double quantidade, custo, valor;
    Produto produto;
    Fornecedor fornecedor;
    QStringList dados_fornecedor;
    ProdutoController produto_controller;
    QMessageBox::StandardButton resposta;

    row = ui->label_selected_row->text().toInt();

    id = ui->lineEdit_id->text();
    descricao = ui->lineEdit_descricao->text();
    quantidade = ui->lineEdit_quantidade->text().replace(",", ".").toDouble();
    custo = ui->lineEdit_custo->text().replace(",", ".").toDouble();
    valor = ui->lineEdit_valor->text().replace(",", ".").toDouble();
    id_fornecedor = ui->comboBox_fornecedores->currentData().toInt();
    dados_fornecedor = ui->comboBox_fornecedores->currentText().split("-");
    razao_social = dados_fornecedor[1];
    nome_fantasia = dados_fornecedor[0];

    if (!global::minCharacters(descricao, 3) || !(custo > 0) || !(valor > custo) || !(id_fornecedor > 0) ) {
        mensagem = "Descrição deve ter no mínimo 3 caracteres.\n";
        mensagem += "Custo deve ser maior que 0. Valor deve ser maior que custo.\n";
        mensagem += "Um grupo deve ser selecionado.";
        QMessageBox::warning(this, "", mensagem);
    }

    fornecedor.setId(id_fornecedor);
    fornecedor.setRazaoSocial(razao_social);
    fornecedor.setNomeFantasia(nome_fantasia);

    produto.setId(id);
    produto.setDescricao(descricao);
    produto.setQuantidade(quantidade);
    produto.setCusto(custo);
    produto.setValor(valor);
    produto.setFornecedor(fornecedor);

    if (row == -1) { // INCLUSAO

        resposta = QMessageBox::question(this, "", "Tem certeza que deseja incluir?", QMessageBox::Yes | QMessageBox::No);
        if (resposta == QMessageBox::Yes) {
            if (!produto_controller.verificaDuplicidadeId(produto)) {
                if (produto_controller.insere(produto)) {

                    row  = ui->tableWidget_produtos->rowCount();

                    ui->tableWidget_produtos->insertRow(row);
                    ui->tableWidget_produtos->setItem(row, 0, new QTableWidgetItem(produto.getId()));
                    ui->tableWidget_produtos->setItem(row, 1, new QTableWidgetItem(produto.getDescricao()));
                    ui->tableWidget_produtos->setItem(row, 2, new QTableWidgetItem(global::formatDoubleToString(produto.getQuantidade())));
                    ui->tableWidget_produtos->setItem(row, 3, new QTableWidgetItem(global::formatDoubleToString(produto.getCusto())));
                    ui->tableWidget_produtos->setItem(row, 4, new QTableWidgetItem(global::formatDoubleToString(produto.getValor())));
                    ui->tableWidget_produtos->setItem(row, 5, new QTableWidgetItem(QString::number(produto.getFornecedor().getId())));
                    ui->tableWidget_produtos->setItem(row, 6, new QTableWidgetItem(produto.getFornecedor().getRazaoSocial()));
                    ui->tableWidget_produtos->setItem(row, 7, new QTableWidgetItem(produto.getFornecedor().getNomeFantasia()));
                    ui->tableWidget_produtos->setRowHeight(row, 20);
                    fm_produtos::limpa_formulario();
                    QMessageBox::information(this, "", "Cadastrado com sucesso");
                } else
                    QMessageBox::information(this, "", "Problemas no cadastrado.");

            } else
                QMessageBox::warning(this, "", "ID já existe!");
        }

    } else { // ALTERAÇÃO

        if (produto_controller.altera(produto)) {
            ui->tableWidget_produtos->item(row, 1)->setText(produto.getDescricao());
            ui->tableWidget_produtos->item(row, 2)->setText(global::formatDoubleToString(produto.getQuantidade()));
            ui->tableWidget_produtos->item(row, 3)->setText(global::formatDoubleToString(produto.getCusto()));
            ui->tableWidget_produtos->item(row, 4)->setText(global::formatDoubleToString(produto.getValor()));
            ui->tableWidget_produtos->item(row, 5)->setText(QString::number(produto.getFornecedor().getId()));
            ui->tableWidget_produtos->item(row, 6)->setText(produto.getFornecedor().getRazaoSocial());
            ui->tableWidget_produtos->item(row, 7)->setText(produto.getFornecedor().getNomeFantasia());
            fm_produtos::limpa_formulario();
            QMessageBox::information(this, "", "Alterado com sucesso");
        } else
            QMessageBox::information(this, "", "Problema ao tentar alterar.");
    }
}

void fm_produtos::on_pushButton_limpar_clicked()
{
    fm_produtos::limpa_formulario();
}

void fm_produtos::on_pushButton_fechar_clicked()
{
    close();
}
