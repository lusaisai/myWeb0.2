#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QMessageBox>
#include <QStandardItem>
#include <QRegExp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    topicModel(new QStandardItemModel(parent)),
    topicFilter(new QSortFilterProxyModel(parent)),
    listModel(new QStandardItemModel(parent)),
    md(nullptr)
{
    ui->setupUi(this);

    // Add the icons
    ui->actionConnect->setIcon(QIcon(":/images/network_server_database.png"));
    ui->actionRefresh->setIcon(QIcon(":/images/refresh.png"));
    ui->actionExit->setIcon(QIcon(":/images/exit.png"));
    ui->actionAbout_mywebQApp->setIcon(QIcon(":/images/info.png"));
    ui->toolBar->addAction(ui->actionConnect);
    ui->toolBar->addAction(ui->actionRefresh);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionExit);
    move(550,100);

    // the topic views
    topicFilter->setSourceModel(topicModel);
    ui->topicTableView->setModel(topicFilter);
    //ui->topicTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // the list views
    ui->listTableView->setModel(listModel);

    // signals and slots
    connect( ui->actionConnect, SIGNAL(triggered()), this, SLOT(connect2mysql()) );
    connect( ui->actionAbout_mywebQApp, SIGNAL(triggered()), this, SLOT(about()) );
    connect( ui->actionExit, SIGNAL(triggered()), this, SLOT(close()) );

    // topics and lists
    connect( ui->actionRefresh, SIGNAL(triggered()), this, SLOT(load_topics()) );
    connect( ui->filterLineEdit, SIGNAL(textChanged(QString)), this, SLOT(filter_topics(QString)) );
    connect( ui->addTopicButton, SIGNAL(clicked()), this, SLOT(new_topic()) );
    connect( ui->saveTopicButton, SIGNAL(clicked()), this, SLOT(save_topic()) );
    connect( ui->deleteTopicButton, SIGNAL(clicked()), this, SLOT(delete_topic()) );
    connect( ui->EditTopicButton, SIGNAL(clicked()), this, SLOT(edit_topic()) );

    connect( ui->topicTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(load_lists()) );
    connect( ui->topicTableView, SIGNAL(activated(QModelIndex)), this, SLOT(load_lists()) );
    connect( ui->addListButton, SIGNAL(clicked()), this, SLOT(new_list()) );
    connect( ui->saveListButton, SIGNAL(clicked()), this, SLOT(save_list()) );
    connect( ui->deleteListButton, SIGNAL(clicked()), this, SLOT(delete_list()) );
    connect( ui->EditListButton, SIGNAL(clicked()), this, SLOT(edit_list()) );
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
           QMessageBox::information(this, "Connected", "Connected to MYSQL!");
       } catch ( std::exception & e ) {
           QMessageBox::warning(this, "Failed", e.what());
       }
    }
}

void MainWindow::about() {
    QMessageBox::about(this, QString("MywebAdminQApp"), QString("This is an application to add/edit/remove backend data for im633.com"));
}


bool MainWindow::testConnection() {
    if ( md == nullptr ) {
        QMessageBox::warning(this, "No Connection", "No connection established yet, please connect first!");
        return false;
    } else {
        return true;
    }

}

void MainWindow::load_topics() {
    if ( !testConnection() ) return;
    topicModel->clear();
    topicModel->setColumnCount(2);
    std::set<Im633::topic> all_topics = md->fetch_topic();
    topicModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Topic ID"));
    topicModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Topic Name"));
    for (auto it=all_topics.begin(); it != all_topics.end(); ++it) {
        topicModel->insertRow(0);
        topicModel->setData(topicModel->index(0, 0), QString::number( (*it).get_id() ));
        topicModel->setData(topicModel->index(0, 1), QString::fromUtf8( (*it).get_topic_name().c_str() ) );
    }
    ui->topicTableView->setColumnWidth(0,80);
    ui->topicTableView->setColumnWidth(1,250);
    ui->topicTableView->setCurrentIndex(ui->topicTableView->indexAt(QPoint(0,0)));

    load_lists();//load the list as well
}

void MainWindow::load_lists() {
    if ( !testConnection() ) return;
    listModel->clear();
    listModel->setColumnCount(2);
    std::set<Im633::list> lists = md->fetch_list(md->fetch_topic(selectedTopicID()));

    listModel->setHeaderData(0, Qt::Horizontal, QObject::tr("List ID"));
    listModel->setHeaderData(1, Qt::Horizontal, QObject::tr("List Name"));
    for (auto it=lists.begin(); it != lists.end(); ++it) {
        listModel->insertRow(0);
        listModel->setData(listModel->index(0, 0), QString::number( (*it).get_id() ));
        listModel->setData(listModel->index(0, 1), QString::fromUtf8( (*it).get_list_name().c_str() ) );
    }
    ui->listTableView->setColumnWidth(0,80);
    ui->listTableView->setColumnWidth(1,250);
    ui->listTableView->setCurrentIndex(ui->listTableView->indexAt(QPoint(0,0)));
}

void MainWindow::filter_topics( const QString & text ) {
    QRegExp regExp(text);
    topicFilter->setDynamicSortFilter(true);
    topicFilter->setFilterKeyColumn(1);
    topicFilter->setFilterRegExp(regExp);
    topicFilter->setFilterCaseSensitivity(Qt::CaseInsensitive);
}

