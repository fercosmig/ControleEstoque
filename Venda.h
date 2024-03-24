#ifndef VENDA_H
#define VENDA_H

#include <QString>
#include "Colaborador.h"
#include "FormaPagamento.h"

class Venda
{
private:
    int id;
    QString data;
    QString hora;
    double valor_total;
    FormaPagamento forma_pagamento;
    Colaborador colaborador;

protected:
public:
    // CONSTRUCTOR

    Venda() {}

    // GETTERS AND SETTERS

    void setId(int id) { this->id = id; }
    int getId() { return this->id; }

    void setData(QString data) { this->data = data; }
    QString getData() { return this->data; }

    void setHora(QString hora) { this->hora = hora; }
    QString getHora() { return this->hora; }

    void setValorTotal(double valor_total) { this->valor_total = valor_total; }
    double getValorTotal() { return this->valor_total; }

    void setFormaPagamento(FormaPagamento forma_pagamento) { this->forma_pagamento = forma_pagamento; }
    FormaPagamento getFormaPagamento() { return this->forma_pagamento; }

    void setColaborador(Colaborador colaborador) { this->colaborador = colaborador; }
    Colaborador getColaborador() { return this->colaborador; }
};

#endif // VENDA_H
