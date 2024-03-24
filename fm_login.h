#ifndef FM_LOGIN_H
#define FM_LOGIN_H

#include <QDialog>

namespace Ui {
class fm_login;
}

class fm_login : public QDialog
{
    Q_OBJECT

public:
    explicit fm_login(QWidget *parent = nullptr);
    ~fm_login();

    // MINHAS FUNÇOES PARA O FORMULARIO
    void limpa_campos_fm_login();

private slots:
    void on_pushButton_fechar_clicked();

    void on_pushButton_login_clicked();

private:
    Ui::fm_login *ui;
};

#endif // FM_LOGIN_H
