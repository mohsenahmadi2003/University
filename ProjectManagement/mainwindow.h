#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data/model/user.h"
#include "QListWidgetItem"
#include "data/model/task.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(User user, QWidget *parent = nullptr);

    ~MainWindow();

    static User getUser();

    static int get_id_porject();

    void show_tasks();


    signals:
            void send_id_project(int);
private
    slots:
            void changed_task();

    void on_logOutButton_clicked();

    void on_my_account_button_clicked();

    void on_my_project_button_clicked();

    void catch_id(int id);

    void on_add_member_button_clicked();

    void show_button();

    void on_add_task_button_clicked();

    void on_tasks_list_itemDoubleClicked(QListWidgetItem *item);

    void on_chat_button_clicked();

private:
    Ui::MainWindow *ui;
    static User user;
    static int id_project;
};
#endif // MAINWINDOW_H
