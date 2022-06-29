#include "addmemberwindow.h"
#include "ui_addmemberwindow.h"
#include "data/database/database.h"
#include "QJsonArray"
#include "data/model/user.h"
#include "QJsonObject"
#include "QListWidgetItem"
#include <QMessageBox>
#include "mainwindow.h"
#include "data/model/project.h"
#include <QJsonDocument>
#include <QFile>



AddMemberWindow::AddMemberWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::AddMemberWindow) {
    ui->setupUi(this);
    show_my_team();
    show_all_user();
}

AddMemberWindow::~AddMemberWindow() {
    delete ui;
}

void AddMemberWindow::show_all_user() {
    Database database;
    QJsonArray all_user = database.get_users();
    foreach(QJsonValue
    value, all_user) {
        QListWidgetItem *widgetItem = new QListWidgetItem();
        widgetItem->setData(Qt::UserRole, value["id"].toInt());
        widgetItem->setText(value["username"].toString());
        ui->all_user_list->addItem(widgetItem);

    }


}

void AddMemberWindow::show_my_team() {
    Database databse;
    QJsonArray all_user = databse.get_my_team(MainWindow::get_id_porject());
    foreach(QJsonValue
    value, all_user) {
        QListWidgetItem *widgetItem = new QListWidgetItem();
        widgetItem->setData(Qt::UserRole, value["id"].toInt());
        widgetItem->setData(1, value["position"].toString());
        widgetItem->setText(value["username"].toString());
        ui->my_team_list->addItem(widgetItem);
    }
}


void AddMemberWindow::on_add_member_button_clicked() {

    bool isExist = false;
    for (int i = 0; i < ui->my_team_list->count(); i++) {
        if (ui->my_team_list->item(i)->data(Qt::UserRole) == ui->all_user_list->currentItem()->data(Qt::UserRole)) {
            isExist = true;
            break;
        }
    }
    if (!isExist) {
        QListWidgetItem *widgetItem = new QListWidgetItem(*(ui->all_user_list->currentItem()));
        widgetItem->setData(1, "member");

        ui->my_team_list->addItem(widgetItem);
    }

}

void AddMemberWindow::on_cancel_button_clicked() {
    AddMemberWindow::close();
}

void AddMemberWindow::on_my_team_list_itemDoubleClicked(QListWidgetItem *item) {

    if (item->data(1).toString() != "leader")
        delete ui->my_team_list->takeItem(ui->my_team_list->row(item));

}

void AddMemberWindow::on_save_button_clicked() {
    Database database;
    Project project = database.get_project_by_id(MainWindow::get_id_porject());
    QJsonArray members;
    for (int i = 0; i < ui->my_team_list->count(); i++) {
        QJsonObject newMember;
        newMember["position"] = ui->my_team_list->item(i)->data(1).toString();
        newMember["user_id"] = ui->my_team_list->item(i)->data(Qt::UserRole).toInt();
        members.append(newMember);
    }
    project.setMembers(members);
    database.edit_project_by_id(project, MainWindow::get_id_porject());
    AddMemberWindow::close();
}

void AddMemberWindow::on_add_elder_button_clicked() {
    bool isExist = false;
    for (int i = 0; i < ui->my_team_list->count(); i++) {
        if (ui->my_team_list->item(i)->data(Qt::UserRole) == ui->all_user_list->currentItem()->data(Qt::UserRole)) {
            isExist = true;
            break;
        }
    }
    if (!isExist) {
        QListWidgetItem *widgetItem = new QListWidgetItem(*(ui->all_user_list->currentItem()));
        widgetItem->setData(1, "elder");
        ui->my_team_list->addItem(widgetItem);
    }

}
