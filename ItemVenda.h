#ifndef ITEMVENDA_H
#define ITEMVENDA_H

#include <QString>
#include "Produto.h"
#include "Venda.h"

class ItemVenda
{
private:
    int id;             // id do item na tabela de itens
    int quantidade;     // quantidade vendida do produto
    double valor_venda; // valor unitario do produto usado na venda
    Venda venda;        // id da venda a qual este item pertence
    Produto produto;    //id do produto vendido

protected:
public:
    // CONSTRUCTOR

    ItemVenda() {}

    // GETTERS AND SETTERS

    void setId(int id) { this->id = id; }
    int getId() { return this->id; }

    void setQuantidade(int quantidade) { this->quantidade = quantidade; }
    int getQuantidade() { return this->quantidade; }

    void setValorVenda(double valor_venda) { this->valor_venda = valor_venda; }
    double getValorVenda() { return this->valor_venda; }

    void setVenda(Venda venda) { this->venda = venda; }
    Venda getVenda() { return this->venda; }

    void setProduto(Produto produto) { this->produto = produto; }
    Produto getProduto() { return this->produto; }
};

#endif // ITEMVENDA_H
