#ifndef CONEXAO_H
#define CONEXAO_H

#include "global.h"
#include <QtSql>

class Conexao
{
private:
protected:
public:
    // CONSTRUCTOR
    Conexao(){}

    // METHODS
    void open();
    bool isOpen();
    void close();
};

inline void Conexao::open()
{
    if (!global::dataBase.isOpen()) {
        if (!global::dataBase.open())
            qDebug() << "Conexao.open() " << global::dataBase.lastError().text();
    }
}

inline bool Conexao::isOpen()
{
    if (global::dataBase.isOpen())
        return true;
    return false;
}

inline void Conexao::close()
{
    if (global::dataBase.isOpen())
        global::dataBase.close();
}

#endif // CONEXAO_H
