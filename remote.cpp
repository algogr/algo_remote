#include "remote.h"
#include "ui_remote.h"


Remote::Remote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Remote)
{
    ui->setupUi(this);
    settingsFile = (QDir::currentPath()+ "/remote.ini");
    QSettings settings(settingsFile,QSettings::IniFormat);
    sshServer=settings.value("sshServer").toString();
    sshUser=settings.value("sshUser").toString();
    sshPwd=settings.value("sshPwd").toString();
    sshCommand=settings.value("sshCommand").toString();
    rdpState=FALSE;
    ui->label->setVisible(FALSE);
    noofProcs=0;
    connect (ui->pushButton,SIGNAL(released()),this,SLOT(enabledisableRdp()));
    connect (ui->pushButton_2,SIGNAL(released()),this,SLOT(createTunnel()));

}

Remote::~Remote()
{
    //Delete plink running processes and free the server
    if (noofProcs>0)
    {
    for (int i=0;i<noofProcs;++i)
    {
        delete runningProcs[i];
    }
    }

    delete ui;

}

void Remote::enabledisableRdp()
{
    QProcess *Process=new QProcess;

    //CScript is needed to execute VBS code
    QString script = "cscript";
    QStringList args;
    if (rdpState==TRUE)
    {
        args<<QString(QDir::currentPath()+ "/ts_disable.vbs")<<"//NoLogo";
        ui->pushButton->setText("ENABLE RDP");
        rdpState=FALSE;
    }
    else
    {
        args<<QString(QDir::currentPath()+ "/ts_enable.vbs")<<"//NoLogo";
        ui->pushButton->setText("DISABLE RDP");
        rdpState=TRUE;
    }

    Process->start(script,args);
}

void Remote::createTunnel()
{
    QString port=getFreePort();
    ui->label->setVisible(TRUE);
    if (port==0)
    {
        ui->label->setText("No ports available...");
        return;
    }
    else
        ui->label->setText(port);


    remoteForward(port);
    return;


}

QString Remote::getFreePort()
{
    QProcess *Process=new QProcess;
    QString script = QDir::currentPath()+ "/plink.exe -ssh "+sshServer+ \
            " -l "+sshUser+" -pw "+sshPwd +" "+sshCommand;
    QString port;
    Process->start(script);
    qDebug()<<script;
    Process->waitForFinished(-1);
    QByteArray out = Process->readAllStandardOutput();
    for (int i=0;i<=sizeof(out);i++)
    {
        qDebug()<<i<<out[i];
        port=port+out[i];
    }
    delete Process;
    return port;

}


void Remote::remoteForward(QString port)
{
    QProcess *Process=new QProcess;
    runningProcs[noofProcs]=Process;
    QString script = QDir::currentPath()+ "/plink.exe -R "+port+":localhost:3389 -ssh "+ sshServer+" -l "+sshUser+" -pw "+sshPwd;
    Process->start(script);
    qDebug()<<script;
    ++noofProcs;

    return;
}
