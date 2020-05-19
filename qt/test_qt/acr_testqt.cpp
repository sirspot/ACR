#include "acr_testqt.h"
#include "ui_acr_testqt.h"

#include "ACR/public.h"

ACR_TestQt::ACR_TestQt(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ACR_TestQt)
{
    ui->setupUi(this);

    ACR_Test();
}

ACR_TestQt::~ACR_TestQt()
{
    delete ui;
}

