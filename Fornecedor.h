#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#include <QString>

/*
CREATE TABLE tb_fornecedores (
    id            INTEGER   PRIMARY KEY AUTOINCREMENT,
    razao_social  TEXT (60) NOT NULL ON CONFLICT ROLLBACK,
    nome_fantasia TEXT (60) NOT NULL ON CONFLICT ROLLBACK
);
*/

class Fornecedor
{
private:
    int id;
    QString razaoSocial;
    QString nomeFantasia;

protected:
public:
    // CONSTRUCTOR
    Fornecedor() {}

    // GETTERS AND SETTERS
    int getId() const;
    void setId(int newId);
    QString getRazaoSocial() const;
    void setRazaoSocial(const QString &newRazaoSocial);
    QString getNomeFantasia() const;
    void setNomeFantasia(const QString &newNomeFantasia);
};

inline int Fornecedor::getId() const
{
    return id;
}

inline void Fornecedor::setId(int newId)
{
    id = newId;
}

inline QString Fornecedor::getRazaoSocial() const
{
    return razaoSocial;
}

inline void Fornecedor::setRazaoSocial(const QString &newRazaoSocial)
{
    razaoSocial = newRazaoSocial;
}

inline QString Fornecedor::getNomeFantasia() const
{
    return nomeFantasia;
}

inline void Fornecedor::setNomeFantasia(const QString &newNomeFantasia)
{
    nomeFantasia = newNomeFantasia;
}

#endif // FORNECEDOR_H
