#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Add the icons
    ui->actionConnect->setIcon(QIcon(":/images/network_server_database.png"));
    ui->actionRefresh->setIcon(QIcon(":/images/refresh.png"));
    ui->toolBar->addAction(ui->actionConnect);
    ui->toolBar->addAction(ui->actionRefresh);
    move(550,100);


    // signals and slots
    connect( ui->actionConnect, SIGNAL(triggered()), this, SLOT(connect2mysql()) );
    connect( ui->actionAbout_mywebQApp, SIGNAL(triggered()), this, SLOT(about()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connect2mysql() {
    ConnectDialog cd(this);
    cd.readSettings();

    if ( cd.exec() == QDialog::Accepted ) {
       cd.writeSettings();
       try {
           md = cd.getConnection();
       } catch ( std::exception & e ) {
           QMessageBox msgBox;
           msgBox.setText(e.what());
           msgBox.exec();
       }
    }
}

void MainWindow::about() {
    QMessageBox::about(this, QString("MywebAdminQApp"), QString("This is an applications to add/edit/remove backend data for im633.com"));
}
