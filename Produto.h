#ifndef PRODUTO_H
#define PRODUTO_H

#include <QString>
#include <Fornecedor.h>

class Produto
{
private:
    int id;
    QString descricao;
    int quantidade;
    double valor_compra;
    double valor_venda;
    Fornecedor fornecedor;

protected:
public:
    // CONSTRUCTOR

    Produto() {}

    // GETTERS AND SETTERS

    void setId(int id) { this->id = id; }
    int getId() { return this->id; }

    void setDescricao(QString descricao) { this->descricao = descricao; }
    QString getDescricao() { return this->descricao; }

    void setQuantidade(int quantidade) { this->quantidade = quantidade; }
    int getQuantidade() { return this->quantidade; }

    void setValorCompra(double valor_compra) { this->valor_compra = valor_compra; }
    double getValorCompra() { return this->valor_compra; }

    void setValorVenda(double valor_venda) { this->valor_venda = valor_venda; }
    double getValorVenda() { return this->valor_venda; }

    void setFornecedor(Fornecedor fornecedor) { this->fornecedor = fornecedor; }
    Fornecedor getFornecedor() { return this->fornecedor; }
};

#endif // PRODUTO_H
