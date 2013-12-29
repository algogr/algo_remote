#include <QtGui/QApplication>
#include "remote.h"
#include <QFile>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Remote w;
    QFile st(QDir::currentPath()+ "/remote.ini");
    if(!st.open(QIODevice::ReadOnly | QIODevice::Text))

    {
        cout<<"Need remote.ini to start";
        QString settingsFile = (QDir::currentPath()+ "/remote.ini");
        QSettings *settings =new QSettings(settingsFile,QSettings::IniFormat);
        settings->setValue("sshServer", "192.168.1.1");
        settings->setValue("sshUser", "user");
        settings->setValue("sshPwd", "123");
        settings->setValue("sshCommand", "free_port.sh");
        settings->sync();
        delete (settings);
    }
    st.close();

    w.setStyleSheet("background-image: url(:/suspects.png)");
    w.show();
    
    return a.exec();
}
