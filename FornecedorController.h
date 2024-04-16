#ifndef FORNECEDORCONTROLLER_H
#define FORNECEDORCONTROLLER_H

#include <QString>
#include "Conexao.h"
#include "Fornecedor.h"

class FornecedorController
{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

protected:
public:
    // CONSTRUCTOR
    FornecedorController() {}

    // METHODS CRUD - CREATE / READ / UPDATE / DELETE
    Fornecedor insere(Fornecedor fornecedor);
    QVector<Fornecedor> buscaTodos();
    QVector<Fornecedor> buscaPorRazaoSocialNomeFantasia(Fornecedor fornecedor);
    Fornecedor buscaPorId(Fornecedor fornecedor);
    bool altera(Fornecedor fornecedor);
    bool remove(Fornecedor fornecedor);
};

inline Fornecedor FornecedorController::insere(Fornecedor fornecedor)
{
    sql = "INSERT INTO tb_fornecedores ";
    sql +="( razao_social, nome_fantasia ) ";
    sql +="VALUES ";
    sql +="( :razao_social, :nome_fantasia )";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()){
        query.exec("BEGIN IMMEDIATE TRANSACTION");

        query.prepare(sql);
        query.bindValue(":razao_social", fornecedor.getRazaoSocial());
        query.bindValue(":nome_fantasia", fornecedor.getNomeFantasia());

        if (query.exec()) {
            sql = "SELECT id, razao_social, nome_fantasia FROM tb_fornecedores ORDER BY id DESC LIMIT 1";
            query.prepare(sql);

            if (query.exec()) {
                if (query.next()){
                    fornecedor.setId(query.record().value("id").toInt());
                    fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                    fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());
                }
            } else
                qDebug() << "FornecedorController::insere(SELECT) " << query.lastError().text();
        } else
            qDebug() << "FornecedorController::insere(INSERT) " << query.lastError().text();

        query.exec("COMMIT");
    }
    conn.close();
    return fornecedor;
}

inline QVector<Fornecedor> FornecedorController::buscaTodos()
{
    sql = "SELECT id, razao_social, nome_fantasia ";
    sql += "FROM tb_fornecedores ";
    sql += "ORDER BY razao_social ASC";

    if (!conn.isOpen())
        conn.open();

    Fornecedor fornecedor;
    QVector<Fornecedor> ListaFornecedores;

    if (conn.isOpen()){
        query.prepare(sql);

        if (query.exec()) {
            if (query.next()) {
                do {
                    fornecedor.setId(query.record().value("id").toInt());
                    fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                    fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());

                    ListaFornecedores.push_back(fornecedor);
                } while (query.next());
            }
        } else
            qDebug() << "FornecedorController::buscaTodos() " << query.lastError().text();
    }
    conn.close();
    return ListaFornecedores;
}

inline QVector<Fornecedor> FornecedorController::buscaPorRazaoSocialNomeFantasia(Fornecedor fornecedor)
{
    sql = "SELECT id, razao_social, nome_fantasia ";
    sql += "FROM tb_fornecedores ";
    sql += "WHERE ";
    sql += "razao_social LIKE :razao_social OR ";
    sql += "nome_fantasia LIKE :nome_fantasia ";
    sql += "ORDER BY razao_social ASC";

    if (!conn.isOpen())
        conn.open();

    QVector<Fornecedor> ListaFornecedores;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":razao_social", "%" + fornecedor.getRazaoSocial() + "%");
        query.bindValue(":nome_fantasia", "%" + fornecedor.getNomeFantasia() + "%");

        if (query.exec()) {
            if (query.next()) {
                do {
                    fornecedor.setId(query.record().value("id").toInt());
                    fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                    fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());

                    ListaFornecedores.push_back(fornecedor);
                } while (query.next());
            }
        } else
            qDebug() << "FornecedorController::buscaPorRazaoSocialNomeFantasia() " << query.lastError().text();
    }
    conn.close();
    return ListaFornecedores;
}

inline Fornecedor FornecedorController::buscaPorId(Fornecedor fornecedor)
{
    sql = "SELECT id, razao_social, nome_fantasia ";
    sql += "FROM tb_fornecedores ";
    sql += "WHERE ";
    sql += "id = :id";

    if (!conn.isOpen())
        conn.open();

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", fornecedor.getId());

        if (query.exec()) {
            if (query.next()) {
                fornecedor.setId(query.record().value("id").toInt());
                fornecedor.setRazaoSocial(query.record().value("razao_social").toString());
                fornecedor.setNomeFantasia(query.record().value("nome_fantasia").toString());
            }
        } else
            qDebug() << "FornecedorController::buscaPorId() " << query.lastError().text();
    }
    conn.close();
    return fornecedor;
}

inline bool FornecedorController::altera(Fornecedor fornecedor)
{
    sql = "UPDATE tb_fornecedores SET ";
    sql += "razao_social = :razao_social, ";
    sql += "nome_fantasia = :nome_fantasia ";
    sql += "WHERE ";
    sql += "id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":razao_social", fornecedor.getRazaoSocial());
        query.bindValue(":nome_fantasia", fornecedor.getNomeFantasia());
        query.bindValue(":id", fornecedor.getId());

        if (query.exec())
            retorno = true;
        else
            qDebug() << "FornecedorController::altera() " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline bool FornecedorController::remove(Fornecedor fornecedor)
{
    sql = "DELETE FROM tb_fornecedores ";
    sql += "WHERE ";
    sql += "id = :id";

    if (!conn.isOpen())
        conn.open();

    bool retorno = false;

    if (conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", fornecedor.getId());

        if (query.exec())
            retorno = true;
        else
            qDebug() << "FornecedorController::remove() " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

#endif // FORNECEDORCONTROLLER_H
