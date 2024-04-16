#ifndef COLABORADORCONTROLLER_H
#define COLABORADORCONTROLLER_H

#include <QString>
#include "Conexao.h"
#include "Colaborador.h"
#include "Grupo.h"

class ColaboradorController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

protected:
public:
    // CONSTRUCTOR
    ColaboradorController(){}

    // METHODS
    Colaborador insere(Colaborador colaborador);
    QVector<Colaborador> buscaTodos();
    QVector<Colaborador> buscaPorNomeEmail(Colaborador colaborador);
    Colaborador buscaPorId(Colaborador colaborador);
    Colaborador autenticar(Colaborador colaborador);
    bool verificaDuplicidadeEmail(Colaborador colaborador);
    bool altera(Colaborador colaborador);
    bool remove(Colaborador colaborador);
};

inline Colaborador ColaboradorController::insere(Colaborador colaborador)
{
    sql = "INSERT INTO tb_colaboradores ";
    sql += "( nome, email, senha, id_grupo ) ";
    sql += "VALUES ";
    sql += "( :nome, :email, :senha, :id_grupo )";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()) {
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":nome", colaborador.getNome());
        query.bindValue(":email", colaborador.getEmail());
        query.bindValue(":senha", colaborador.getSenha());
        query.bindValue(":id_grupo", colaborador.getGrupo().getId());

        if (query.exec()) {
            sql = "SELECT id FROM tb_colaboradores ORDER BY id DESC LIMIT 1";
            query.prepare(sql);
            if (query.exec()) {
                if (query.next())
                    colaborador.setId(query.record().value("id").toInt());
            } else
                qDebug() << "ColaboradorController::insere() query.exec(SELECT): " << query.lastError().text();
        } else
            qDebug() << "ColaboradorController::insere() query.exec(INSERT): " << query.lastError().text();

        query.exec("COMMIT");
    }
    conn.close();
    return colaborador;
}

