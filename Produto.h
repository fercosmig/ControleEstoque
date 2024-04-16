#ifndef PRODUTO_H
#define PRODUTO_H

#include <QString>
#include "Fornecedor.h"

/*
CREATE TABLE tb_produtos (
    id            TEXT (15) PRIMARY KEY
                            NOT NULL ON CONFLICT ROLLBACK
                            UNIQUE ON CONFLICT ROLLBACK,
    descricao     TEXT (30) NOT NULL ON CONFLICT ROLLBACK,
    quantidade    REAL      NOT NULL ON CONFLICT ROLLBACK,
    custo         REAL      NOT NULL ON CONFLICT ROLLBACK,
    valor         REAL      NOT NULL ON CONFLICT ROLLBACK,
    id_fornecedor INTEGER   NOT NULL ON CONFLICT ROLLBACK
                            REFERENCES tb_fornecedores (id) ON DELETE CASCADE
);
*/

class Produto
{
private:
    QString id;
    QString descricao;
    double quantidade;
    double custo;
    double valor;
    Fornecedor fornecedor;

protected:
public:
    // CONSTRUCTOR
    Produto() {}

    // GETTERS AND SETTERS
    QString getId() const;
    void setId(const QString &newId);
    QString getDescricao() const;
    void setDescricao(const QString &newDescricao);
    double getQuantidade() const;
    void setQuantidade(double newQuantidade);
    double getCusto() const;
    void setCusto(double newCusto);
    double getValor() const;
    void setValor(double newValor);
    Fornecedor getFornecedor() const;
    void setFornecedor(const Fornecedor &newFornecedor);
};

inline QString Produto::getId() const
{
    return id;
}

inline void Produto::setId(const QString &newId)
{
    id = newId;
}

inline QString Produto::getDescricao() const
{
    return descricao;
}

inline void Produto::setDescricao(const QString &newDescricao)
{
    descricao = newDescricao;
}

inline double Produto::getQuantidade() const
{
    return quantidade;
}

inline void Produto::setQuantidade(double newQuantidade)
{
    quantidade = newQuantidade;
}

inline double Produto::getCusto() const
{
    return custo;
}

inline void Produto::setCusto(double newCusto)
{
    custo = newCusto;
}

inline double Produto::getValor() const
{
    return valor;
}

inline void Produto::setValor(double newValor)
{
    valor = newValor;
}

inline Fornecedor Produto::getFornecedor() const
{
    return fornecedor;
}

inline void Produto::setFornecedor(const Fornecedor &newFornecedor)
{
    fornecedor = newFornecedor;
}

#endif // PRODUTO_H
