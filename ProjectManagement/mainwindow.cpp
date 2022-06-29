#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data/model/user.h"
#include "loginwindow.h"
#include "settingwindow.h"
#include "projectswindow.h"
#include "QJsonArray"
#include "QString"
#include "addmemberwindow.h"
#include "data/database/database.h"
#include "addtaskwindow.h"
#include "QJsonArray"
#include "QJsonValue"
#include "chatwindow.h"

#include <iostream>

using namespace std;

MainWindow::MainWindow(User user, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->user = user;
    ui->setupUi(this);

    id_project = -1;

    if (id_project == -1) {
        ui->project_name->setStyleSheet("color: rgb(255,25,25)");
        ui->project_name->setText("No project selected");
        ui->your_position->setStyleSheet("color: rgb(255,25,25)");
        ui->your_position->setText("No Position");
        ui->add_task_button->setDisabled(true);
        ui->add_member_button->setDisabled(true);
        ui->chat_button->setDisabled(true);

    }


}

MainWindow::~MainWindow() {
    delete ui;
}

User MainWindow::getUser() {
    return user;
}

int MainWindow::get_id_porject() {
    return id_project;
}

void MainWindow::show_tasks() {
    ui->tasks_list->clear();

    Database database;
    QJsonArray tasks = database.get_tasks();

    foreach(QJsonValue
    value, tasks) {
        if (value["project_id"].toInt() == get_id_porject()) {
            QListWidgetItem *widgetItem = new QListWidgetItem();
            widgetItem->setData(Qt::UserRole, value);
            widgetItem->setText("Task Name: " + value["name"].toString() + "\tAssignment:  " +
                                value["assignment"].toString() + "\tStatus:  " +
                                value["status"].toString());
            ui->tasks_list->addItem(widgetItem);
        }

    }

}

void MainWindow::changed_task() {
    show_tasks();
}

User MainWindow::user = User();

int MainWindow::id_project = -1;

void MainWindow::on_logOutButton_clicked() {
    LoginWindow *loginWindow = new LoginWindow();
    loginWindow->show();
    MainWindow::close();
}

void MainWindow::on_my_account_button_clicked() {
    SettingWindow *sw = new SettingWindow(this);

    sw->show();
}

void MainWindow::on_my_project_button_clicked() {
    ProjectsWindow *projectsWindow = new ProjectsWindow();
    projectsWindow->show();

    connect(projectsWindow, SIGNAL(send_project_id(int)), this, SLOT(catch_id(int)));

}

void MainWindow::catch_id(int id) {
    id_project = id;
    Database database;
    Project project = database.get_project_by_id(id);
    ui->project_name->setStyleSheet("color: rgb(0,0,0)");
    ui->project_name->setText(project.getName());
    ui->your_position->setStyleSheet("color: rgb(0,0,0)");
    ui->your_position->setText(database.find_position(user.get_id(), id));
    show_button();
    show_tasks();
}


void MainWindow::on_add_member_button_clicked() {
    AddMemberWindow *amw = new AddMemberWindow(this);
    amw->show();

}

void MainWindow::show_button() {
    Database database;

    if (database.find_position(user.get_id(), get_id_porject()) == "leader") {
        ui->add_task_button->setEnabled(true);
        ui->add_member_button->setEnabled(true);
        ui->chat_button->setEnabled(true);

    } else if (database.find_position(user.get_id(), get_id_porject()) == "elder") {
        ui->chat_button->setEnabled(true);
        ui->add_task_button->setEnabled(true);
    } else {
        ui->chat_button->setEnabled(true);
    }

}


void MainWindow::on_add_task_button_clicked() {
    AddTaskWindow *atw = new AddTaskWindow(this, nullptr);
    atw->show();
    connect(atw, SIGNAL(edit_task()), this, SLOT(changed_task()));
}


void MainWindow::on_tasks_list_itemDoubleClicked(QListWidgetItem *item) {
    Task task;
    task = task.fromJsonObject(item->data(Qt::UserRole).toJsonObject());
    AddTaskWindow *atw = new AddTaskWindow(this, &task);
    atw->show();
    connect(atw, SIGNAL(edit_task()), this, SLOT(changed_task()));
}

void MainWindow::on_chat_button_clicked()
{
    ChatWindow *cw = new ChatWindow(this);
    cw->show();
}
