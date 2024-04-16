#ifndef GRUPOCONTROLLER_H
#define GRUPOCONTROLLER_H

#include <QString>
#include "Conexao.h"
#include "Grupo.h"

class GrupoController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;
protected:
public:
    // CONSTRUCTOR
    GrupoController() {}

    // METHODS
    Grupo insere(Grupo grupo);
    QVector<Grupo> buscaTodos();
    QVector<Grupo> buscaPorDescricao(Grupo grupo);
    Grupo buscaPorId(Grupo grupo);
    bool buscaSiglaDuplicada(Grupo grupo);
    bool altera(Grupo grupo);
    bool remove(Grupo grupo);
};

inline Grupo GrupoController::insere(Grupo grupo)
{
    sql = "INSERT INTO tb_grupos ";
    sql += "( descricao, sigla ) ";
    sql += "VALUES ";
    sql += "( :descricao, :sigla )";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()){
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":descricao", grupo.getDescricao());
        query.bindValue(":sigla", grupo.getSigla());

        if (query.exec()) {
            sql = "SELECT id, descricao, sigla FROM tb_grupos ORDER BY id DESC LIMIT 1";
            query.prepare(sql);

            if (query.exec()) {
                if (query.next()){
                    grupo.setId(query.record().value("id").toInt());
                    grupo.setDescricao(query.record().value("descricao").toString());
                    grupo.setSigla(query.record().value("sigla").toString());
                }
            } else
                qDebug() << "GrupoController::insere(SELECT) " << query.lastError().text();
        } else
            qDebug() << "GrupoController::insere(INSERT) " << query.lastError().text();

        query.exec("COMMIT");
    }
    conn.close();
    return grupo;
}

inline QVector<Grupo> GrupoController::buscaTodos()
{
    sql = "SELECT id, descricao, sigla ";
    sql += "FROM tb_grupos ";
    sql += "ORDER BY descricao ASC";

    if (!conn.isOpen())
        conn.open();

    Grupo grupo;
    QVector<Grupo> listaGrupos;

    if (conn.isOpen()){
        query.prepare(sql);

        if (query.exec()) {
            if (query.next()){
                do {
                    grupo.setId(query.record().value("id").toInt());
                    grupo.setDescricao(query.record().value("descricao").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    listaGrupos.push_back(grupo);
                } while (query.next());
            }
        } else
            qDebug() << "GrupoController::buscaTodos() " << query.lastError().text();
    }
    conn.close();
    return listaGrupos;
}

inline QVector<Grupo> GrupoController::buscaPorDescricao(Grupo grupo)
{
    sql = "SELECT id, descricao, sigla ";
    sql += "FROM tb_grupos ";
    sql += "WHERE descricao LIKE :descricao ";
    sql += "ORDER BY descricao ASC";

    if (!conn.isOpen())
        conn.open();

    QVector<Grupo> listaGrupos;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":descricao", "%" + grupo.getDescricao() + "%");

        if (query.exec()) {
            if (query.next()){
                do {
                    grupo.setId(query.record().value("id").toInt());
                    grupo.setDescricao(query.record().value("descricao").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    listaGrupos.push_back(grupo);
                } while (query.next());
            }
        } else
            qDebug() << "GrupoController::buscaPorDescricao() " << query.lastError().text();
    }
    conn.close();
    return listaGrupos;
}

inline Grupo GrupoController::buscaPorId(Grupo grupo)
{
    sql = "SELECT id, descricao, sigla ";
    sql += "FROM tb_grupos ";
    sql += "WHERE id = :id ";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", grupo.getId());

        if (query.exec()) {
            if (query.next()){
                    grupo.setId(query.record().value("id").toInt());
                    grupo.setDescricao(query.record().value("descricao").toString());
                    grupo.setSigla(query.record().value("sigla").toString());
            }
        } else
            qDebug() << "GrupoController::buscaPorId() " << query.lastError().text();
    }
    conn.close();
    return grupo;
}

inline bool GrupoController::buscaSiglaDuplicada(Grupo grupo)
{
    sql = "SELECT id ";
    sql += "FROM tb_grupos ";
    sql += "WHERE sigla = :sigla ";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":sigla", grupo.getSigla());

        if (query.exec()) {
            if (query.next())
                retorno = true;
        } else
            qDebug() << "GrupoController::buscaSiglaDuplicada() " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline bool GrupoController::altera(Grupo grupo)
{
    sql = "UPDATE tb_grupos SET ";
    sql += "descricao = :descricao, ";
    sql += "sigla = :sigla ";
    sql += "WHERE id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":descricao", grupo.getDescricao());
        query.bindValue(":sigla", grupo.getSigla());
        query.bindValue(":id", grupo.getId());

        if (query.exec()) {
            retorno = true;
        } else
            qDebug() << "GrupoController::altera() " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline bool GrupoController::remove(Grupo grupo)
{
    sql = "DELETE FROM tb_grupos ";
    sql += "WHERE id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", grupo.getId());

        if (!query.exec()) {
            retorno = true;
        } else
            qDebug() << "GrupoController::remove() " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

#endif // GRUPOCONTROLLER_H
