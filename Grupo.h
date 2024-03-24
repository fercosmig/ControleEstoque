#ifndef GRUPO_H
#define GRUPO_H

#include <QString>

class Grupo
{
private:
    int id;
    QString descricao;
    QString sigla;

protected:
public:
    // CONSTRUCTOR

    Grupo() {}

    // GETTERS AND SETTERS

    void setId(int id) { this->id = id; }
    int getId() { return this->id; }

    void setDescricao(QString descricao) { this->descricao = descricao; }
    QString getDescricao() { return this->descricao; }

    void setSigla(QString sigla) { this->sigla = sigla; }
    QString getSigla() { return this->sigla; }
};

#endif // GRUPO_H
