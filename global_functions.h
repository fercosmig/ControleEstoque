#ifndef GLOBAL_FUNCTIONS_H
#define GLOBAL_FUNCTIONS_H

#include <QString>
#include <QTableWidget>

class global_functions
{
public:
    global_functions();
    static bool minCaracter(QString str, int quantidade);
    static void formata_table_widget(QTableWidget *tw, QStringList cabecalho);
    static QString formata_double(double valor);
};

#endif // GLOBAL_FUNCTIONS_H
