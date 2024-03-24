#ifndef FORNECEDORCONTROLLER_H
#define FORNECEDORCONTROLLER_H

#include <QDebug>
#include <QString>
#include <QVector>
#include "Conexao.h"
#include "Fornecedor.h"

class FornecedorController
{
private:
    QString sql;
    Conexao conn;
    QSqlQuery query;

protected:
public:
    // CONSTRUCTOR

    FornecedorController() {}

    // METHODS CRUD = create, read, update, and delete

    bool insere(Fornecedor fornecedor)
    {
        sql = "INSERT INTO tb_fornecedores (razao_social, nome_fantasia) VALUES (:razao_social, "
              ":nome_fantasia)";

        if (!conn.isOpen())
            conn.open();

        bool retorno = false;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":razao_social", fornecedor.getRazaoSocial());
            query.bindValue(":nome_fantasia", fornecedor.getNomeFantasia());

            if (query.exec())
                retorno = true;
            else {
                qDebug() << "FornecedorController.insere()";
                qDebug() << "query.exec: " << query.lastError().text();
            }
        }

        conn.close();
        return retorno;
    }

    QVector<Fornecedor> buscaTodos()
    {
        sql = "SELECT id, razao_social, nome_fantasia FROM tb_fornecedores ORDER BY nome_fantasia "
              "ASC";

        if (!conn.isOpen())
            conn.open();

        QVector<Fornecedor> listaFornecedores;
        Fornecedor fornecedor;

        if (conn.isOpen()) {
            query.prepare(sql);

            if (query.exec()) {
                if (query.next()) {
                    do {
                        fornecedor.setId(query.record().value("id").toInt());
                        fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                        fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());
                        listaFornecedores.push_back(fornecedor);
                    } while (query.next());
                } else
                    qDebug() << "FornecedorController.buscaTodos: 0 registros.";

            } else {
                qDebug() << "FornecedorController.buscaTodos()";
                qDebug() << "query.exec: " << query.lastError().text();
            }
        }

        conn.close();
        return listaFornecedores;
    }

    Fornecedor buscaPorId(int id)
    {
        sql = "SELECT id, razao_social, nome_fantasia FROM tb_fornecedores WHERE id = :id";

        if (!conn.isOpen())
            conn.open();

        Fornecedor fornecedor;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":id", id);

            if (query.exec()) {
                if (query.next()) {
                    fornecedor.setId(query.record().value("id").toInt());
                    fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                    fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());
                } else
                    qDebug() << "FornecedorController.buscaPorId: 0 registros";
            } else {
                qDebug() << "FornecedorController.buscaPorId()";
                qDebug() << "query.exec: " << query.lastError().text();
            }
        }

        conn.close();
        return fornecedor;
    }

    QVector<Fornecedor> buscaPorNomeFantasia(QString buscar)
    {
        sql = "SELECT id, razao_social, nome_fantasia FROM tb_fornecedores WHERE nome_fantasia "
              "LIKE :nome_fantasia ORDER BY nome_fantasia ASC";

        if (!conn.isOpen())
            conn.open();

        QVector<Fornecedor> listaFornecedores;
        Fornecedor fornecedor;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":nome_fantasia", "%" + buscar + "%");

            if (query.exec()) {
                if (query.next()) {
                    do {
                        fornecedor.setId(query.record().value("id").toInt());
                        fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                        fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());
                        listaFornecedores.push_back(fornecedor);
                    } while (query.next());
                } else
                    qDebug() << "FornecedorController.buscaPorNomeFantasia: 0 registros";
            } else {
                qDebug() << "FornecedorController.buscaPorNomeFantasia()";
                qDebug() << "query.exec: " << query.lastError().text();
            }
        }

        conn.close();
        return listaFornecedores;
    }

    QVector<Fornecedor> buscaPorRazaoSocial(QString buscar)
    {
        sql = "SELECT id, razao_social, nome_fantasia FROM tb_fornecedores WHERE razao_social LIKE "
              ":razao_social ORDER BY nome_fantasia ASC";

        if (!conn.isOpen())
            conn.open();

        QVector<Fornecedor> listaFornecedores;
        Fornecedor fornecedor;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":razao_social", "%" + buscar + "%");

            if (query.exec()) {
                if (query.next()) {
                    do {
                        fornecedor.setId(query.record().value("id").toInt());
                        fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                        fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());
                        listaFornecedores.push_back(fornecedor);
                    } while (query.next());
                } else
                    qDebug() << "FornecedorController.buscaPorRazaoSocial: 0 registros";
            } else {
                qDebug() << "FornecedorController.buscaPorRazaoSocial()";
                qDebug() << "query.exec: " << query.lastError().text();
            }
        }

        conn.close();
        return listaFornecedores;
    }

    bool altera(Fornecedor fornecedor)
    {
        sql = "UPDATE tb_fornecedores SET razao_social = :razao_social, nome_fantasia = "
              ":nome_fantasia WHERE id = :id";

        if (!conn.isOpen())
            conn.open();

        bool retorno = false;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":razao_social", fornecedor.getRazaoSocial());
            query.bindValue(":nome_fantasia", fornecedor.getNomeFantasia());
            query.bindValue(":id", fornecedor.getId());

            if (query.exec())
                retorno = true;
            else {
                qDebug() << "FornecedorController.altera()";
                qDebug() << "query.exec: " << query.lastError().text();
            }
        }

        conn.close();
        return retorno;
    }

    bool remove(int id)
    {
        sql = "DELETE FROM tb_fornecedores WHERE id = :id";

        if (!conn.isOpen())
            conn.open();

        bool retorno = false;
        if (conn.isOpen()) {
            query.prepare(sql);
            query.bindValue(":id", id);

            if (query.exec())
                retorno = true;
            else {
                qDebug() << "FornecedorController.remove()";
                qDebug() << "query.exec: " << query.lastError().text();
            }
        }

        conn.close();
        return retorno;
    }
};

#endif // FORNECEDORCONTROLLER_H
