#ifndef VENDA_H
#define VENDA_H

#include <QString>
#include "FormaPagamento.h"
#include "Colaborador.h"

/*
CREATE TABLE tb_vendas (
    id                 INTEGER PRIMARY KEY AUTOINCREMENT,
    data               NUMERIC NOT NULL ON CONFLICT ROLLBACK
                               DEFAULT (date('now', 'localtime') ),
    hora               NUMERIC NOT NULL ON CONFLICT ROLLBACK
                               DEFAULT (time('now', 'localtime') ),
    valor              REAL    NOT NULL ON CONFLICT ROLLBACK,
    id_forma_pagamento INTEGER NOT NULL ON CONFLICT ROLLBACK
                               REFERENCES tb_formas_pagamento (id) ON DELETE CASCADE,
    id_colaborador     INTEGER REFERENCES tb_colaboradores (id) ON DELETE CASCADE
                               NOT NULL ON CONFLICT ROLLBACK
);
*/

class Venda
{
private:
    int id;
    QString data;
    QString hora;
    double valor;
    FormaPagamento formaPagamento;
    Colaborador colaborador;

protected:
public:
    // CONSTRUCTOR
    Venda() {}

    // GETTERS AND SETTERS
    int getId() const;
    void setId(int newId);
    QString getData() const;
    void setData(const QString &newData);
    QString getHora() const;
    void setHora(const QString &newHora);
    double getValor() const;
    void setValor(double newValor);
    FormaPagamento getFormaPagamento() const;
    void setFormaPagamento(const FormaPagamento &newFormaPagamento);
    Colaborador getColaborador() const;
    void setColaborador(const Colaborador &newColaborador);
};

inline int Venda::getId() const
{
    return id;
}

inline void Venda::setId(int newId)
{
    id = newId;
}

inline QString Venda::getData() const
{
    return data;
}

inline void Venda::setData(const QString &newData)
{
    data = newData;
}

inline QString Venda::getHora() const
{
    return hora;
}

inline void Venda::setHora(const QString &newHora)
{
    hora = newHora;
}

inline double Venda::getValor() const
{
    return valor;
}

inline void Venda::setValor(double newValor)
{
    valor = newValor;
}

inline FormaPagamento Venda::getFormaPagamento() const
{
    return formaPagamento;
}

inline void Venda::setFormaPagamento(const FormaPagamento &newFormaPagamento)
{
    formaPagamento = newFormaPagamento;
}

inline Colaborador Venda::getColaborador() const
{
    return colaborador;
}

inline void Venda::setColaborador(const Colaborador &newColaborador)
{
    colaborador = newColaborador;
}

#endif // VENDA_H
