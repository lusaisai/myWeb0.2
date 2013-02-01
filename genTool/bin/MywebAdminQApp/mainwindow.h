#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectdialog.h"
#include "lib/mysqldeliver.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void connect2mysql();
    void about();
    
private:
    Ui::MainWindow *ui;
    Im633::mysqldeliver * md;
};

#endif // MAINWINDOW_H
