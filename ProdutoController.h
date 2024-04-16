#ifndef PRODUTOCONTROLLER_H
#define PRODUTOCONTROLLER_H

#include "Conexao.h"
#include "Produto.h"
#include "Fornecedor.h"

class ProdutoController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

protected:
public:
    // CONSTRUCTOR
    ProdutoController() {}

    // METHODS CRUD - CREATE / READ / UPDATE / DELETE
    bool insere(Produto produto);
    QVector<Produto> buscaTodos();
    QVector<Produto> buscaPorDescricao(Produto produto);
    Produto buscaPorId(Produto produto);
    bool verificaDuplicidadeId(Produto produto);
    bool altera(Produto produto);
    bool remove(Produto produto);
};

inline bool ProdutoController::insere(Produto produto)
{
    sql = "INSERT INTO tb_produtos ";
    sql += "( id, descricao, quantidade, custo, valor, id_fornecedor ) ";
    sql += "VALUES ";
    sql += "( :id, :descricao, :quantidade, :custo, :valor, :id_fornecedor )";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":id", produto.getId());
        query.bindValue(":descricao", produto.getDescricao());
        query.bindValue(":quantidade", QString::number(produto.getQuantidade()));
        query.bindValue(":custo", QString::number(produto.getCusto()));
        query.bindValue(":valor", QString::number(produto.getValor()));
        query.bindValue(":id_fornecedor", QString::number(produto.getFornecedor().getId()));

        if (query.exec())
            retorno = true;
        else
            qDebug() << "ProdutoController::insere() query.exec(): " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline QVector<Produto> ProdutoController::buscaTodos()
{
    sql = "SELECT ";
    sql += "tb_produtos.id, ";
    sql += "tb_produtos.descricao, ";
    sql += "tb_produtos.quantidade, ";
    sql += "tb_produtos.custo, ";
    sql += "tb_produtos.valor, ";
    sql += "tb_fornecedores.id AS id_fornecedor, ";
    sql += "tb_fornecedores.razao_social, ";
    sql += "tb_fornecedores.nome_fantasia ";
    sql += "FROM tb_produtos ";
    sql += "INNER JOIN tb_fornecedores ";
    sql += "ON tb_produtos.id_fornecedor = tb_fornecedores.id ";
    sql += "ORDER BY tb_produtos.descricao ASC";

    if (!conn.isOpen())
        conn.open();

    Produto produto;
    Fornecedor fornecedor;
    QVector<Produto> listaProdutos;

    if (conn.isOpen()) {
        query.prepare(sql);
        if (query.exec()) {
            if (query.next()) {
                do {
                    fornecedor.setId(query.record().value("id_fornecedor").toInt());
                    fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                    fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());

                    produto.setId(query.record().value("id").toString());
                    produto.setDescricao(query.record().value("descricao").toString());
                    produto.setQuantidade(query.record().value("quantidade").toDouble());
                    produto.setCusto(query.record().value("custo").toDouble());
                    produto.setValor(query.record().value("valor").toDouble());
                    produto.setFornecedor(fornecedor);

                    listaProdutos.push_back(produto);
                } while (query.next());
            }
        } else
            qDebug() << "ProdutoController::buscaTodos() query.exec(): " << query.lastError().text();
    }
    conn.close();
    return listaProdutos;
}