inline QVector<Colaborador> ColaboradorController::buscaTodos()
{
    sql = "SELECT ";
    sql += "tb_colaboradores.id, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.email, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id AS id_grupo, ";
    sql += "tb_grupos.descricao, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM tb_colaboradores ";
    sql += "INNER JOIN tb_grupos ";
    sql += "ON tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "ORDER BY tb_colaboradores.nome ASC";

    if (!conn.isOpen())
        conn.open();

    Grupo grupo;
    Colaborador colaborador;
    QVector<Colaborador> listaColaboradores;

    if (conn.isOpen()) {

        query.prepare(sql);

        if (query.exec()) {
            if (query.next()) {
                do {
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setDescricao(query.record().value("descricao").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    colaborador.setId(query.record().value("id").toInt());
                    colaborador.setNome(query.record().value("nome").toString());
                    colaborador.setEmail(query.record().value("email").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setGrupo(grupo);

                    listaColaboradores.push_back(colaborador);
                } while (query.next());
            }
        } else
            qDebug() << "ColaboradorController::buscaTodos() query.exec(): " << query.lastError().text();
    }
    conn.close();
    return listaColaboradores;
}

inline QVector<Colaborador> ColaboradorController::buscaPorNomeEmail(Colaborador colaborador)
{
    sql = "SELECT ";
    sql += "tb_colaboradores.id, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.email, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id AS id_grupo, ";
    sql += "tb_grupos.descricao, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM tb_colaboradores ";
    sql += "INNER JOIN tb_grupos ";
    sql += "ON tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "WHERE ";
    sql += "tb_colaboradores.nome LIKE :nome OR ";
    sql += "tb_colaboradores.email LIKE :email ";
    sql += "ORDER BY tb_colaboradores.nome ASC";

    if (!conn.isOpen())
        conn.open();

    Grupo grupo;
    QVector<Colaborador> ListaColaboradores;

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":nome", "%" + colaborador.getNome() + "%");
        query.bindValue(":email", "%" + colaborador.getEmail() + "%");

        if (query.exec()) {
            if (query.next()) {
                do {
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setDescricao(query.record().value("descricao").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    colaborador.setId(query.record().value("id").toInt());
                    colaborador.setNome(query.record().value("nome").toString());
                    colaborador.setEmail(query.record().value("email").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setGrupo(grupo);

                    ListaColaboradores.push_back(colaborador);
                } while (query.next());
            }
        } else
            qDebug() << "ColaboradorController::buscaPorNomeEmail() query.exec(): " << query.lastError().text();
    }
    conn.close();
    return ListaColaboradores;
}

inline Colaborador ColaboradorController::buscaPorId(Colaborador colaborador)
{
    sql = "SELECT ";
    sql += "tb_colaboradores.id, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.email, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id AS id_grupo, ";
    sql += "tb_grupos.descricao, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM tb_colaboradores ";
    sql += "INNER JOIN tb_grupos ";
    sql += "ON tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "WHERE tb_colaboradores.id = :id ";

    if (!conn.isOpen())
        conn.open();

    Grupo grupo;

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":id", colaborador.getId());

        if (query.exec()) {
            if (query.next()) {
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setDescricao(query.record().value("descricao").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    colaborador.setId(query.record().value("id").toInt());
                    colaborador.setNome(query.record().value("nome").toString());
                    colaborador.setEmail(query.record().value("email").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setGrupo(grupo);
            }
        } else
            qDebug() << "ColaboradorController::buscaPorId() query.exec(): " << query.lastError().text();
    }
    conn.close();
    return colaborador;
}

inline Colaborador ColaboradorController::autenticar(Colaborador colaborador)
{
    sql = "SELECT ";
    sql += "tb_colaboradores.id, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.email, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id AS id_grupo, ";
    sql += "tb_grupos.descricao, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM tb_colaboradores ";
    sql += "INNER JOIN tb_grupos ";
    sql += "ON tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "WHERE ";
    sql += "tb_colaboradores.email = :email AND ";
    sql += "tb_colaboradores.senha = :senha";

    if (!conn.isOpen())
        conn.open();

    Grupo grupo;

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":email", colaborador.getEmail());
        query.bindValue(":senha", colaborador.getSenha());

        if (query.exec()) {
            if (query.next()) {
                grupo.setId(query.record().value("id_grupo").toInt());
                grupo.setDescricao(query.record().value("descricao").toString());
                grupo.setSigla(query.record().value("sigla").toString());

                colaborador.setId(query.record().value("id").toInt());
                colaborador.setNome(query.record().value("nome").toString());
                colaborador.setEmail(query.record().value("email").toString());
                colaborador.setSenha(query.record().value("senha").toString());
                colaborador.setGrupo(grupo);
            }
        } else
            qDebug() << "ColaboradorController::autenticar() query.exec(): " << query.lastError().text();
    }
    conn.close();
    return colaborador;
}
inline bool ColaboradorController::verificaDuplicidadeEmail(Colaborador colaborador)
{
    sql = "SELECT id ";
    sql += "FROM tb_colaboradores ";
    sql += "WHERE tb_colaboradores.email = :email ";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":email", colaborador.getEmail());

        if (query.exec()) {
            if (query.next())
                retorno = true;
        } else
            qDebug() << "ColaboradorController::verificaDuplicidadeEmail() query.exec(): " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline bool ColaboradorController::altera(Colaborador colaborador)
{
    sql = "UPDATE tb_colaboradores ";
    sql += "SET ";
    sql += "nome = :nome, ";
    sql += "email = :email, ";
    sql += "senha = :senha, ";
    sql += "id_grupo = :id_grupo ";
    sql += " WHERE id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":nome", colaborador.getNome());
        query.bindValue(":email", colaborador.getEmail());
        query.bindValue(":senha", colaborador.getSenha());
        query.bindValue(":id_grupo", colaborador.getGrupo().getId());
        query.bindValue(":id", colaborador.getId());

        if (query.exec())
            retorno = true;
        else
            qDebug() << "ColaboradorController::altera() query.exec: " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline bool ColaboradorController::remove(Colaborador colaborador)
{
    sql = "DELETE FROM tb_colaboradores WHERE id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":id", colaborador.getId());

        if (query.exec())
            retorno = true;
        else
            qDebug() << "ColaboradorController::remove() query.exec: " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

#endif // COLABORADORCONTROLLER_H
