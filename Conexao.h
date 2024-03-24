#ifndef CONEXAO_H
#define CONEXAO_H

#include <QDebug>
#include <QtSql>
#include "global_variables.h"

class Conexao
{
private:
protected:
public:
    // CONSTRUCTOR

    Conexao(){}

    void open()
    {
        if (!global_variables::bancoDeDados.isOpen()) {
            if (!global_variables::bancoDeDados.open())
                qDebug() << "Conexao.open(): " << global_variables::bancoDeDados.lastError().text();
        }
    }

    bool isOpen()
    {
        if (global_variables::bancoDeDados.isOpen())
            return true;
        return false;
    }

    void close()
    {
        if (global_variables::bancoDeDados.isOpen()) {
            global_variables::bancoDeDados.close();
        }
    }
};

#endif // CONEXAO_H
