#ifndef REMOTE_H
#define REMOTE_H

#include <QDialog>

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
};

#endif // REMOTE_H