void MainWindow::setFilledTopic(Im633::topic topic) {
    ui->topicIDEdit->setText( QString::number(topic.get_id()) );
    ui->topicTypeComboBox->setCurrentIndex(topic.get_topic_type().get_id() - 1);
    ui->topicNameEdit->setText(QString::fromUtf8(topic.get_topic_name().c_str()));
    ui->topicTagEdit->setText(QString::fromUtf8(topic.get_topic_tags().c_str()));
    ui->topicRecomComboBox->setCurrentIndex( topic.get_topic_recom_flag() == "N" ? 0 : 1 );
}

void MainWindow::setFilledList(Im633::list list) {
    ui->listIDEdit->setText( QString::number(list.get_id()) );
    ui->listTopicIDEdit->setText( QString::number(list.get_topic_id()) );
    ui->listNameEdit->setText(QString::fromUtf8(list.get_list_name().c_str()));
    ui->listImgLocEdit->setText(QString::fromUtf8(list.get_list_image_loc().c_str()));
    ui->listOuterLinkEdit->setText(QString::fromUtf8(list.get_list_outer_link().c_str()));
    ui->listOtherLinkEdit->setText(QString::fromUtf8(list.get_list_other_link().c_str()));
    ui->listDescEdit->setText(QString::fromUtf8(list.get_list_desc().c_str()));
}

Im633::topic MainWindow::getFilledTopic() {
    return Im633::topic(ui->topicIDEdit->text().toInt(),
                        ui->topicTypeComboBox->currentIndex() + 1,
                        ui->topicNameEdit->text().toUtf8().constData(),
                        ui->topicTagEdit->text().toUtf8().constData(),
                        ui->topicRecomComboBox->currentText().toStdString()
                );
}

Im633::list MainWindow::getFilledList() {
    return Im633::list(ui->listIDEdit->text().toInt(),
                       ui->listTopicIDEdit->text().toInt(),
                       ui->listNameEdit->text().toUtf8().constData(),
                       ui->listDescEdit->toPlainText().toUtf8().constData(),
                       ui->listImgLocEdit->text().toUtf8().constData(),
                       ui->listOuterLinkEdit->text().toUtf8().constData(),
                       ui->listOtherLinkEdit->text().toUtf8().constData()
                );
}


void MainWindow::new_topic() {
    if ( !testConnection() ) return;
    try {
       setFilledTopic(md->new_topic(Im633::topictype::get_topictype(1))); // default to music
    } catch ( std::exception & e ) {
        QMessageBox::warning(this, "Failed!", e.what());
    }

}


void MainWindow::new_list() {
    if ( !testConnection() ) return;
    try {
       setFilledList(md->new_list(md->fetch_topic(selectedTopicID())));
    } catch ( std::exception & e ) {
        QMessageBox::warning(this, "Failed!", e.what());
    }
}

void MainWindow::save_topic() {
    if ( !testConnection() ) return;
    Im633::topic topic = getFilledTopic();
    try {
        if ( md->topic_update(topic) == 0 ) {
            md->topic_delete(topic);
            md->topic_insert(topic);
        }
       QMessageBox::information(this, "Saved", "Topic Saved!");
       load_topics();
    } catch ( std::exception & e ) {
       QMessageBox::warning(this, "Failed!", e.what());
    }
}

void MainWindow::save_list() {
    if ( !testConnection() ) return;
    Im633::list list = getFilledList();
    try {
        if ( md->list_update(list) == 0 ) {
            md->list_delete(list);
            md->list_insert(list);
        }
       QMessageBox::information(this, "Saved", "List Saved!");
       load_lists();
    } catch ( std::exception & e ) {
       QMessageBox::warning(this, "Failed!", e.what());
    }
}

void MainWindow::delete_topic() {
    if ( !testConnection() ) return;
    if ( QMessageBox::question(this, "Confirm", "Are you sure you want to delete this topic?", QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Cancel ) return;
    try {
        md->topic_delete(md->fetch_topic(selectedTopicID()));
        QMessageBox::information(this, "Deleted", "Record Deleted!");
        load_topics();
    } catch ( std::exception & e ) {
        QMessageBox::warning(this, "Failed!", e.what());
    }
}

void MainWindow::delete_list() {
    if ( !testConnection() ) return;
    if ( QMessageBox::question(this, "Confirm", "Are you sure you want to delete this list?", QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Cancel ) return;
    try {
        md->list_delete(md->fetch_list(selectedListID()));
        QMessageBox::information(this, "Deleted", "Record Deleted!");
        load_lists();
    } catch ( std::exception & e ) {
        QMessageBox::warning(this, "Failed!", e.what());
    }
}

void MainWindow::edit_topic() {
    if ( !testConnection() ) return;
    try {
        setFilledTopic(md->fetch_topic(selectedTopicID()));
    } catch ( std::exception & e ) {
        QMessageBox::warning(this, "Failed!", e.what());
    }

}

void MainWindow::edit_list() {
    if ( !testConnection() ) return;
    try {
        setFilledList(md->fetch_list(selectedListID()));
    } catch ( std::exception & e ) {
        QMessageBox::warning(this, "Failed!", e.what());
    }

}

/*
* The util functions to get the current selected topic id and list id
*/
int MainWindow::selectedTopicID() {
    return topicFilter->index( ui->topicTableView->currentIndex().row(), 0 ).data().toInt();
}

int MainWindow::selectedListID() {
    return listModel->index( ui->listTableView->currentIndex().row(), 0 ).data().toInt();
}
