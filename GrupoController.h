#ifndef GRUPOCONTROLLER_H
#define GRUPOCONTROLLER_H

#include <QtSql>
#include "Conexao.h"
#include "Grupo.h"

class GrupoController
{
private:
    QString sql;
    Conexao conn;
    QSqlQuery query;

protected:
public:
    //  CONSTRUCTOR
    GrupoController() {}

    // METHODS CRUD = create, read, update, and delete

    QVector<Grupo> buscaTodos()
    {
        sql = "SELECT id, descricao, sigla FROM tb_grupos ORDER BY descricao ASC";

        if (!conn.isOpen())
            conn.open();

        QVector<Grupo> listaGrupos;
        Grupo grupo;
        if (conn.isOpen()) {
            query.prepare(sql);

            if (query.exec()) {
                if (query.next()) {
                    do {
                        grupo.setId(query.record().value("id").toInt());
                        grupo.setDescricao(query.record().value("descricao").toString());
                        grupo.setSigla(query.record().value("sigla").toString());
                        listaGrupos.push_back(grupo);
                    } while (query.next());
                } else
                    qDebug() << "GrupoController.buscaTodos: 0 registros";

            } else
                qDebug() << "GrupoController.buscaTodos() query.exec: " << query.lastError().text();
        }

        conn.close();
        return listaGrupos;
    }

    Grupo buscaPorId(QString id)
    {
        sql = "SELECT id, descricao, sigla FROM tb_grupos WHERE id = :id";

        if (!conn.isOpen())
            conn.open();

        Grupo grupo;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":id", id);

            if (query.exec()) {
                if (query.next()) {
                    grupo.setId(query.record().value("id").toInt());
                    grupo.setDescricao(query.record().value("descricao").toString());
                    grupo.setSigla(query.record().value("sigla").toString());
                } else
                    qDebug() << "GrupoController.buscaPorId: 0 registros";

            } else
                qDebug() << "GrupoController.buscaPorId() query.exec: " << query.lastError().text();
        }

        conn.close();
        return grupo;
    }
};

#endif // GRUPOCONTROLLER_H
