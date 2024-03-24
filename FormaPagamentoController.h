#ifndef FORMAPAGAMENTOCONTROLLER_H
#define FORMAPAGAMENTOCONTROLLER_H

#include <QDebug>
#include <QString>
#include <QVector>
#include "Conexao.h"
#include "FormaPagamento.h"

class FormaPagamentoController
{
private:
    QString sql;
    Conexao conn;
    QSqlQuery query;

protected:
public:
    // CONSTRUCTOR

    FormaPagamentoController() {}

    //METHODS CRUD = create, read, update, and delete

    bool insere(FormaPagamento forma_pagamento)
    {
        sql = "INSERT INTO tb_forma_pagamento (descricao) VALUES (:descricao)";

        if (!conn.isOpen())
            conn.open();

        bool retorno = false;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":descricao", forma_pagamento.getDescricao());

            if (query.exec())
                retorno = true;
            else {
                qDebug() << "FormaPagamentoController.insere()";
                qDebug() << "query.exec: " << query.lastError().text();
            }
        }

        conn.close();
        return retorno;
    }

    QVector<FormaPagamento> buscaTodos()
    {
        sql = "SELECT id, descricao FROM tb_forma_pagamento ORDER BY descricao ASC";

        if (!conn.isOpen())
            conn.open();

        QVector<FormaPagamento> listaFormaPagamento;
        FormaPagamento forma_pagamento;
        if (conn.isOpen()) {
            query.prepare(sql);

            if (query.exec()) {
                if (query.next()) {
                    do {
                        forma_pagamento.setId(query.record().value("id").toInt());
                        forma_pagamento.setDescricao(query.record().value("descricao").toString());
                        listaFormaPagamento.push_back(forma_pagamento);
                    } while (query.next());
                } else
                    qDebug() << "FormaPagamentoController.buscaTodos: 0 registros";

            } else
                qDebug() << "FormaPagamentoController.buscaTodos() query.exec: " << query.lastError().text();
        }

        conn.close();
        return listaFormaPagamento;
    }

    FormaPagamento buscaPorId(int id)
    {
        sql = "SELECT id, descricao FROM tb_forma_pagamento WHERE id = :id";

        if (!conn.isOpen())
            conn.open();

        FormaPagamento forma_pagamento;

        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":id", id);

            if (query.exec()) {
                if (query.next()) {
                    forma_pagamento.setId(query.record().value("id").toInt());
                    forma_pagamento.setDescricao(query.record().value("descricao").toString());
                } else
                    qDebug() << "FormaPagamentoController.buscaPorId: 0 registros";

            } else
                qDebug() << "FormaPagamentoController.buscaPorId() query.exec: " << query.lastError().text();
        }

        conn.close();
        return forma_pagamento;
    }

    QVector<FormaPagamento> buscaPorDescricao(QString descricao)
    {
        sql = "SELECT id, descricao FROM tb_forma_pagamento WHERE descricao LIKE "
              ":descricao ORDER BY descricao ASC ";

        if (!conn.isOpen())
            conn.open();

        QVector<FormaPagamento> listaFormaPagamento;
        FormaPagamento forma_pagamento;

        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":descricao", "%" + descricao + "%");

            if (query.exec()) {
                if (query.next()) {
                    do {
                        forma_pagamento.setId(query.value(0).toInt());
                        forma_pagamento.setDescricao(query.value(1).toString());
                        listaFormaPagamento.push_back(forma_pagamento);
                    } while (query.next());
                } else
                    qDebug() << "FormaPagamentoController.buscaPorDescricao: 0 registros";

            } else
                qDebug() << "FormaPagamentoController.buscaPorDescricao() query.exec: " << query.lastError().text();
        }

        conn.close();
        return listaFormaPagamento;
    }
    bool altera(FormaPagamento forma_pagamento)
    {
        sql = "UPDATE tb_forma_pagamento SET descricao = :descricao WHERE id = :id";

        if (!conn.isOpen())
            conn.open();

        bool retorno = false;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":descricao", forma_pagamento.getDescricao());
            query.bindValue(":id", forma_pagamento.getId());

            if (query.exec())
                retorno = true;
            else
                qDebug() << "FormaPagamentoController.altera() query.exec: " << query.lastError().text();
        }

        conn.close();
        return retorno;
    }
    bool remove(int id)
    {
        sql = "DELETE FROM tb_forma_pagamento WHERE id = :id";

        if (!conn.isOpen())
            conn.open();

        bool retorno = false;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":id", id);

            if (query.exec())
                retorno = true;
            else
                qDebug() << "FormaPagamentoController.remove() query.exec: " << query.lastError().text();
        }

        conn.close();
        return retorno;
    }
};

#endif // FORMAPAGAMENTOCONTROLLER_H
