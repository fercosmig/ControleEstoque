#include "fm_gestao_tipo_pagamento.h"
#include "ui_fm_gestao_tipo_pagamento.h"

fm_gestao_tipo_pagamento::fm_gestao_tipo_pagamento(QWidget *parent) : QDialog(parent), ui(new Ui::fm_gestao_tipo_pagamento)
{
    ui->setupUi(this);
}

fm_gestao_tipo_pagamento::~fm_gestao_tipo_pagamento()
{
    delete ui;
}