inline QVector<Produto> ProdutoController::buscaPorDescricao(Produto produto)
{
    sql = "SELECT ";
    sql += "tb_produtos.id, ";
    sql += "tb_produtos.descricao, ";
    sql += "tb_produtos.quantidade, ";
    sql += "tb_produtos.custo, ";
    sql += "tb_produtos.valor, ";
    sql += "tb_fornecedores.id AS id_fornecedor, ";
    sql += "tb_fornecedores.razao_social, ";
    sql += "tb_fornecedores.nome_fantasia ";
    sql += "FROM tb_produtos ";
    sql += "INNER JOIN tb_fornecedores ";
    sql += "ON tb_produtos.id_fornecedor = tb_fornecedores.id ";
    sql += "WHERE tb_produtos.descricao LIKE :descricao ";
    sql += "ORDER BY tb_produtos.descricao ASC";

    if (!conn.isOpen())
        conn.open();

    Fornecedor fornecedor;
    QVector<Produto> listaProdutos;

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":descricao", "%" + produto.getDescricao() + "%");
        if (query.exec()) {
            if (query.next()) {
                do {
                    fornecedor.setId(query.record().value("id_fornecedor").toInt());
                    fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                    fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());

                    produto.setId(query.record().value("id").toString());
                    produto.setDescricao(query.record().value("descricao").toString());
                    produto.setQuantidade(query.record().value("quantidade").toDouble());
                    produto.setCusto(query.record().value("custo").toDouble());
                    produto.setValor(query.record().value("valor").toDouble());
                    produto.setFornecedor(fornecedor);

                    listaProdutos.push_back(produto);
                } while (query.next());
            }
        } else
            qDebug() << "ProdutoController::buscaPorDescricao() query.exec(): " << query.lastError().text();
    }
    conn.close();
    return listaProdutos;
}

inline Produto ProdutoController::buscaPorId(Produto produto)
{
    sql = "SELECT ";
    sql += "tb_produtos.id, ";
    sql += "tb_produtos.descricao, ";
    sql += "tb_produtos.quantidade, ";
    sql += "tb_produtos.custo, ";
    sql += "tb_produtos.valor, ";
    sql += "tb_fornecedores.id AS id_fornecedor, ";
    sql += "tb_fornecedores.razao_social, ";
    sql += "tb_fornecedores.nome_fantasia ";
    sql += "FROM tb_produtos ";
    sql += "INNER JOIN tb_fornecedores ";
    sql += "ON tb_produtos.id_fornecedor = tb_fornecedores.id ";
    sql += "WHERE tb_produtos.id = :id ";

    if (!conn.isOpen())
        conn.open();

    Fornecedor fornecedor;

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":id", produto.getId());
        if (query.exec()) {
            if (query.next()) {
                    fornecedor.setId(query.record().value("id_fornecedor").toInt());
                    fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                    fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());

                    produto.setId(query.record().value("id").toString());
                    produto.setDescricao(query.record().value("descricao").toString());
                    produto.setQuantidade(query.record().value("quantidade").toDouble());
                    produto.setCusto(query.record().value("custo").toDouble());
                    produto.setValor(query.record().value("valor").toDouble());
                    produto.setFornecedor(fornecedor);
            } else
                produto.setId("0");
        } else
            qDebug() << "ProdutoController::buscaPorDescricao() query.exec(): " << query.lastError().text();
    }
    conn.close();
    return produto;
}

inline bool ProdutoController::verificaDuplicidadeId(Produto produto)
{
    sql = "SELECT id ";
    sql += "FROM tb_produtos ";
    sql += "WHERE id = :id ";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":id", produto.getId());

        if (query.exec()) {
            if (query.next())
                retorno = true;
        } else
            qDebug() << "ProdutoController::verificaDuplicidadeId() query.exec(): " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline bool ProdutoController::altera(Produto produto)
{
    sql = "UPDATE tb_produtos SET ";
    sql += "descricao = :descricao, ";
    sql += "quantidade = :quantidade, ";
    sql += "custo = :custo, ";
    sql += "valor = :valor, ";
    sql += "id_fornecedor = :id_fornecedor ";
    sql += "WHERE id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":descricao", produto.getDescricao());
        query.bindValue(":quantidade", QString::number(produto.getQuantidade()));
        query.bindValue(":custo", QString::number(produto.getCusto()));
        query.bindValue(":valor", QString::number(produto.getValor()));
        query.bindValue(":id_fornecedor", QString::number(produto.getFornecedor().getId()));
        query.bindValue(":id", produto.getId());

        if (query.exec())
            retorno = true;
        else
            qDebug() << "ProdutoController::altera() query.exec(): " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline bool ProdutoController::remove(Produto produto)
{
    sql = "DELETE FROM tb_produtos WHERE id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()) {
        query.prepare(sql);
        query.bindValue(":id", produto.getId());

        if (query.exec())
            retorno = true;
        else
            qDebug() << "ProdutoController::remove() query.exec(): " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

#endif // PRODUTOCONTROLLER_H
