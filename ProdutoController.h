#ifndef PRODUTOCONTROLLER_H
#define PRODUTOCONTROLLER_H

#include <QDebug>
#include <QString>
#include <QtSql>
#include "Conexao.h"
#include "Fornecedor.h"
#include "Produto.h"

class ProdutoController
{
private:
    QString sql;
    Conexao conn;
    QSqlQuery query;

protected:
public:
    // CONSTRUCTOR

    ProdutoController() {}

    // METHODS CRUD = create, read, update, and delete

    bool insere(Produto produto)
    {
        sql = "INSERT INTO tb_produtos (id, descricao, quantidade, valor_compra, valor_venda, id_fornecedor) ";
        sql += "VALUES (:id, :descricao, :quantidade, :valor_compra, :valor_venda, :id_fornecedor)";

        if (!conn.isOpen())
            conn.open();

        bool retorno = false;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":id", produto.getId());
            query.bindValue(":descricao", produto.getDescricao());
            query.bindValue(":quantidade", produto.getQuantidade());
            query.bindValue(":valor_compra", produto.getValorCompra());
            query.bindValue(":valor_venda", produto.getValorVenda());
            query.bindValue(":id_fornecedor", produto.getFornecedor().getId());

            if (query.exec())
                retorno = true;
            else
                qDebug() << "ProdutoController.insere() query.exec: " << query.lastError().text();
        }

        conn.close();
        return retorno;
    }

    Produto buscaPorId(int id)
    {
        sql = "SELECT ";
        sql+= "tb_produtos.id, tb_produtos.descricao, tb_produtos.quantidade, tb_produtos.valor_compra, tb_produtos.valor_venda, ";
        sql+= "tb_fornecedores.id as id_fornecedor, tb_fornecedores.razao_social, tb_fornecedores.nome_fantasia ";
        sql+= "FROM tb_produtos ";
        sql+= "INNER JOIN tb_fornecedores ON tb_produtos.id_fornecedor = tb_fornecedores.id ";
        sql+= "WHERE tb_produtos.id = :id";

        if (!conn.isOpen())
            conn.open();

        Produto produto;
        Fornecedor fornecedor;

        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":id", id);

            if (query.exec()) {
                if (query.next()) {
                    // produto precisa de um fornecedor
                    fornecedor.setId(query.record().value("id_fornecedor").toInt());
                    fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                    fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());

                    produto.setId(query.record().value("id").toInt());
                    produto.setDescricao(query.record().value("descricao").toString());
                    produto.setQuantidade(query.record().value("quantidade").toInt());
                    produto.setValorCompra(query.record().value("valor_compra").toDouble());
                    produto.setValorVenda(query.record().value("valor_venda").toDouble());
                    produto.setFornecedor(fornecedor);
                } else {
                    qDebug() << "ProdutoController.buscaPorId: 0 registros";
                    produto.setId(0);
                }

            } else
                qDebug() << "ProdutoController.buscaPorId() query.exec: " << query.lastError().text();
        }

        conn.close();
        return produto;
    }

    QVector<Produto> buscaPorDescricao(QString descricao)
    {
        sql = "SELECT ";
        sql+= "tb_produtos.id, tb_produtos.descricao, tb_produtos.quantidade, tb_produtos.valor_compra, tb_produtos.valor_venda, ";
        sql+= "tb_fornecedores.id as id_fornecedor, tb_fornecedores.razao_social, tb_fornecedores.nome_fantasia ";
        sql+= "FROM tb_produtos ";
        sql+= "INNER JOIN tb_fornecedores ON tb_produtos.id_fornecedor = tb_fornecedores.id ";
        sql+= "WHERE tb_produtos.descricao like :descricao ";
        sql+= "ORDER BY tb_produtos.descricao ASC";

        if (!conn.isOpen())
            conn.open();

        QVector<Produto> listaProdutos;
        Produto produto;
        Fornecedor fornecedor;

        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":descricao", "%" + descricao + "%");

            if (query.exec()) {
                if (query.next()) {
                    do {
                        // produto precisa de um fornecedor
                        fornecedor.setId(query.record().value("id_fornecedor").toInt());
                        fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                        fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());

                        produto.setId(query.record().value("id").toInt());
                        produto.setDescricao(query.record().value("descricao").toString());
                        produto.setQuantidade(query.record().value("quantidade").toInt());
                        produto.setValorCompra(query.record().value("valor_compra").toDouble());
                        produto.setValorVenda(query.record().value("valor_venda").toDouble());
                        produto.setFornecedor(fornecedor);

                        listaProdutos.push_back(produto);
                    } while (query.next());
                } else
                    qDebug() << "ProdutoController.buscaPorDescricao: 0 registros";

            } else
                qDebug() << "ProdutoController.buscaPorDescricao() query.exec: " << query.lastError().text();
        }

        conn.close();
        return listaProdutos;
    }

    QVector<Produto> buscaTodos()
    {
        sql = "SELECT ";
        sql+= "tb_produtos.id, tb_produtos.descricao, tb_produtos.quantidade, tb_produtos.valor_compra, tb_produtos.valor_venda, ";
        sql+= "tb_fornecedores.id as id_fornecedor, tb_fornecedores.razao_social, tb_fornecedores.nome_fantasia ";
        sql+= "FROM tb_produtos ";
        sql+= "INNER JOIN tb_fornecedores ON tb_produtos.id_fornecedor = tb_fornecedores.id ";
        sql+= "ORDER BY tb_produtos.descricao ASC";

        if (!conn.isOpen())
            conn.open();

        QVector<Produto> listaProdutos;
        Produto produto;
        Fornecedor fornecedor;

        if (conn.isOpen()) {
            query.prepare(sql);
            if (query.exec()) {
                if (query.next()) {
                    do {
                        // produto precisa de um fornecedor
                        fornecedor.setId(query.record().value("id_fornecedor").toInt());
                        fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                        fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());

                        produto.setId(query.record().value("id").toInt());
                        produto.setDescricao(query.record().value("descricao").toString());
                        produto.setQuantidade(query.record().value("quantidade").toInt());
                        produto.setValorCompra(query.record().value("valor_compra").toDouble());
                        produto.setValorVenda(query.record().value("valor_venda").toDouble());
                        produto.setFornecedor(fornecedor);

                        listaProdutos.push_back(produto);
                    } while (query.next());
                } else
                    qDebug() << "ProdutoController.buscaTodos: 0 registros";

            } else
                qDebug() << "ProdutoController.buscaTodos() query.exec: " << query.lastError().text();
        }

        conn.close();
        return listaProdutos;
    }

    int buscaIdDuplicado(int id)
    {
        sql = "SELECT id FROM tb_produtos WHERE id = :id";

        if (!conn.isOpen())
            conn.open();

        int retorno = 0;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":id", id);

            if (query.exec()) {
                if (query.next()) {
                    retorno = query.value(0).toInt();
                    qDebug() << "ProdutoController.buscaIdDuplicado: duplicado";
                }

            } else
                qDebug() << "ProdutoController.buscaIdDuplicado() query.exec: " << query.lastError().text();
        }

        conn.close();
        return retorno;
    }

    bool altera(Produto produto)
    {
        sql = "UPDATE tb_produtos ";
        sql+= "SET descricao = :descricao, quantidade = :quantidade, valor_compra = :valor_compra, ";
        sql+= "valor_venda = :valor_venda, id_fornecedor = :id_fornecedor WHERE id = :id";

        if (!conn.isOpen())
            conn.open();

        bool retorno = false;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":descricao", produto.getDescricao());
            query.bindValue(":quantidade", produto.getQuantidade());
            query.bindValue(":valor_compra", produto.getValorCompra());
            query.bindValue(":valor_venda", produto.getValorVenda());
            query.bindValue(":id_fornecedor", produto.getFornecedor().getId());
            query.bindValue(":id", produto.getId());

            if (query.exec())
                retorno = true;
            else
                qDebug() << "ProdutoController.altera() query.exec: " << query.lastError().text();
        }

        conn.close();
        return retorno;
    }

    bool remove(QString id)
    {
        sql = "DELETE FROM tb_produtos WHERE id = :id";

        if (!conn.isOpen())
            conn.open();

        bool retorno = false;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":id", id);

            if (query.exec())
                retorno = true;
            else
                qDebug() << "ProdutoController.remove() query.exec: " << query.lastError().text();
        }

        conn.close();
        return retorno;
    }
};

#endif // PRODUTOCONTROLLER_H
