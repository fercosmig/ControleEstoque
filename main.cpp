/* ********************************************
 * Fernando Costa Migliorini
 * 2024-03-02
 */

#include "fm_principal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fm_principal w;
    w.show();
    return a.exec();
}
