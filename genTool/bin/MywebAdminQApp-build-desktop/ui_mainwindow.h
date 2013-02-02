/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Feb 2 21:30:53 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionRefresh;
    QAction *actionExit;
    QAction *actionAbout_mywebQApp;
    QWidget *centralwidget;
    QGridLayout *gridLayout_6;
    QGroupBox *topicGroupBox;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLineEdit *filterLineEdit;
    QTableView *topicTableView;
    QGridLayout *gridLayout;
    QLabel *topicType;
    QLineEdit *topicNameEdit;
    QLineEdit *topicTagEdit;
    QComboBox *topicTypeComboBox;
    QLabel *topicTags;
    QLabel *topicName;
    QComboBox *topicRecomComboBox;
    QLabel *topicRecomFlag;
    QLabel *topicID;
    QLineEdit *topicIDEdit;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *addTopicButton;
    QPushButton *deleteTopicButton;
    QPushButton *EditTopicButton;
    QPushButton *saveTopicButton;
    QSpacerItem *horizontalSpacer;
    QGroupBox *listGroupBox;
    QGridLayout *gridLayout_4;
    QTableView *listTableView;
    QGridLayout *gridLayout_3;
    QLabel *listID;
    QLineEdit *listIDEdit;
    QLabel *listTopicID;
    QLineEdit *listTopicIDEdit;
    QLabel *listName;
    QLineEdit *listNameEdit;
    QLabel *topicRecomFlag_2;
    QLineEdit *listImgLocEdit;
    QLabel *label;
    QLineEdit *listOuterLinkEdit;
    QLabel *label_2;
    QLineEdit *listOtherLinkEdit;
    QLabel *topicTags_2;
    QTextEdit *listDescEdit;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addListButton;
    QPushButton *deleteListButton;
    QPushButton *EditListButton;
    QPushButton *saveListButton;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(879, 886);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        actionRefresh = new QAction(MainWindow);
        actionRefresh->setObjectName(QString::fromUtf8("actionRefresh"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAbout_mywebQApp = new QAction(MainWindow);
        actionAbout_mywebQApp->setObjectName(QString::fromUtf8("actionAbout_mywebQApp"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_6 = new QGridLayout(centralwidget);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        topicGroupBox = new QGroupBox(centralwidget);
        topicGroupBox->setObjectName(QString::fromUtf8("topicGroupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(topicGroupBox->sizePolicy().hasHeightForWidth());
        topicGroupBox->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(topicGroupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_3 = new QLabel(topicGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        filterLineEdit = new QLineEdit(topicGroupBox);
        filterLineEdit->setObjectName(QString::fromUtf8("filterLineEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(filterLineEdit->sizePolicy().hasHeightForWidth());
        filterLineEdit->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(filterLineEdit, 0, 1, 1, 1);

        topicTableView = new QTableView(topicGroupBox);
        topicTableView->setObjectName(QString::fromUtf8("topicTableView"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(topicTableView->sizePolicy().hasHeightForWidth());
        topicTableView->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(topicTableView, 1, 0, 1, 2);


        gridLayout_5->addLayout(gridLayout_2, 0, 0, 2, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        topicType = new QLabel(topicGroupBox);
        topicType->setObjectName(QString::fromUtf8("topicType"));

        gridLayout->addWidget(topicType, 1, 0, 1, 1);

        topicNameEdit = new QLineEdit(topicGroupBox);
        topicNameEdit->setObjectName(QString::fromUtf8("topicNameEdit"));

        gridLayout->addWidget(topicNameEdit, 2, 1, 1, 1);

        topicTagEdit = new QLineEdit(topicGroupBox);
        topicTagEdit->setObjectName(QString::fromUtf8("topicTagEdit"));

        gridLayout->addWidget(topicTagEdit, 3, 1, 1, 1);

        topicTypeComboBox = new QComboBox(topicGroupBox);
        topicTypeComboBox->setObjectName(QString::fromUtf8("topicTypeComboBox"));

        gridLayout->addWidget(topicTypeComboBox, 1, 1, 1, 1);

        topicTags = new QLabel(topicGroupBox);
        topicTags->setObjectName(QString::fromUtf8("topicTags"));

        gridLayout->addWidget(topicTags, 3, 0, 1, 1);

        topicName = new QLabel(topicGroupBox);
        topicName->setObjectName(QString::fromUtf8("topicName"));

        gridLayout->addWidget(topicName, 2, 0, 1, 1);

        topicRecomComboBox = new QComboBox(topicGroupBox);
        topicRecomComboBox->setObjectName(QString::fromUtf8("topicRecomComboBox"));

        gridLayout->addWidget(topicRecomComboBox, 4, 1, 1, 1);

        topicRecomFlag = new QLabel(topicGroupBox);
        topicRecomFlag->setObjectName(QString::fromUtf8("topicRecomFlag"));

        gridLayout->addWidget(topicRecomFlag, 4, 0, 1, 1);

        topicID = new QLabel(topicGroupBox);
        topicID->setObjectName(QString::fromUtf8("topicID"));

        gridLayout->addWidget(topicID, 0, 0, 1, 1);

        topicIDEdit = new QLineEdit(topicGroupBox);
        topicIDEdit->setObjectName(QString::fromUtf8("topicIDEdit"));
        topicIDEdit->setReadOnly(false);

        gridLayout->addWidget(topicIDEdit, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout, 1, 1, 1, 1);


        gridLayout_6->addWidget(topicGroupBox, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addTopicButton = new QPushButton(centralwidget);
        addTopicButton->setObjectName(QString::fromUtf8("addTopicButton"));

        horizontalLayout->addWidget(addTopicButton);

        deleteTopicButton = new QPushButton(centralwidget);
        deleteTopicButton->setObjectName(QString::fromUtf8("deleteTopicButton"));

        horizontalLayout->addWidget(deleteTopicButton);

        EditTopicButton = new QPushButton(centralwidget);
        EditTopicButton->setObjectName(QString::fromUtf8("EditTopicButton"));

        horizontalLayout->addWidget(EditTopicButton);

        saveTopicButton = new QPushButton(centralwidget);
        saveTopicButton->setObjectName(QString::fromUtf8("saveTopicButton"));

        horizontalLayout->addWidget(saveTopicButton);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(248, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        gridLayout_6->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        listGroupBox = new QGroupBox(centralwidget);
        listGroupBox->setObjectName(QString::fromUtf8("listGroupBox"));
        gridLayout_4 = new QGridLayout(listGroupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        listTableView = new QTableView(listGroupBox);
        listTableView->setObjectName(QString::fromUtf8("listTableView"));
        sizePolicy3.setHeightForWidth(listTableView->sizePolicy().hasHeightForWidth());
        listTableView->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(listTableView, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        listID = new QLabel(listGroupBox);
        listID->setObjectName(QString::fromUtf8("listID"));

        gridLayout_3->addWidget(listID, 0, 0, 1, 1);

        listIDEdit = new QLineEdit(listGroupBox);
        listIDEdit->setObjectName(QString::fromUtf8("listIDEdit"));

        gridLayout_3->addWidget(listIDEdit, 0, 1, 1, 1);

        listTopicID = new QLabel(listGroupBox);
        listTopicID->setObjectName(QString::fromUtf8("listTopicID"));

        gridLayout_3->addWidget(listTopicID, 1, 0, 1, 1);

        listTopicIDEdit = new QLineEdit(listGroupBox);
        listTopicIDEdit->setObjectName(QString::fromUtf8("listTopicIDEdit"));

        gridLayout_3->addWidget(listTopicIDEdit, 1, 1, 1, 1);

        listName = new QLabel(listGroupBox);
        listName->setObjectName(QString::fromUtf8("listName"));

        gridLayout_3->addWidget(listName, 2, 0, 1, 1);

        listNameEdit = new QLineEdit(listGroupBox);
        listNameEdit->setObjectName(QString::fromUtf8("listNameEdit"));

        gridLayout_3->addWidget(listNameEdit, 2, 1, 1, 1);

        topicRecomFlag_2 = new QLabel(listGroupBox);
        topicRecomFlag_2->setObjectName(QString::fromUtf8("topicRecomFlag_2"));

        gridLayout_3->addWidget(topicRecomFlag_2, 3, 0, 1, 1);

        listImgLocEdit = new QLineEdit(listGroupBox);
        listImgLocEdit->setObjectName(QString::fromUtf8("listImgLocEdit"));

        gridLayout_3->addWidget(listImgLocEdit, 3, 1, 1, 1);

        label = new QLabel(listGroupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 4, 0, 1, 1);

        listOuterLinkEdit = new QLineEdit(listGroupBox);
        listOuterLinkEdit->setObjectName(QString::fromUtf8("listOuterLinkEdit"));

        gridLayout_3->addWidget(listOuterLinkEdit, 4, 1, 1, 1);

        label_2 = new QLabel(listGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 5, 0, 1, 1);

        listOtherLinkEdit = new QLineEdit(listGroupBox);
        listOtherLinkEdit->setObjectName(QString::fromUtf8("listOtherLinkEdit"));

        gridLayout_3->addWidget(listOtherLinkEdit, 5, 1, 1, 1);

        topicTags_2 = new QLabel(listGroupBox);
        topicTags_2->setObjectName(QString::fromUtf8("topicTags_2"));

        gridLayout_3->addWidget(topicTags_2, 6, 0, 1, 1);

        listDescEdit = new QTextEdit(listGroupBox);
        listDescEdit->setObjectName(QString::fromUtf8("listDescEdit"));

        gridLayout_3->addWidget(listDescEdit, 6, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 1, 1, 1);


        gridLayout_6->addWidget(listGroupBox, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        addListButton = new QPushButton(centralwidget);
        addListButton->setObjectName(QString::fromUtf8("addListButton"));

        horizontalLayout_2->addWidget(addListButton);

        deleteListButton = new QPushButton(centralwidget);
        deleteListButton->setObjectName(QString::fromUtf8("deleteListButton"));

        horizontalLayout_2->addWidget(deleteListButton);

        EditListButton = new QPushButton(centralwidget);
        EditListButton->setObjectName(QString::fromUtf8("EditListButton"));

        horizontalLayout_2->addWidget(EditListButton);

        saveListButton = new QPushButton(centralwidget);
        saveListButton->setObjectName(QString::fromUtf8("saveListButton"));

        horizontalLayout_2->addWidget(saveListButton);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(375, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        gridLayout_6->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 879, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        QWidget::setTabOrder(topicTableView, topicIDEdit);
        QWidget::setTabOrder(topicIDEdit, topicTypeComboBox);
        QWidget::setTabOrder(topicTypeComboBox, topicNameEdit);
        QWidget::setTabOrder(topicNameEdit, topicTagEdit);
        QWidget::setTabOrder(topicTagEdit, topicRecomComboBox);
        QWidget::setTabOrder(topicRecomComboBox, addTopicButton);
        QWidget::setTabOrder(addTopicButton, deleteTopicButton);
        QWidget::setTabOrder(deleteTopicButton, EditTopicButton);
        QWidget::setTabOrder(EditTopicButton, saveTopicButton);
        QWidget::setTabOrder(saveTopicButton, listTableView);
        QWidget::setTabOrder(listTableView, listIDEdit);
        QWidget::setTabOrder(listIDEdit, listTopicIDEdit);
        QWidget::setTabOrder(listTopicIDEdit, listNameEdit);
        QWidget::setTabOrder(listNameEdit, listImgLocEdit);
        QWidget::setTabOrder(listImgLocEdit, listOuterLinkEdit);
        QWidget::setTabOrder(listOuterLinkEdit, listOtherLinkEdit);
        QWidget::setTabOrder(listOtherLinkEdit, listDescEdit);
        QWidget::setTabOrder(listDescEdit, addListButton);
        QWidget::setTabOrder(addListButton, deleteListButton);
        QWidget::setTabOrder(deleteListButton, EditListButton);
        QWidget::setTabOrder(EditListButton, saveListButton);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionConnect);
        menuFile->addAction(actionRefresh);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuAbout->addAction(actionAbout_mywebQApp);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MywebAdminQApp", 0, QApplication::UnicodeUTF8));
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        actionRefresh->setText(QApplication::translate("MainWindow", "Refresh", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionAbout_mywebQApp->setText(QApplication::translate("MainWindow", "About mywebQApp", 0, QApplication::UnicodeUTF8));
        topicGroupBox->setTitle(QApplication::translate("MainWindow", "Topic", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Filter:", 0, QApplication::UnicodeUTF8));
        topicType->setText(QApplication::translate("MainWindow", "topic type:", 0, QApplication::UnicodeUTF8));
        topicTypeComboBox->clear();
        topicTypeComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "music", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "video", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "soccer", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "fun", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "software", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "blog", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "others", 0, QApplication::UnicodeUTF8)
        );
        topicTags->setText(QApplication::translate("MainWindow", "topic tags:", 0, QApplication::UnicodeUTF8));
        topicName->setText(QApplication::translate("MainWindow", "topic name:", 0, QApplication::UnicodeUTF8));
        topicRecomComboBox->clear();
        topicRecomComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "N", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Y", 0, QApplication::UnicodeUTF8)
        );
        topicRecomFlag->setText(QApplication::translate("MainWindow", "topic recommend:", 0, QApplication::UnicodeUTF8));
        topicID->setText(QApplication::translate("MainWindow", "topic id:", 0, QApplication::UnicodeUTF8));
        addTopicButton->setText(QApplication::translate("MainWindow", "Add Topic", 0, QApplication::UnicodeUTF8));
        deleteTopicButton->setText(QApplication::translate("MainWindow", "Delete Topic", 0, QApplication::UnicodeUTF8));
        EditTopicButton->setText(QApplication::translate("MainWindow", "Edit Topic", 0, QApplication::UnicodeUTF8));
        saveTopicButton->setText(QApplication::translate("MainWindow", "Save Topic", 0, QApplication::UnicodeUTF8));
        listGroupBox->setTitle(QApplication::translate("MainWindow", "List", 0, QApplication::UnicodeUTF8));
        listID->setText(QApplication::translate("MainWindow", "list id:", 0, QApplication::UnicodeUTF8));
        listTopicID->setText(QApplication::translate("MainWindow", "topic id:", 0, QApplication::UnicodeUTF8));
        listName->setText(QApplication::translate("MainWindow", "list name:", 0, QApplication::UnicodeUTF8));
        topicRecomFlag_2->setText(QApplication::translate("MainWindow", "list image location: ", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "list outer link:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "list other link:", 0, QApplication::UnicodeUTF8));
        topicTags_2->setText(QApplication::translate("MainWindow", "list description:", 0, QApplication::UnicodeUTF8));
        addListButton->setText(QApplication::translate("MainWindow", "Add List", 0, QApplication::UnicodeUTF8));
        deleteListButton->setText(QApplication::translate("MainWindow", "Delete List", 0, QApplication::UnicodeUTF8));
        EditListButton->setText(QApplication::translate("MainWindow", "Edit List", 0, QApplication::UnicodeUTF8));
        saveListButton->setText(QApplication::translate("MainWindow", "Save List", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
