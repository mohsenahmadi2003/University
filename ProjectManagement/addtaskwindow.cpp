#include "addtaskwindow.h"
#include "ui_addtaskwindow.h"
#include "data/model/task.h"
#include "data/database/database.h"
#include "mainwindow.h"
#include "QMessageBox"
#include "mainwindow.h"


AddTaskWindow::AddTaskWindow(QWidget *parent, Task *task) :
        QDialog(parent),
        ui(new Ui::AddTaskWindow) {
    ui->setupUi(this);
    show_my_team();
    ui->delete_button->hide();
    this->task = Task();
    ui->doing_button->setChecked(true);
    if (task != nullptr) {
        this->task = *task;
        Database database;
        ui->save_button->setText("Edit");
        ui->delete_button->show();

        if (task->get_user_id() != -1 && task->get_user_id() != MainWindow::getUser().get_id() &&
            database.find_position(MainWindow::getUser().get_id(), MainWindow::get_id_porject()) == "member") {
            ui->finished_button->setEnabled(false);
            ui->doing_button->setEnabled(false);
            ui->save_button->setDisabled(true);
        }
        ui->assigned->setText(this->task.get_assignment());
        ui->task_name->setText(this->task.get_task_name());
        ui->task_description->setText(this->task.get_task_description());

        for (int i = 0; i < ui->my_team_list->count(); ++i) {
            if (ui->my_team_list->item(i)->data(Qt::UserRole).toInt() == this->task.get_user_id()) {
                ui->my_team_list->setCurrentRow(i);
                break;
            }
        }

        if (task->get_task_status() == "Doing") {
            ui->doing_button->setChecked(true);
        } else {
            ui->finished_button->setChecked(true);
        }


        QString position = database.find_position(MainWindow::getUser().get_id(), MainWindow::get_id_porject());
        if (position == "member") {
            ui->delete_button->setEnabled(false);
            ui->assigned->setEnabled(false);
            ui->task_name->setEnabled(false);
            ui->task_description->setEnabled(false);
            ui->my_team_list->setEnabled(false);
        }

    }


}

AddTaskWindow::~AddTaskWindow() {
    delete ui;
}

void AddTaskWindow::on_pushButton_2_clicked() {
    AddTaskWindow::close();
}

void AddTaskWindow::on_save_button_clicked() {
    Task new_task;
    Database database;
    if (ui->task_name->text() == "") {
        QMessageBox::warning(this, tr("Warning"), tr("The Name Is Null!"));
    } else if (ui->task_description->toPlainText() == "") {
        QMessageBox::warning(this, tr("Warning"), tr("The Description Is Null!"));
    } else {
        new_task.set_task_name(ui->task_name->text());
        new_task.set_task_description(ui->task_description->toPlainText());
        new_task.set_project_id(MainWindow::get_id_porject());
        new_task.set_user_id(ui->my_team_list->currentItem()->data(Qt::UserRole).toInt());
        new_task.set_assignment(ui->my_team_list->currentItem()->text());
        new_task.set_task_status((ui->finished_button->isChecked()) ? "Finished" : "Doing");
        if (task.get_task_id() == -1) {
            database.add_task(new_task);
        } else {
            new_task.set_task_id(task.get_task_id());
            database.edit_task_by_id(task.get_task_id(), new_task);
        }
        emit edit_task();
        AddTaskWindow::close();

    }


}

void AddTaskWindow::show_my_team() {
    Database databse;
    QJsonArray all_user = databse.get_my_team(MainWindow::get_id_porject());

    QListWidgetItem *widgetItem = new QListWidgetItem();
    widgetItem->setData(Qt::UserRole, -1);
    widgetItem->setText("No One");
    ui->my_team_list->addItem(widgetItem);
    foreach(QJsonValue
    value, all_user) {
        QListWidgetItem *widgetItem = new QListWidgetItem();
        widgetItem->setData(Qt::UserRole, value["id"].toInt());
        widgetItem->setText(value["username"].toString());
        ui->my_team_list->addItem(widgetItem);
    }
    ui->my_team_list->setCurrentRow(0);

}


void AddTaskWindow::on_my_team_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous) {
    ui->assigned->setText(current->text());
}

void AddTaskWindow::on_delete_button_clicked() {
    Database database;
    database.delete_task(task.get_task_id());
    emit edit_task();
    AddTaskWindow::close();
}
