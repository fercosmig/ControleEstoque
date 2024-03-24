#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <QSqlDatabase>
#include "Colaborador.h"

class global_variables
{
public:
    static QSqlDatabase bancoDeDados;
    static Colaborador colaboradorLogado;
    static bool isLogged;

    global_variables();
};

#endif // GLOBAL_VARIABLES_H
