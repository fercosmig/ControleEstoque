/* ********************************************
 * Fernando Costa Migliorini
 * 2024-03-02
 */

#include "global_functions.h"
#include <QDebug>
#include <QHeaderView>
#include <QString>
#include <QTableWidget>

global_functions::global_functions() {}

QString global_functions::formata_double(double valor)
{
    /*
     * formata double - FD
     * Recebe um double.
     * Retorna uma string com o valor formatado com 2 casas decimais.
     */

    QString formatado;
    try {

        formatado = QString("%1").arg(valor, 0, 'f', 2);

    } catch (const std::exception &e) {
        qDebug() << "fd (formata_double): " << e.what();
    }

    return formatado;
}

void global_functions::formata_table_widget(QTableWidget *tw, QStringList cabecalho)
{
    int columns = cabecalho.size();

    // quantidade de colunas
    tw->setColumnCount(columns);

    // insere cabeçalho
    tw->setHorizontalHeaderLabels(cabecalho);

    // desabilitando edição
    tw->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // seleção de toda a linha
    tw->setSelectionBehavior(QAbstractItemView::SelectRows);

    // remove nº linha
    tw->verticalHeader()->setVisible(false);

    // selecionando somente uma linha
    tw->setSelectionMode(QAbstractItemView::SingleSelection);

    // formata largura da coluna conforme conteudo
    tw->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // formata largura da coluna conforme tamanho do tableWidget
    //tw->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

bool global_functions::minCaracter(QString str, int quantidade)
{
    /*
     * valida quantidade de caracteres - VQC
     * Recebe uma string e a quantidade mínima de caracteres que a string deve conter.
     * Retorna verdadeiro ou false.
     */

    if (str.length() < quantidade)
        return false;
    return true;
}
