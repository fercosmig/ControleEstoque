#ifndef GLOBAL_H
#define GLOBAL_H

#include <QSqlDatabase>
#include <QTableWidget>
#include "Colaborador.h"

class global
{
public:
    global();

    // VARIABLES
    static QSqlDatabase dataBase;
    static Colaborador colaboradorLogado;
    static bool isLogged;
    static QString version;

    // FUNCTIONS
    static void initializeGlobalVariables();
    static bool minCharacters(QString str, int quantity);
    static void formatTableWidget(QTableWidget *tw, QStringList header);
    static QString formatDoubleToString(double value);
};

#endif // GLOBAL_H
