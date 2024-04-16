#ifndef ITEMVENDACONTROLLER_H
#define ITEMVENDACONTROLLER_H

#include "Conexao.h"
#include "ItemVenda.h"

class ItemVendaController{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

protected:
public:
    // CONSTRUCTOR
    ItemVendaController() {}

    //METHODS
    void insere(ItemVenda item_venda);
    QVector<ItemVenda> buscaPorIdVenda(int id_venda);
};

inline void ItemVendaController::insere(ItemVenda item_venda)
{
    sql = "INSERT INTO tb_itens_venda ( quantidade, valor, id_venda, id_produto ) ";
    sql+= "VALUES ( :quantidade, :valor, :id_venda, :id_produto )";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":quantidade", QString::number(item_venda.getQuantidade()));
        query.bindValue(":valor", QString::number(item_venda.getValor()));
        query.bindValue(":id_venda", QString::number(item_venda.getVenda().getId()));
        query.bindValue(":id_produto", item_venda.getProduto().getId());

        if (!query.exec())
            qDebug() << "ItemVendaController::insere() query.exec(): " << query.lastError().text();
    }
    conn.close();
}

inline QVector<ItemVenda> ItemVendaController::buscaPorIdVenda(int id_venda)
{
    sql = "SELECT ";
    sql += "tb_itens_venda.id, ";
    sql += "tb_itens_venda.quantidade, ";
    sql += "tb_itens_venda.valor, ";
    sql += "tb_vendas.id AS id_venda, ";
    sql += "tb_vendas.data, ";
    sql += "tb_vendas.hora, ";
    sql += "tb_vendas.valor AS valor_venda, ";
    sql += "tb_formas_pagamento.id AS id_forma_pagamento, ";
    sql += "tb_formas_pagamento.descricao AS descricao_forma_pagamento, ";
    sql += "tb_colaboradores.id AS id_colaborador, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.email, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id AS id_grupo, ";
    sql += "tb_grupos.descricao AS descricao_grupo, ";
    sql += "tb_grupos.sigla, ";
    sql += "tb_produtos.id AS id_produto, ";
    sql += "tb_produtos.descricao AS descricao_produto, ";
    sql += "tb_produtos.quantidade AS quantidade_produto, ";
    sql += "tb_produtos.custo, ";
    sql += "tb_produtos.valor AS valor_produto, ";
    sql += "tb_fornecedores.id AS id_fornecedor, ";
    sql += "tb_fornecedores.razao_social, ";
    sql += "tb_fornecedores.nome_fantasia ";
    sql += "FROM tb_itens_venda ";
    sql += "INNER JOIN tb_vendas ";
    sql += "ON tb_itens_venda.id_venda = tb_vendas.id ";
    sql += "INNER JOIN tb_formas_pagamento ";
    sql += "ON tb_vendas.id_forma_pagamento = tb_formas_pagamento.id ";
    sql += "INNER JOIN tb_colaboradores ";
    sql += "ON tb_vendas.id_colaborador = tb_colaboradores.id ";
    sql += "INNER JOIN tb_grupos ";
    sql += "ON tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "INNER JOIN tb_produtos ";
    sql += "ON tb_itens_venda.id_produto = tb_produtos.id ";
    sql += "INNER JOIN tb_fornecedores ";
    sql += "ON tb_produtos.id_fornecedor = tb_fornecedores.id ";
    sql += "WHERE tb_itens_venda.id_venda = :id";

    if (!conn.isOpen())
        conn.open();

    QVector<ItemVenda> listaItensVenda;
    Fornecedor fornecedor;
    Produto produto;
    Grupo grupo;
    Colaborador colaborador;
    FormaPagamento forma_pagamento;
    Venda venda;
    ItemVenda item_venda;

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":id", id_venda);
        if (query.exec()) {
            if (query.next()) {
                do {
                    // ItemVenda precisa de Produto que precisa de Fornecedor
                    fornecedor.setId(query.record().value("id_fornecedor").toInt());
                    fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                    fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());

                    // ItemVenda precisa de Produto
                    produto.setId(query.record().value("id_produto").toString());
                    produto.setDescricao(query.record().value("descricao_produto").toString());
                    produto.setQuantidade(query.record().value("quantidade_produto").toDouble());
                    produto.setCusto(query.record().value("custo").toDouble());
                    produto.setValor(query.record().value("valor_produto").toDouble());
                    produto.setFornecedor(fornecedor);

                    // ItemVenda precisa de Venda que precisa de Colaborador que precisa de Grupo
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setDescricao(query.record().value("descricao_grupo").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    // ItemVenda precisa de Venda que precisa de Colaborador
                    colaborador.setId(query.record().value("id_colaborador").toInt());
                    colaborador.setNome(query.record().value("nome").toString());
                    colaborador.setEmail(query.record().value("email").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setGrupo(grupo);

                    // ItemVenda precisa de Venda que precisa de FormaPagamento
                    forma_pagamento.setId(query.record().value("id_forma_pagamento").toInt());
                    forma_pagamento.setDescricao(query.record().value("descricao_forma_pagamento").toString());

                    // ItemVenda precisa de Venda
                    venda.setId(query.record().value("id_venda").toInt());
                    venda.setData(query.record().value("data").toString());
                    venda.setHora(query.record().value("hora").toString());
                    venda.setValor(query.record().value("valor_venda").toDouble());
                    venda.setFormaPagamento(forma_pagamento);
                    venda.setColaborador(colaborador);

                    // ItemVenda
                    item_venda.setId(query.record().value("id").toInt());
                    item_venda.setQuantidade(query.record().value("quantidade").toDouble());
                    item_venda.setValor(query.record().value("valor").toDouble());
                    item_venda.setVenda(venda);
                    item_venda.setProduto(produto);

                    listaItensVenda.push_back(item_venda);
                } while (query.next());
            }
        } else
            qDebug() << "ItemVendaController::buscaPorIdVenda() query.exec(): " << query.lastError().text();
    }
    conn.close();
    return listaItensVenda;
}


#endif // ITEMVENDACONTROLLER_H
