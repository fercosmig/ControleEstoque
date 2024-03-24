#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <QString>
#include "Grupo.h"
#include "QDebug"

class Colaborador
{
private:
    int id;
    QString nome;
    QString nome_usuario;
    QString senha;
    QString telefone;
    Grupo grupo;

protected:
public:
    // CONSTRUCTOR

    Colaborador() {}

    // GETTERS AND SETTERS

    void setId(int id) { this->id = id; }
    int getId() { return this->id; }

    void setNome(QString nome) { this->nome = nome; }
    QString getNome() { return this->nome; }

    void setNomeUsuario(QString nome_usuario) { this->nome_usuario = nome_usuario; }
    QString getNomeUsuario() { return this->nome_usuario; }

    void setSenha(QString senha) { this->senha = senha; }
    QString getSenha() { return this->senha; }

    void setTelefone(QString telefone) { this->telefone = telefone; }
    QString getTelefone() { return this->telefone; }

    void setGrupo(Grupo grupo) { this->grupo = grupo; }
    Grupo getGrupo() { return this->grupo; }
};
#endif // COLABORADOR_H
