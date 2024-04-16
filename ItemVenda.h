#ifndef ITEMVENDA_H
#define ITEMVENDA_H

#include "Venda.h"
#include "Produto.h"

/*
CREATE TABLE tb_itens_venda (
    id         INTEGER PRIMARY KEY AUTOINCREMENT,
    quantidade REAL    NOT NULL ON CONFLICT ROLLBACK,
    valor      REAL    NOT NULL ON CONFLICT ROLLBACK,
    id_venda   INTEGER NOT NULL ON CONFLICT ROLLBACK
                       REFERENCES tb_vendas (id) ON DELETE CASCADE,
    id_produto INTEGER NOT NULL ON CONFLICT ROLLBACK
                       REFERENCES tb_produtos (id) ON DELETE CASCADE
);
*/

class ItemVenda
{
private:
    int id;
    double quantidade;
    double valor;
    Venda venda;
    Produto produto;

protected:
public:
    // CONSTRUCTOR
    ItemVenda() {}

    // GETTERS AND SETTERS
    int getId() const;
    void setId(int newId);
    double getQuantidade() const;
    void setQuantidade(double newQuantidade);
    double getValor() const;
    void setValor(double newValor);
    Venda getVenda() const;
    void setVenda(const Venda &newVenda);
    Produto getProduto() const;
    void setProduto(const Produto &newProduto);
};

inline int ItemVenda::getId() const
{
    return id;
}

inline void ItemVenda::setId(int newId)
{
    id = newId;
}

inline double ItemVenda::getQuantidade() const
{
    return quantidade;
}

inline void ItemVenda::setQuantidade(double newQuantidade)
{
    quantidade = newQuantidade;
}

inline double ItemVenda::getValor() const
{
    return valor;
}

inline void ItemVenda::setValor(double newValor)
{
    valor = newValor;
}

inline Venda ItemVenda::getVenda() const
{
    return venda;
}

inline void ItemVenda::setVenda(const Venda &newVenda)
{
    venda = newVenda;
}

inline Produto ItemVenda::getProduto() const
{
    return produto;
}

inline void ItemVenda::setProduto(const Produto &newProduto)
{
    produto = newProduto;
}

#endif // ITEMVENDA_H
