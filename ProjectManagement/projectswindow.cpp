#include "projectswindow.h"
#include "ui_projectswindow.h"
#include "createprojectwindow.h"
#include "data/database/database.h"
#include "mainwindow.h"
#include "QJsonArray"
#include "QJsonValue"
#include "QListWidgetItem"
#include <QMessageBox>

ProjectsWindow::ProjectsWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ProjectsWindow) {
    ui->setupUi(this);
    fillList();
}

ProjectsWindow::~ProjectsWindow() {
    delete ui;
}

void ProjectsWindow::on_create_project_button_clicked() {
    CreateProjectWindow *createProjectWindow = new CreateProjectWindow();
    createProjectWindow->show();

    connect(createProjectWindow, SIGNAL(changedEvent()), this, SLOT(changedEvent()));
}

void ProjectsWindow::on_close_button_clicked() {
    ProjectsWindow::close();
}

void ProjectsWindow::changedEvent() {
    fillList();
}

void ProjectsWindow::fillList() {
    ui->projects_list->clear();
    Database database;
    QJsonArray projects = database.get_projet_of_user(MainWindow::getUser().get_id());
    foreach(QJsonValue
    value, projects) {
        QListWidgetItem *widgetItem = new QListWidgetItem();
        widgetItem->setData(Qt::UserRole, value["id"].toInt());
        widgetItem->setText(value["name"].toString());
        ui->projects_list->addItem(widgetItem);
    }
}

void ProjectsWindow::on_close_button_2_clicked() {
    QListWidgetItem *widgetItem = ui->projects_list->currentItem();
    if (widgetItem != nullptr) {
        int id = widgetItem->data(Qt::UserRole).toInt();
        emit send_project_id(id);
        ProjectsWindow::close();
    } else {
        QMessageBox::warning(this, tr("Warning"), tr("Not Selected Project!"));
    }
}
