#ifndef VENDACONTROLLER_H
#define VENDACONTROLLER_H

#include <QDebug>
#include <QString>
#include <QVector>
#include <QtSql>
#include "Colaborador.h"
#include "Conexao.h"
#include "FormaPagamento.h"
#include "Grupo.h"
#include "Venda.h"

class VendaController
{
private:
    QString sql;
    Conexao conn;
    QSqlQuery query;

protected:
public:
    // CONSTRUCTOR

    VendaController() {}

    // METHODS CRUD = create, read, update, and delete

    int insere(Venda venda)
    {
        sql = "INSERT INTO tb_vendas (data, hora, valor_total, id_forma_pagamento, id_colaborador) ";
        sql += "VALUES (:data, :hora, :valor_total, :id_forma_pagamento, :id_colaborador)";

        QString sql1 = "SELECT id FROM tb_vendas ORDER BY id DESC LIMIT 1";

        if (!conn.isOpen())
            conn.open();

        int retorno_id_venda = 0;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":data", venda.getData());
            query.bindValue(":hora", venda.getHora());
            query.bindValue(":valor_total", venda.getValorTotal());
            query.bindValue(":id_forma_pagamento", venda.getFormaPagamento().getId());
            query.bindValue(":id_colaborador", venda.getColaborador().getId());

