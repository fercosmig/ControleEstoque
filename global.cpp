#include "global.h"

#include <QHeaderView>
#include <QDebug>
#include <QtSql>

global::global() {}

/* ***** ***** ***** ***** *****
 *  GLOBAL VARIABLES
 * ***** ***** ***** ***** *****/

Colaborador global::colaboradorLogado;
bool global::isLogged;
QSqlDatabase global::dataBase;
QString global::version;

/* ***** ***** ***** ***** *****
 *  GLOBAL METHODS & FUNCTIONS
 * ***** ***** ***** ***** *****/

void global::initializeGlobalVariables()
{
    QString appPath, dbName, dbFullPath;

    appPath = qApp->applicationDirPath();
    dbName = "/db/controle_estoque.db";
    dbFullPath = appPath + dbName;

    global::dataBase = QSqlDatabase::addDatabase("QSQLITE");
    global::dataBase.setDatabaseName(dbFullPath);

    global::isLogged = false;

    global::version = "2.0";
}

bool global::minCharacters(QString str, int quantity)
{
    if (str.length() < quantity)
        return false;
    return true;
}

void global::formatTableWidget(QTableWidget *tw, QStringList header)
{
    int columns = header.size();

    tw->clear();
    tw->setRowCount(0);

    // quantidade de colunas
    tw->setColumnCount(columns);

    // insere cabeçalho
    tw->setHorizontalHeaderLabels(header);

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

QString global::formatDoubleToString(double value)
{
    QString formated;
    try {

        formated = QString("%1").arg(value, 0, 'f', 2);

    } catch (const std::exception &e) {
        qDebug() << "global::formatDoubleToString(): ERROR:" << e.what();
    }

    return formated;
}
