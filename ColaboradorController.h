#ifndef COLABORADORCONTROLLER_H
#define COLABORADORCONTROLLER_H

#include <QDebug>
#include <QString>
#include <QtSql>
#include "Colaborador.h"
#include "Conexao.h"
#include "Grupo.h"

class ColaboradorController
{
private:
    QString sql;
    Conexao conn;
    QSqlQuery query;

protected:
public:
    // CONSTRUCTOR

    ColaboradorController() {}

    // METHODS CRUD = create, read, update, and delete

    bool insere(Colaborador colaborador)
    {
        sql = "INSERT INTO tb_colaboradores (nome, nome_usuario, senha, telefone, id_grupo) ";
        sql += "VALUES (:nome, :nome_usuario, :senha, :telefone, :id_grupo)";

        if (!conn.isOpen())
            conn.open();

        bool retorno = false;

        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":nome", colaborador.getNome());
            query.bindValue(":nome_usuario", colaborador.getNomeUsuario());
            query.bindValue(":senha", colaborador.getSenha());
            query.bindValue(":telefone", colaborador.getTelefone());
            query.bindValue(":id_grupo", colaborador.getGrupo().getId());

            if (query.exec())
                retorno = true;
            else
                qDebug() << "ColaboradorController.insere() query.exec: " << query.lastError().text();
        }

        conn.close();
        return retorno;
    }

    Colaborador buscaPorId(int id)
    {
        sql = "SELECT ";
        sql += "tb_colaboradores.id, tb_colaboradores.nome, tb_colaboradores.nome_usuario, tb_colaboradores.senha, ";
        sql += "tb_colaboradores.telefone, tb_grupos.id as id_grupo, tb_grupos.descricao, tb_grupos.sigla ";
        sql += "FROM tb_colaboradores ";
        sql += "INNER JOIN tb_grupos ON tb_colaboradores.id_grupo = tb_grupos.id ";
        sql += "WHERE tb_colaboradores.id = :id";

        if (!conn.isOpen())
            conn.open();

        Colaborador colaborador;
        Grupo grupo;

        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":id", id);

            if (query.exec()) {
                if (query.next()) {
                    // colaborador precisa de um grupo
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setDescricao(query.record().value("descricao").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    colaborador.setId(query.record().value("id").toInt());
                    colaborador.setNome(query.record().value("nome").toString());
                    colaborador.setNomeUsuario(query.record().value("nome_usuario").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setTelefone(query.record().value("telefone").toString());
                    colaborador.setGrupo(grupo);
                } else
                    qDebug() << "ColaboradorController.buscaPorId: 0 registros";

            } else
                qDebug() << "ColaboradorController.buscaPorId() query.exec: " << query.lastError().text();
        }

        conn.close();
        return colaborador;
    }

    QVector<Colaborador> buscaPorNome(QString nome)
    {
        sql = "SELECT ";
        sql += "tb_colaboradores.id, tb_colaboradores.nome, tb_colaboradores.nome_usuario, tb_colaboradores.senha, ";
        sql += "tb_colaboradores.telefone, tb_grupos.id as id_grupo, tb_grupos.descricao, tb_grupos.sigla ";
        sql += "FROM tb_colaboradores ";
        sql += "INNER JOIN tb_grupos ON tb_colaboradores.id_grupo = tb_grupos.id ";
        sql += "WHERE tb_colaboradores.nome like :nome";

        if (!conn.isOpen())
            conn.open();

        QVector<Colaborador> listaColaboradores;
        Colaborador colaborador;
        Grupo grupo;

        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":nome", "%" + nome + "%");

            if (query.exec()) {
                if (query.next()) {
                    do {
                        // colaborador precisa de um grupo
                        grupo.setId(query.record().value("id_grupo").toInt());
                        grupo.setDescricao(query.record().value("descricao").toString());
                        grupo.setSigla(query.record().value("sigla").toString());

                        colaborador.setId(query.record().value("id").toInt());
                        colaborador.setNome(query.record().value("nome").toString());
                        colaborador.setNomeUsuario(query.record().value("nome_usuario").toString());
                        colaborador.setSenha(query.record().value("senha").toString());
                        colaborador.setTelefone(query.record().value("telefone").toString());
                        colaborador.setGrupo(grupo);

                        listaColaboradores.push_back(colaborador);
                    } while (query.next());
                } else
                    qDebug() << "ColaboradorController.buscaPorNome: 0 registros";

            } else
                qDebug() << "ColaboradorController.buscaPorNome() query.exec: " << query.lastError().text();
        }

        conn.close();
        return listaColaboradores;
    }

    QVector<Colaborador> buscaTodos()
    {
        sql = "SELECT ";
        sql += "tb_colaboradores.id, tb_colaboradores.nome, tb_colaboradores.nome_usuario, tb_colaboradores.senha, ";
        sql += "tb_colaboradores.telefone, tb_grupos.id as id_grupo, tb_grupos.descricao, tb_grupos.sigla ";
        sql += "FROM tb_colaboradores ";
        sql += "INNER JOIN tb_grupos ON tb_colaboradores.id_grupo = tb_grupos.id";

        if (!conn.isOpen())
            conn.open();

        QVector<Colaborador> listaColaboradores;
        Colaborador colaborador;
        Grupo grupo;

        if (conn.isOpen()) {
            query.prepare(sql);

            if (query.exec()) {
                if (query.next()) {
                    do {
                        // colaborador precisa de um grupo
                        grupo.setId(query.record().value("id_grupo").toInt());
                        grupo.setDescricao(query.record().value("descricao").toString());
                        grupo.setSigla(query.record().value("sigla").toString());

                        colaborador.setId(query.record().value("id").toInt());
                        colaborador.setNome(query.record().value("nome").toString());
                        colaborador.setNomeUsuario(query.record().value("nome_usuario").toString());
                        colaborador.setSenha(query.record().value("senha").toString());
                        colaborador.setTelefone(query.record().value("telefone").toString());
                        colaborador.setGrupo(grupo);

                        listaColaboradores.push_back(colaborador);
                    } while (query.next());
                } else
                    qDebug() << "ColaboradorController.buscaTodos: 0 registros";

            } else
                qDebug() << "ColaboradorController.buscaTodos() query.exec: " << query.lastError().text();
        }

        conn.close();
        return listaColaboradores;
    }

    int autentica(QString nome_usuario, QString senha)
    {
        sql = "SELECT id FROM tb_colaboradores WHERE nome_usuario = :nome_usuario AND senha = :senha";

        if (!conn.isOpen())
            conn.open();

        int id = 0;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":nome_usuario", nome_usuario);
            query.bindValue(":senha", senha);

            if (query.exec()) {
                if (query.next()) {
                    id = query.record().value("id").toInt();
                } else
                    qDebug() << "ColaboradorController.autentica: 0 registros";

            } else
                qDebug() << "ColaboradorController.autentica() query.exec: " << query.lastError().text();
        }

        conn.close();
        return id;
    }

    int buscaNomeUsuarioDuplicado(QString nome_usuario)
    {
        sql = "SELECT id FROM tb_colaboradores WHERE nome_usuario = :nome_usuario";

        if (!conn.isOpen())
            conn.open();

        int retorno = 0;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":nome_usuario", nome_usuario);

            if (query.exec()) {
                if (query.next()) {
                    retorno = query.record().value("id").toInt();
                    qDebug() << "ColaboradorController.buscaNomeUsuarioDuplicado: duplicado.";
                }

            } else
                qDebug() << "ColaboradorController.buscaNomeUsuarioDuplicado() query.exec: " << query.lastError().text();
        }

        conn.close();
        return retorno;
    }

    bool altera(Colaborador colaborador)
    {
        sql = "UPDATE tb_colaboradores SET nome = :nome, nome_usuario = :nome_usuario, senha = :senha, ";
        sql += "telefone = :telefone, id_grupo = :id_grupo WHERE id = :id";

        if (!conn.isOpen())
            conn.open();

        bool retorno = false;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":nome", colaborador.getNome());
            query.bindValue(":nome_usuario", colaborador.getNomeUsuario());
            query.bindValue(":senha", colaborador.getSenha());
            query.bindValue(":telefone", colaborador.getTelefone());
            query.bindValue(":id_grupo", colaborador.getGrupo().getId());
            query.bindValue(":id", colaborador.getId());

            if (query.exec())
                retorno = true;
            else
                qDebug() << "ColaboradorController.altera() query.exec: " << query.lastError().text();
        }

        conn.close();
        return retorno;
    }

    bool remove(int id)
    {
        sql = "DELETE FROM tb_colaboradores WHERE id = :id";

        if (!conn.isOpen())
            conn.open();

        bool retorno = false;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":id", id);

            if (query.exec())
                retorno = true;
            else
                qDebug() << "ColaboradorController.remove() query.exec: " << query.lastError().text();
        }

        conn.close();
        return retorno;
    }
};

#endif // COLABORADORCONTROLLER_H
