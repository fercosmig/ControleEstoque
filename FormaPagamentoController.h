#ifndef FORMAPAGAMENTOCONTROLLER_H
#define FORMAPAGAMENTOCONTROLLER_H

#include "Conexao.h"
#include "FormaPagamento.h"

class FormaPagamentoController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

protected:
public:
    // CONSTRUCTOR
    FormaPagamentoController() {}

    // METHODS
    FormaPagamento insere(FormaPagamento forma_pagamento);
    QVector<FormaPagamento> buscaTodos();
    QVector<FormaPagamento> buscaPorDescricao(FormaPagamento forma_pagamento);
    FormaPagamento buscaPorId(FormaPagamento forma_pagamento);
    bool altera(FormaPagamento forma_pagamento);
    bool remove(FormaPagamento forma_pagamento);

};

inline FormaPagamento FormaPagamentoController::insere(FormaPagamento forma_pagamento)
{
    sql = "INSERT INTO tb_formas_pagamento ( descricao ) VALUES ( :descricao )";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()){
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":descricao", forma_pagamento.getDescricao());

        if (query.exec()) {
            sql = "SELECT id, descricao FROM tb_formas_pagamento ORDER BY id DESC LIMIT 1";
            query.prepare(sql);
            if (query.exec()) {
                if (query.next()) {
                    forma_pagamento.setId(query.record().value("id").toInt());
                    forma_pagamento.setDescricao(query.record().value("descricao").toString());
                }
            } else
                qDebug() << "FormaPagamentoController::insere() query.exec(SELECT)" << query.lastError().text();
        } else
            qDebug() << "FormaPagamentoController::insere() query.exec(INSERT)" << query.lastError().text();

        query.exec("COMMIT");
    }
    conn.close();
    return forma_pagamento;
}

inline QVector<FormaPagamento> FormaPagamentoController::buscaTodos()
{
    sql = "SELECT id, descricao ";
    sql += "FROM tb_formas_pagamento ";
    sql += "ORDER BY descricao ASC";

    if (!conn.isOpen())
        conn.open();

    FormaPagamento forma_pagamento;
    QVector<FormaPagamento> listaFormasPagamento;

    if (conn.isOpen()) {

        query.prepare(sql);
        if (query.exec()) {
            if (query.next()) {
                do {
                    forma_pagamento.setId(query.record().value("id").toInt());
                    forma_pagamento.setDescricao(query.record().value("descricao").toString());

                    listaFormasPagamento.push_back(forma_pagamento);
                } while (query.next());
            }
        }else
            qDebug() << "FormaPagamentoController::buscaTodos() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaFormasPagamento;
}

inline QVector<FormaPagamento> FormaPagamentoController::buscaPorDescricao(FormaPagamento forma_pagamento)
{
    sql = "SELECT id, descricao ";
    sql += "FROM tb_formas_pagamento ";
    sql += "WHERE descricao like :descricao ";
    sql += "ORDER BY descricao ASC";

    if (!conn.isOpen())
        conn.open();

    QVector<FormaPagamento> listaFormasPagamento;

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":descricao", "%" + forma_pagamento.getDescricao() + "%");

        if (query.exec()) {
            if (query.next()) {
                do {
                    forma_pagamento.setId(query.record().value("id").toInt());
                    forma_pagamento.setDescricao(query.record().value("descricao").toString());

                    listaFormasPagamento.push_back(forma_pagamento);
                } while (query.next());
            }
        }else
            qDebug() << "FormaPagamentoController::buscaPorDescricao() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaFormasPagamento;
}

inline FormaPagamento FormaPagamentoController::buscaPorId(FormaPagamento forma_pagamento)
{
    sql = "SELECT id, descricao ";
    sql += "FROM tb_formas_pagamento ";
    sql += "WHERE id = :id";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":id", forma_pagamento.getId());

        if (query.exec()) {
            if (query.next()) {
                    forma_pagamento.setId(query.record().value("id").toInt());
                    forma_pagamento.setDescricao(query.record().value("descricao").toString());
            }
        }else
            qDebug() << "FormaPagamentoController::buscaPorId() query.exec: " << query.lastError().text();
    }
    conn.close();
    return forma_pagamento;
}

inline bool FormaPagamentoController::altera(FormaPagamento forma_pagamento)
{
    sql = "UPDATE tb_formas_pagamento SET ";
    sql += "descricao = :descricao ";
    sql += "WHERE id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno  = false;

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":descricao", forma_pagamento.getDescricao());
        query.bindValue(":id", forma_pagamento.getId());

        if (query.exec()) {
            retorno = true;
        }else
            qDebug() << "FormaPagamentoController::altera() query.exec: " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline bool FormaPagamentoController::remove(FormaPagamento forma_pagamento)
{
    sql = "DELETE FROM tb_formas_pagamento ";
    sql += "WHERE id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno  = false;

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":id", forma_pagamento.getId());

        if (query.exec()) {
            retorno = true;
        }else
            qDebug() << "FormaPagamentoController::remove() query.exec: " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

#endif // FORMAPAGAMENTOCONTROLLER_H
