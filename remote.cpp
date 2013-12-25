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
    ui->label->setVisible(FALSE);
    connect (ui->pushButton,SIGNAL(released()),this,SLOT(enable_disable_rdp()));
    connect (ui->pushButton_2,SIGNAL(released()),this,SLOT(create_tunnel()));

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

void Remote::create_tunnel()
{
    QString port=get_free_port();
    ui->label->setText(port);
    ui->label->setVisible(TRUE);
}

QString Remote::get_free_port()
{
    QProcess *Process=new QProcess;
    QString script = QDir::currentPath()+ "/plink.exe blackcat -l jim -pw dn1111";
    QString port;
    Process->start(script);
    qDebug()<<script;
    Process->waitForFinished(-1);
    QByteArray out = Process->readAllStandardOutput();
    for (int i=0;i<=sizeof(out);++i)
    {
        port=port+out[i];
    }
    return port;

}
