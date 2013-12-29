#ifndef REMOTE_H
#define REMOTE_H

#include <QDialog>
#include <QDebug>
#include "QProcess"
#include "QDir"
#include <QSettings>
namespace Ui {
class Remote;
}

class Remote : public QDialog
{
    Q_OBJECT
    
public:
    explicit Remote(QWidget *parent = 0);
    ~Remote();
    
private:
    Ui::Remote *ui;
    bool rdpState;
    QProcess *runningProcs[10];
    QString getFreePort();
    void remoteForward(QString port);
    int noofProcs;
    QString settingsFile;
    QString sshServer;
    QString sshUser;
    QString sshPwd;
    QString sshCommand;

private slots:
    void enabledisableRdp();
    void createTunnel();
};

#endif // REMOTE_H
