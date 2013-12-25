#ifndef REMOTE_H
#define REMOTE_H

#include <QDialog>
#include <QDebug>

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
    bool rdp_state;
    QString get_free_port();

private slots:
    void enable_disable_rdp();
    void create_tunnel();
};

#endif // REMOTE_H