            if (query.exec()) {
                query.prepare(sql1);

                if (query.exec()) {
                    if (query.next())
                        retorno_id_venda = query.record().value("id").toInt();
                    else
                        qDebug() << "VendaController.insere(): Não retornou id da venda.";

                } else
                    qDebug() << "VendaController.insere() query.exec: (sql1)" << query.lastError().text();

            } else
                qDebug() << "VendaController.insere() query.exec: (sql)" << query.lastError().text();
        }

        conn.close();
        return retorno_id_venda;
    }

    QVector<Venda> buscaPorIdColaboradorPeriodo(int id_colaborador, QString data_inicial, QString data_final)
    {
        sql = "SELECT tb_vendas.id, tb_vendas.data, tb_vendas.hora, tb_vendas.valor_total, ";
        sql += "tb_forma_pagamento.id as id_forma_pagamento, tb_forma_pagamento.descricao as descricao_forma_pagamento, ";
        sql += "tb_colaboradores.id as id_colaborador, tb_colaboradores.nome, tb_colaboradores.nome_usuario, ";
        sql += "tb_colaboradores.senha, tb_colaboradores.telefone, tb_grupos.id as id_grupo, tb_grupos.descricao, ";
        sql += "tb_grupos.sigla FROM tb_vendas INNER JOIN tb_forma_pagamento ON tb_vendas.id_forma_pagamento = tb_forma_pagamento.id ";
        sql += "INNER JOIN tb_colaboradores ON tb_vendas.id_colaborador = tb_colaboradores.id ";
        sql += "INNER JOIN tb_grupos ON tb_colaboradores.id_grupo = tb_grupos.id ";
        sql += "WHERE tb_colaboradores.id = :id AND tb_vendas.data BETWEEN :data_inicial AND :data_final";

        if (!conn.isOpen())
            conn.open();

        QVector<Venda> listaVendas;
        Venda venda;
        Colaborador colaborador;
        Grupo grupo;
        FormaPagamento forma_pagamento;

        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":id", id_colaborador);
            query.bindValue(":data_inicial", data_inicial);
            query.bindValue(":data_final", data_final);

            if (query.exec()) {
                if (query.next()) {
                    do {
                        // colaborador precisa de um grupo
                        grupo.setId(query.record().value("id_grupo").toInt());
                        grupo.setDescricao(query.record().value("descricao").toString());
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

                        venda.setId(query.record().value("id").toInt());
                        venda.setData(query.record().value("data").toString());
                        venda.setHora(query.record().value("hora").toString());
                        venda.setValorTotal(query.record().value("valor_total").toDouble());
                        venda.setFormaPagamento(forma_pagamento);
                        venda.setColaborador(colaborador);

                        listaVendas.push_back(venda);
                    } while (query.next());
                } else
                    qDebug() << "VendaController.buscaPorIdColaboradorPeriodo: 0 registros";
            } else
                qDebug() << "VendaController.buscaPorIdColaboradorPeriodo() query.exec: " << query.lastError().text();
        }

        conn.close();
        return listaVendas;
    }

    QVector<Venda> buscaTodasPeriodo(QString data_inicial, QString data_final)
    {
        sql = "SELECT tb_vendas.id, tb_vendas.data, tb_vendas.hora, tb_vendas.valor_total, ";
        sql += "tb_forma_pagamento.id as id_forma_pagamento, tb_forma_pagamento.descricao as descricao_forma_pagamento, ";
        sql += "tb_colaboradores.id as id_colaborador, tb_colaboradores.nome, tb_colaboradores.nome_usuario, ";
        sql += "tb_colaboradores.senha, tb_colaboradores.telefone, tb_grupos.id as id_grupo, tb_grupos.descricao, ";
        sql += "tb_grupos.sigla FROM tb_vendas INNER JOIN tb_forma_pagamento ON tb_vendas.id_forma_pagamento = tb_forma_pagamento.id ";
        sql += "INNER JOIN tb_colaboradores ON tb_vendas.id_colaborador = tb_colaboradores.id ";
        sql += "INNER JOIN tb_grupos ON tb_colaboradores.id_grupo = tb_grupos.id ";
        sql += "WHERE tb_vendas.data BETWEEN :data_inicial AND :data_final";

        if (!conn.isOpen())
            conn.open();

        QVector<Venda> listaVendas;
        Venda venda;
        Colaborador colaborador;
        Grupo grupo;
        FormaPagamento forma_pagamento;

        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":data_inicial", data_inicial);
            query.bindValue(":data_final", data_final);

            if (query.exec()) {
                if (query.next()) {
                    do {
                        // colaborador precisa de um grupo
                        grupo.setId(query.record().value("id_grupo").toInt());
                        grupo.setDescricao(query.record().value("descricao").toString());
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

                        venda.setId(query.record().value("id").toInt());
                        venda.setData(query.record().value("data").toString());
                        venda.setHora(query.record().value("hora").toString());
                        venda.setValorTotal(query.record().value("valor_total").toDouble());
                        venda.setFormaPagamento(forma_pagamento);
                        venda.setColaborador(colaborador);

                        listaVendas.push_back(venda);
                    } while (query.next());
                } else
                    qDebug() << "VendaController.buscaTodas: 0 registros";
            } else
                qDebug() << "VendaController.buscaTodas() query.exec: " << query.lastError().text();
        }

        conn.close();
        return listaVendas;
    }

    Venda buscaPorId(int id)
    {
        sql = "SELECT tb_vendas.id, tb_vendas.data, tb_vendas.hora, tb_vendas.valor_total, ";
        sql += "tb_forma_pagamento.id as id_forma_pagamento, tb_forma_pagamento.descricao as descricao_forma_pagamento, ";
        sql += "tb_colaboradores.id as id_colaborador, tb_colaboradores.nome, tb_colaboradores.nome_usuario, ";
        sql += "tb_colaboradores.senha, tb_colaboradores.telefone, tb_grupos.id as id_grupo, tb_grupos.descricao, ";
        sql += "tb_grupos.sigla FROM tb_vendas INNER JOIN tb_forma_pagamento ON tb_vendas.id_forma_pagamento = tb_forma_pagamento.id ";
        sql += "INNER JOIN tb_colaboradores ON tb_vendas.id_colaborador = tb_colaboradores.id ";
        sql += "INNER JOIN tb_grupos ON tb_colaboradores.id_grupo = tb_grupos.id ";
        sql += "WHERE tb_vendas.id = :id";

        if (!conn.isOpen())
            conn.open();

        Venda venda;
        Colaborador colaborador;
        Grupo grupo;
        FormaPagamento forma_pagamento;

        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":id", id);

            if (query.exec()) {
                if (query.next()) {
                    // colaborador precisa de um grupo
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setDescricao(query.record().value("descricao").toString());
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

                    venda.setId(query.record().value("id").toInt());
                    venda.setData(query.record().value("data").toString());
                    venda.setHora(query.record().value("hora").toString());
                    venda.setValorTotal(query.record().value("valor_total").toDouble());
                    venda.setFormaPagamento(forma_pagamento);
                    venda.setColaborador(colaborador);
                } else
                    qDebug() << "VendaController.buscaPorId: 0 registros";
            } else
                qDebug() << "VendaController.buscaPorId() query.exec: " << query.lastError().text();
        }

        conn.close();
        return venda;
    }
};

#endif // VENDACONTROLLER_H
