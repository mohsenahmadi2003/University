#include "createprojectwindow.h"
#include "ui_createprojectwindow.h"
#include "data/database/database.h"
#include "data/model/project.h"
#include "data/model/user.h"
#include "mainwindow.h"
#include <QMessageBox>

CreateProjectWindow::CreateProjectWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::CreateProjectWindow) {
    ui->setupUi(this);
}

CreateProjectWindow::~CreateProjectWindow() {
    delete ui;
}

void CreateProjectWindow::on_save_button_clicked() {
    if (ui->name_project_edit->text() != "") {
        Project project;
        project.setName(ui->name_project_edit->text());
        Database database;
        database.add_project(project, MainWindow::getUser().get_id());
//        database.edit_user_by_id(MainWindow::getUser().get_id(),)
        emit changedEvent();
        CreateProjectWindow::close();
    } else {
        QMessageBox::warning(this, tr("Warning"), tr("Please fill in all fields"));
    }
}

void CreateProjectWindow::on_close_button_clicked() {
    CreateProjectWindow::close();
}
