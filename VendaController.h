#ifndef VENDACONTROLLER_H
#define VENDACONTROLLER_H

#include "Conexao.h"
#include "Venda.h"

class VendaController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

protected:
public:
    // CONSTRUCTOR
    VendaController() {}

    // METHODS
    Venda insere(Venda venda);
    //Venda buscaPorId(int id);
    //QVector<Venda> buscaPorIdColaboradorPeriodo(int id_colaborador, QString data_inicial, QString data_final);
    QVector<Venda> buscaPorPeriodo(QString data_inicial, QString data_final);
};

inline Venda VendaController::insere(Venda venda)
{
    sql = "INSERT INTO tb_vendas ( valor, id_forma_pagamento, id_colaborador ) ";
    sql += "VALUES ( :valor, :id_forma_pagamento, :id_colaborador )";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()) {
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":valor", venda.getValor());
        query.bindValue(":id_forma_pagamento", venda.getFormaPagamento().getId());
        query.bindValue(":id_colaborador", venda.getColaborador().getId());

        if (query.exec()) {
            sql = "SELECT id, data, hora FROM tb_vendas ORDER BY id DESC LIMIT 1";
            query.prepare(sql);
            if(query.exec()) {
                if (query.next()) {
                    venda.setId(query.record().value("id").toInt());
                    venda.setData(query.record().value("data").toString());
                    venda.setHora(query.record().value("hora").toString());
                }
            } else
                qDebug() << "Venda VendaController::insere() query.exec(SELECT): " << query.lastError().text();
        } else
            qDebug() << "Venda VendaController::insere() query.exec(INSERT): " << query.lastError().text();

        query.exec("COMMIT");
    }
    conn.close();
    return venda;
}

// inline Venda VendaController::buscaPorId(int id)
// {
//     sql = "SELECT ";
//     sql += "tb_vendas.id, ";
//     sql += "tb_vendas.data, ";
//     sql += "tb_vendas.hora, ";
//     sql += "tb_vendas.valor, ";
//     sql += "tb_formas_pagamento.id AS id_forma_pagamento, ";
//     sql += "tb_formas_pagamento.descricao AS descricao_forma_pagamento, ";
//     sql += "tb_colaboradores.id AS id_colaborador, ";
//     sql += "tb_colaboradores.nome, ";
//     sql += "tb_colaboradores.email, ";
//     sql += "tb_colaboradores.senha, ";
//     sql += "tb_grupos.id AS id_grupo, ";
//     sql += "tb_grupos.descricao AS descricao_grupo, ";
//     sql += "tb_grupos.sigla ";
//     sql += "FROM tb_vendas ";
//     sql += "INNER JOIN tb_formas_pagamento ";
//     sql += "ON tb_vendas.id_forma_pagamento = tb_formas_pagamento.id ";
//     sql += "INNER JOIN tb_colaboradores ";
//     sql += "ON tb_vendas.id_colaborador = tb_colaboradores.id ";
//     sql += "INNER JOIN tb_grupos ";
//     sql += "ON tb_colaboradores.id_grupo = tb_grupos.id ";
//     sql += "WHERE tb_vendas.id = :id";
// }
// inline QVector<Venda> VendaController::buscaPorIdColaboradorPeriodo(int id_colaborador, QString data_inicial, QString data_final)
// {
//     sql = "SELECT ";
//     sql += "tb_vendas.id, ";
//     sql += "tb_vendas.data, ";
//     sql += "tb_vendas.hora, ";
//     sql += "tb_vendas.valor, ";
//     sql += "tb_formas_pagamento.id AS id_forma_pagamento, ";
//     sql += "tb_formas_pagamento.descricao AS descricao_forma_pagamento, ";
//     sql += "tb_colaboradores.id AS id_colaborador, ";
//     sql += "tb_colaboradores.nome, ";
//     sql += "tb_colaboradores.email, ";
//     sql += "tb_colaboradores.senha, ";
//     sql += "tb_grupos.id AS id_grupo, ";
//     sql += "tb_grupos.descricao AS descricao_grupo, ";
//     sql += "tb_grupos.sigla ";
//     sql += "FROM tb_vendas ";
//     sql += "INNER JOIN tb_formas_pagamento ";
//     sql += "ON tb_vendas.id_forma_pagamento = tb_formas_pagamento.id ";
//     sql += "INNER JOIN tb_colaboradores ";
//     sql += "ON tb_vendas.id_colaborador = tb_colaboradores.id ";
//     sql += "INNER JOIN tb_grupos ";
//     sql += "ON tb_colaboradores.id_grupo = tb_grupos.id ";
//     sql += "WHERE ";
//     sql += "tb_vendas.id_colaborador = :id_colaborador AND ";
//     sql += "tb_vendas.data BETWEEN :data_inicial AND :data_final";
// }

inline QVector<Venda> VendaController::buscaPorPeriodo(QString data_inicial, QString data_final)
{
    sql = "SELECT ";
    sql += "tb_vendas.id, ";
    sql += "tb_vendas.data, ";
    sql += "tb_vendas.hora, ";
    sql += "tb_vendas.valor, ";
    sql += "tb_formas_pagamento.id AS id_forma_pagamento, ";
    sql += "tb_formas_pagamento.descricao AS descricao_forma_pagamento, ";
    sql += "tb_colaboradores.id AS id_colaborador, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.email, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id AS id_grupo, ";
    sql += "tb_grupos.descricao AS descricao_grupo, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM tb_vendas ";
    sql += "INNER JOIN tb_formas_pagamento ";
    sql += "ON tb_vendas.id_forma_pagamento = tb_formas_pagamento.id ";
    sql += "INNER JOIN tb_colaboradores ";
    sql += "ON tb_vendas.id_colaborador = tb_colaboradores.id ";
    sql += "INNER JOIN tb_grupos ";
    sql += "ON tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "WHERE ";
    sql += "tb_vendas.data BETWEEN :data_inicial AND :data_final";

    if (!conn.isOpen())
        conn.open();

    Venda venda;
    FormaPagamento forma_pagamento;
    Colaborador colaborador;
    Grupo grupo;
    QVector<Venda> listaVendas;

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":data_inicial", data_inicial);
        query.bindValue(":data_final", data_final);

        if (query.exec()) {
            if (query.next()) {
                do {
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setDescricao(query.record().value("descricao_grupo").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    colaborador.setId(query.record().value("id_colaborador").toInt());
                    colaborador.setNome(query.record().value("nome").toString());
                    colaborador.setEmail(query.record().value("email").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setGrupo(grupo);

                    forma_pagamento.setId(query.record().value("id_forma_pagamento").toInt());
                    forma_pagamento.setDescricao(query.record().value("descricao_forma_pagamento").toString());

                    venda.setId(query.record().value("id").toInt());
                    venda.setData(query.record().value("data").toString());
                    venda.setHora(query.record().value("hora").toString());
                    venda.setValor(query.record().value("valor").toDouble());
                    venda.setFormaPagamento(forma_pagamento);
                    venda.setColaborador(colaborador);

                    listaVendas.push_back(venda);
                } while (query.next());
            }
        } else
            qDebug() << "VendaController::buscaPorPeriodo() query.exec(): " << query.lastError().text();
    }
    conn.close();
    return listaVendas;
}

#endif // VENDACONTROLLER_H
