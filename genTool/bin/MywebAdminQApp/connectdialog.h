#ifndef CONNECT_H
#define CONNECT_H

#include <QDialog>
#include <QSettings>
#include "mainwindow.h"
#include "lib/mysqldeliver.hpp"

namespace Ui {
    class ConnectDialog;
}

class ConnectDialog : public QDialog {
    Q_OBJECT
public:
    explicit ConnectDialog(QWidget * parent = 0);
    ~ConnectDialog();
    void readSettings();
    void writeSettings();
    Im633::mysqldeliver *getConnection();

private:
    Ui::ConnectDialog *ui;
    QSettings settings;
};

#endif // CONNECT_H
