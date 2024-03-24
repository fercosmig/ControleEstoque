#ifndef ITEMVENDACONTROLLER_H
#define ITEMVENDACONTROLLER_H

#include <QDebug>
#include <QString>
#include <QVector>
#include "Colaborador.h"
#include "Conexao.h"
#include "FormaPagamento.h"
#include "Grupo.h"
#include "ItemVenda.h"
#include "Produto.h"
#include "Venda.h"

class ItemVendaController
{
private:
    QString sql;
    Conexao conn;
    QSqlQuery query;

protected:
public:
    // CONSTRUCTOR

    ItemVendaController() {}

    // METHODS CRUD = create, read, update, and delete

    void insere(ItemVenda item_venda)
    {
        sql = "INSERT INTO tb_itens_venda (quantidade, valor_venda, id_venda, id_produto) VALUES "
              "(:quantidade, :valor_venda, :id_venda, :id_produto)";

        if (!conn.isOpen())
            conn.open();

        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":quantidade", item_venda.getQuantidade());
            query.bindValue(":valor_venda", item_venda.getValorVenda());
            query.bindValue(":id_venda", item_venda.getVenda().getId());
            query.bindValue(":id_produto", item_venda.getProduto().getId());

            if (!query.exec())
                qDebug() << "ItemVendaController.insere() query.exec: " << query.lastError().text();
        }

        conn.close();
    }

    QVector<ItemVenda> buscaPorIdVenda(int id_venda)
    {
        sql = "SELECT tb_itens_venda.id, ";
        sql += "tb_itens_venda.quantidade, ";
        sql += "tb_itens_venda.valor_venda, ";
        sql += "tb_vendas.id as id_venda, ";
        sql += "tb_vendas.data, ";
        sql += "tb_vendas.hora, ";
        sql += "tb_vendas.valor_total, ";
        sql += "tb_forma_pagamento.id as id_forma_pagamento, ";
        sql += "tb_forma_pagamento.descricao as descricao_forma_pagamento, ";
        sql += "tb_colaboradores.id as id_colaborador, ";
        sql += "tb_colaboradores.nome, ";
        sql += "tb_colaboradores.nome_usuario, ";
        sql += "tb_colaboradores.senha, ";
        sql += "tb_colaboradores.telefone, ";
        sql += "tb_grupos.id as id_grupo, ";
        sql += "tb_grupos.descricao as descricao_grupo, ";
        sql += "tb_grupos.sigla, ";
        sql += "tb_produtos.id as id_produto, ";
        sql += "tb_produtos.descricao as descricao_produto, ";
        sql += "tb_produtos.quantidade as quantidade_produto, ";
        sql += "tb_produtos.valor_compra, ";
        sql += "tb_produtos.valor_venda as valor_venda_produto, ";
        sql += "tb_fornecedores.id as id_fornecedor, ";
        sql += "tb_fornecedores.razao_social, ";
        sql += "tb_fornecedores.nome_fantasia ";
        sql += "FROM tb_itens_venda ";
        sql += "INNER JOIN tb_vendas ON tb_itens_venda.id_venda = tb_vendas.id ";
        sql += "INNER JOIN tb_forma_pagamento ON tb_vendas.id_forma_pagamento = tb_forma_pagamento.id ";
        sql += "INNER JOIN tb_colaboradores ON tb_vendas.id_colaborador = tb_colaboradores.id ";
        sql += "INNER JOIN tb_grupos ON tb_colaboradores.id_grupo = tb_grupos.id ";
        sql += "INNER JOIN tb_produtos ON tb_itens_venda.id_produto = tb_produtos.id ";
        sql += "INNER JOIN tb_fornecedores ON tb_produtos.id_fornecedor = tb_fornecedores.id ";
        sql += "WHERE tb_vendas.id = :id_venda";

        if (!conn.isOpen())
            conn.open();

        QVector<ItemVenda> listaItensVenda;
        ItemVenda item_venda;
        Venda venda;
        Colaborador colaborador;
        Grupo grupo;
        FormaPagamento forma_pagamento;
        Produto produto;
        Fornecedor fornecedor;

        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":id_venda", id_venda);

            if (query.exec()) {
                if (query.next()) {
                    do {
                        // produto precisa de um fornecedor
                        fornecedor.setId(query.record().value("id_fornecedor").toInt());
                        fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                        fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());

                        // item_venda precisa de um produto
                        produto.setId(query.record().value("id_produto").toInt());
                        produto.setDescricao(query.record().value("descricao_produto").toString());
                        produto.setQuantidade(query.record().value("quantidade_produto").toInt());
                        produto.setValorCompra(query.record().value("valor_compra").toDouble());
                        produto.setValorVenda(query.record().value("valor_venda_produto").toDouble());
                        produto.setFornecedor(fornecedor);

                        // colaborador precisa de um grupo
                        grupo.setId(query.record().value("id_grupo").toInt());
                        grupo.setDescricao(query.record().value("descricao_grupo").toString());
                        grupo.setSigla(query.record().value("sigla").toString());

                        // venda precisa de um colaborador
                        colaborador.setId(query.record().value("id_colaborador").toInt());
                        colaborador.setNome(query.record().value("nome").toString());
                        colaborador.setNomeUsuario(query.record().value("nome_usuario").toString());
                        colaborador.setSenha(query.record().value("senha").toString());
                        colaborador.setTelefone(query.record().value("telefone").toString());
                        colaborador.setGrupo(grupo);

                        // venda precisa de uma forma_pagamento
                        forma_pagamento.setId(query.record().value("id_forma_pagamento").toInt());
                        forma_pagamento.setDescricao(query.record().value("descricao_forma_pagamento").toString());

                        // item_venda precisa de uma venda
                        venda.setId(query.record().value("id_venda").toInt());
                        venda.setData(query.record().value("data").toString());
                        venda.setHora(query.record().value("hora").toString());
                        venda.setValorTotal(query.record().value("valor_total").toDouble());
                        venda.setColaborador(colaborador);
                        venda.setFormaPagamento(forma_pagamento);

                        // item_venda
                        item_venda.setId(query.record().value("id").toInt());
                        item_venda.setQuantidade(query.record().value("quantidade").toInt());
                        item_venda.setValorVenda(query.record().value("valor_venda").toInt());
                        item_venda.setVenda(venda);
                        item_venda.setProduto(produto);

                        listaItensVenda.push_back(item_venda);
                    } while (query.next());
                } else
                    qDebug() << "ItemVendaController.pesquisarIdVenda: 0 registros";

            } else
                qDebug() << "ItemVendaController.pesquisarIdVenda() query.exec: " << query.lastError().text();
        }

        conn.close();
        return listaItensVenda;
    }
};

#endif // ITEMVENDACONTROLLER_H
