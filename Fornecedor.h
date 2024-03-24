#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#include <QString>

class Fornecedor
{
private:
    int id;
    QString razao_social;
    QString nome_fantasia;

protected:
public:
    // CONSTRUCTOR

    Fornecedor() {}

    //GETTERS AND SETTERS

    void setId(int id) { this->id = id; }
    int getId() { return this->id; }

    void setRazaoSocial(QString razao_social) { this->razao_social = razao_social; }
    QString getRazaoSocial() { return this->razao_social; }

    void setNomeFantasia(QString nome_fantasia) { this->nome_fantasia = nome_fantasia; }
    QString getNomeFantasia() { return this->nome_fantasia; }
};

#endif // FORNECEDOR_H
