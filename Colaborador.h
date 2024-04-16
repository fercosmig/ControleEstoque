#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <QString>
#include "Grupo.h"

/*
CREATE TABLE tb_colaboradores (
    id       INTEGER   PRIMARY KEY AUTOINCREMENT,
    nome     TEXT (30) NOT NULL ON CONFLICT ROLLBACK,
    email    TEXT (30) NOT NULL ON CONFLICT ROLLBACK,
    senha    TEXT (30) NOT NULL ON CONFLICT ROLLBACK,
    id_grupo INTEGER   NOT NULL ON CONFLICT ROLLBACK
                       REFERENCES tb_grupos (id) ON DELETE CASCADE
);
*/

class Colaborador
{
private:
    int id;
    QString nome;
    QString email;
    QString senha;
    Grupo grupo;

protected:
public:
    // CONSTRUCTOR
    Colaborador() {}

    // GETTERS AND SETTERS
    int getId() const;
    void setId(int newId);
    QString getNome() const;
    void setNome(const QString &newNome);
    QString getEmail() const;
    void setEmail(const QString &newEmail);
    QString getSenha() const;
    void setSenha(const QString &newSenha);
    Grupo getGrupo() const;
    void setGrupo(const Grupo &newGrupo);
};

inline int Colaborador::getId() const
{
    return id;
}

inline void Colaborador::setId(int newId)
{
    id = newId;
}

inline QString Colaborador::getNome() const
{
    return nome;
}

inline void Colaborador::setNome(const QString &newNome)
{
    nome = newNome;
}

inline QString Colaborador::getEmail() const
{
    return email;
}

inline void Colaborador::setEmail(const QString &newEmail)
{
    email = newEmail;
}

inline QString Colaborador::getSenha() const
{
    return senha;
}

inline void Colaborador::setSenha(const QString &newSenha)
{
    senha = newSenha;
}

inline Grupo Colaborador::getGrupo() const
{
    return grupo;
}

inline void Colaborador::setGrupo(const Grupo &newGrupo)
{
    grupo = newGrupo;
}

#endif // COLABORADOR_H
