#include "remote.h"
#include "ui_remote.h"

Remote::Remote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Remote)
{
    ui->setupUi(this);
}

Remote::~Remote()
{
    delete ui;
}
