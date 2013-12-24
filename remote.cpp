#include "remote.h"
#include "ui_remote.h"
#include "QProcess"
#include "QDir"

Remote::Remote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Remote)
{
    ui->setupUi(this);
    rdp_state=FALSE;
    connect (ui->pushButton,SIGNAL(released()),this,SLOT(enable_disable_rdp()));

}

Remote::~Remote()
{
    delete ui;
}

void Remote::enable_disable_rdp()
{
    QProcess *Process=new QProcess;
    //QString file = QDir::homePath() + "ts_disable.vbs";
    //QString file1 = QDir::currentPath() + "/ts_disable.vbs";
    //qDebug() << file << file1;
    //process.start(file);
    //process.execute(file); //i tried as well
    //system("start /ts_disable.vbs");
    QString script = "cscript";
    QStringList args;
    if (rdp_state==TRUE)
    {
        args<<QString(QDir::currentPath()+ "/ts_disable.vbs")<<"//NoLogo";
        ui->pushButton->setText("ENABLE RDP");
        rdp_state=FALSE;
    }
    else
    {
        args<<QString(QDir::currentPath()+ "/ts_enable.vbs")<<"//NoLogo";
        ui->pushButton->setText("DISABLE RDP");
        rdp_state=TRUE;
    }

    Process->start(script,args);
}
