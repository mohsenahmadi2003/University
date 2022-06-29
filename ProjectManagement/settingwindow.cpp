#include "settingwindow.h"
#include "ui_settingwindow.h"
#include "data/database/database.h"
#include "data/model/user.h"
#include "mainwindow.h"
#include "utils/exception.h"
#include <QMessageBox>
#include <QDebug>


SettingWindow::SettingWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::SettingWindow) {
    ui->setupUi(this);

    User user;
    Database database;
    user = database.get_user_by_id((MainWindow::getUser().get_id()));
    ui->name->setText(user.get_name());
    ui->username->setText(user.get_username());
    ui->password->setText(user.get_password());
    ui->email->setText(user.get_email());
    ui->phonenumber->setText(user.get_phone_number());

}

SettingWindow::~SettingWindow() {
    delete ui;
}


void SettingWindow::on_save_button_clicked() {
    if (ui->name->text() == "") {
        QMessageBox::warning(this, tr("Warning"), tr("The Name Is Null!"));
    } else if (ui->username->text() == "") {
        QMessageBox::warning(this, tr("Warning"), tr("The Username Is Null!"));
    } else if (ui->password->text() == "") {
        QMessageBox::warning(this, tr("Warning"), tr("The Password Is Null!"));
    } else if (ui->email->text() == "") {
        QMessageBox::warning(this, tr("Warning"), tr("The Email Is Null!"));
    } else if (ui->phonenumber->text() == "") {
        QMessageBox::warning(this, tr("Warning"), tr("The Phone Number Is Null!"));
    } else {

        User user;
        Database database;
        user = database.get_user_by_id((MainWindow::getUser().get_id()));
        user.set_name(ui->name->text());
        user.set_username(ui->username->text());
        user.set_password(ui->password->text());
        user.set_email(ui->email->text());
        user.set_phone_number(ui->phonenumber->text());

        try {

            database.edit_user_by_id(MainWindow::getUser().get_id(), user);
            QMessageBox::information(this, tr("Notice"), tr("Changes Saved"));
            SettingWindow::on_pushButton_2_clicked();

        } catch (Exception e) {
            QMessageBox::warning(this, tr("Warning"), e.get_message());
        }
    }
}

void SettingWindow::on_pushButton_2_clicked() {
    SettingWindow::close();
}
