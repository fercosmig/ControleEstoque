#ifndef FM_GESTAO_TIPO_PAGAMENTO_H
#define FM_GESTAO_TIPO_PAGAMENTO_H

#include <QDialog>

namespace Ui {
class fm_gestao_tipo_pagamento;
}

class fm_gestao_tipo_pagamento : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestao_tipo_pagamento(QWidget *parent = nullptr);
    ~fm_gestao_tipo_pagamento();

private:
    Ui::fm_gestao_tipo_pagamento *ui;
};

#endif // FM_GESTAO_TIPO_PAGAMENTO_H
