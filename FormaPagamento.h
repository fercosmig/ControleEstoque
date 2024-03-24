#ifndef FORMAPAGAMENTO_H
#define FORMAPAGAMENTO_H

#include <QString>

class FormaPagamento
{
private:
    int id;
    QString descricao;

protected:
public:
    // CONSTRUCTOR

    FormaPagamento() {}

    //GETTERS AND SETTERS

    void setId(int id) { this->id = id; }
    int getId() { return this->id; }

    void setDescricao(QString descricao) { this->descricao = descricao; }
    QString getDescricao() { return this->descricao; }
};

#endif // FORMAPAGAMENTO_H
