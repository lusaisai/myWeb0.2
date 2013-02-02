/********************************************************************************
** Form generated from reading UI file 'connectdialog.ui'
**
** Created: Sat Feb 2 21:30:53 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTDIALOG_H
#define UI_CONNECTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_ConnectDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *mysqlHost;
    QLabel *label_2;
    QLineEdit *mysqlPort;
    QLabel *label_3;
    QLineEdit *mysqlDBName;
    QLabel *label_4;
    QLineEdit *mysqlUser;
    QLabel *label_5;
    QLineEdit *mysqlPasswd;
    QLabel *label_6;
    QLineEdit *topicTableName;
    QLabel *label_7;
    QLineEdit *listTableName;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *connectButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *ConnectDialog)
    {
        if (ConnectDialog->objectName().isEmpty())
            ConnectDialog->setObjectName(QString::fromUtf8("ConnectDialog"));
        ConnectDialog->resize(487, 296);
        gridLayout_2 = new QGridLayout(ConnectDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(ConnectDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        mysqlHost = new QLineEdit(ConnectDialog);
        mysqlHost->setObjectName(QString::fromUtf8("mysqlHost"));

        gridLayout->addWidget(mysqlHost, 0, 1, 1, 1);

        label_2 = new QLabel(ConnectDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        mysqlPort = new QLineEdit(ConnectDialog);
        mysqlPort->setObjectName(QString::fromUtf8("mysqlPort"));

        gridLayout->addWidget(mysqlPort, 1, 1, 1, 1);

        label_3 = new QLabel(ConnectDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        mysqlDBName = new QLineEdit(ConnectDialog);
        mysqlDBName->setObjectName(QString::fromUtf8("mysqlDBName"));

        gridLayout->addWidget(mysqlDBName, 2, 1, 1, 1);

        label_4 = new QLabel(ConnectDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        mysqlUser = new QLineEdit(ConnectDialog);
        mysqlUser->setObjectName(QString::fromUtf8("mysqlUser"));

        gridLayout->addWidget(mysqlUser, 3, 1, 1, 1);

        label_5 = new QLabel(ConnectDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        mysqlPasswd = new QLineEdit(ConnectDialog);
        mysqlPasswd->setObjectName(QString::fromUtf8("mysqlPasswd"));

        gridLayout->addWidget(mysqlPasswd, 4, 1, 1, 1);

        label_6 = new QLabel(ConnectDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        topicTableName = new QLineEdit(ConnectDialog);
        topicTableName->setObjectName(QString::fromUtf8("topicTableName"));

        gridLayout->addWidget(topicTableName, 5, 1, 1, 1);

        label_7 = new QLabel(ConnectDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        listTableName = new QLineEdit(ConnectDialog);
        listTableName->setObjectName(QString::fromUtf8("listTableName"));

        gridLayout->addWidget(listTableName, 6, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(134, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(282, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        connectButton = new QPushButton(ConnectDialog);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        horizontalLayout->addWidget(connectButton);

        cancelButton = new QPushButton(ConnectDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        gridLayout_2->addLayout(horizontalLayout, 1, 1, 1, 2);

        QWidget::setTabOrder(mysqlHost, mysqlPort);
        QWidget::setTabOrder(mysqlPort, mysqlDBName);
        QWidget::setTabOrder(mysqlDBName, mysqlUser);
        QWidget::setTabOrder(mysqlUser, mysqlPasswd);
        QWidget::setTabOrder(mysqlPasswd, topicTableName);
        QWidget::setTabOrder(topicTableName, listTableName);
        QWidget::setTabOrder(listTableName, connectButton);
        QWidget::setTabOrder(connectButton, cancelButton);

        retranslateUi(ConnectDialog);
        QObject::connect(cancelButton, SIGNAL(clicked()), ConnectDialog, SLOT(reject()));
        QObject::connect(connectButton, SIGNAL(clicked()), ConnectDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(ConnectDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectDialog)
    {
        ConnectDialog->setWindowTitle(QApplication::translate("ConnectDialog", "Connect", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ConnectDialog", "MYSQL Host:", 0, QApplication::UnicodeUTF8));
        mysqlHost->setText(QString());
        label_2->setText(QApplication::translate("ConnectDialog", "MYSQL Port:", 0, QApplication::UnicodeUTF8));
        mysqlPort->setText(QString());
        label_3->setText(QApplication::translate("ConnectDialog", "MYSQL DB Name:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ConnectDialog", "MYSQL User Name:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ConnectDialog", "MYSQL Password:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ConnectDialog", "Topic Table Name:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ConnectDialog", "List Table Name:", 0, QApplication::UnicodeUTF8));
        connectButton->setText(QApplication::translate("ConnectDialog", "Connect", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("ConnectDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConnectDialog: public Ui_ConnectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTDIALOG_H
