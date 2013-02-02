#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectdialog.h"
#include "lib/mysqldeliver.hpp"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QSortFilterProxyModel>

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
    void load_topics();
    void filter_topics( const QString & text );
    void new_topic();
    void save_topic();
    void delete_topic();
    void edit_topic();
    void load_lists();
    void new_list();
    void save_list();
    void delete_list();
    void edit_list();
    
private:
    Ui::MainWindow *ui;
    Im633::mysqldeliver * md;
    QStandardItemModel * topicModel;
    QSortFilterProxyModel * topicFilter;
    QStandardItemModel * listModel;

    bool testConnection();
    void setFilledTopic(Im633::topic topic);
    void setFilledList(Im633::list list);
    Im633::topic getFilledTopic();
    Im633::list getFilledList();
    int selectedTopicID();
    int selectedListID();

};

#endif // MAINWINDOW_H
