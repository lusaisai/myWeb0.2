#include "connectdialog.h"
#include "ui_connectdialog.h"
#include <QObject>

ConnectDialog::ConnectDialog(QWidget *parent):
    QDialog(parent), ui(new Ui::ConnectDialog), settings("connect.ini", QSettings::IniFormat)
{
    ui->setupUi(this);
    ui->mysqlPasswd->setEchoMode(QLineEdit::Password);
}

ConnectDialog::~ConnectDialog() {
    delete ui;
}

void ConnectDialog::readSettings(){
    ui->mysqlHost->setText( settings.value("host").toString() );
    ui->mysqlPort->setText( settings.value("port").toString() );
    ui->mysqlDBName->setText( settings.value("db").toString() );
    ui->mysqlUser->setText( settings.value("user").toString() );
    ui->mysqlPasswd->setText( settings.value("passwd").toString() );
    ui->topicTableName->setText( settings.value("topic_table_name").toString() );
    ui->listTableName->setText( settings.value("list_table_name").toString() );
}

void ConnectDialog::writeSettings() {
    settings.setValue( "host", ui->mysqlHost->text() );
    settings.setValue( "port", ui->mysqlPort->text() );
    settings.setValue( "db", ui->mysqlDBName->text() );
    settings.setValue( "user", ui->mysqlUser->text() );
    settings.setValue( "passwd", ui->mysqlPasswd->text() );
    settings.setValue( "topic_table_name", ui->topicTableName->text() );
    settings.setValue( "list_table_name", ui->listTableName->text() );
}

Im633::mysqldeliver * ConnectDialog::getConnection() {
    return new Im633::mysqldeliver( ui->mysqlDBName->text().toStdString().c_str(),
                                ui->topicTableName->text().toStdString(),
                                ui->listTableName->text().toStdString(),
                                ui->mysqlUser->text().toStdString().c_str(),
                                ui->mysqlPasswd->text().toStdString().c_str(),
                                ui->mysqlHost->text().toStdString().c_str(),
                                ui->mysqlPort->text().toInt());
}
