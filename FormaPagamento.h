#ifndef FORMAPAGAMENTO_H
#define FORMAPAGAMENTO_H

#include <QString>

/*
CREATE TABLE tb_formas_pagamento (
    id        INTEGER   PRIMARY KEY AUTOINCREMENT,
    descricao TEXT (30) NOT NULL ON CONFLICT ROLLBACK
);
*/

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
    int getId() const;
    void setId(int newId);
    QString getDescricao() const;
    void setDescricao(const QString &newDescricao);
};

inline int FormaPagamento::getId() const
{
    return id;
}

inline void FormaPagamento::setId(int newId)
{
    id = newId;
}

inline QString FormaPagamento::getDescricao() const
{
    return descricao;
}

inline void FormaPagamento::setDescricao(const QString &newDescricao)
{
    descricao = newDescricao;
}

#endif // FORMAPAGAMENTO_H
