#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "data/model/user.h"
#include "data/database/database.h"
#include "createaccountwindow.h"
#include "forgetpasswordwindow.h"
#include "mainwindow.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>

using namespace std;

LoginWindow::LoginWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::LoginWindow) {
    ui->setupUi(this);
}

LoginWindow::~LoginWindow() {
    delete ui;
}


void LoginWindow::on_create_account_button_clicked() {
    CreateAccountWindow *caw = new CreateAccountWindow(this);

    caw->show();

    connect(caw, SIGNAL(signal_username(QString)), this, SLOT(fill_username(QString)));
    connect(caw, SIGNAL(signal_password(QString)), this, SLOT(fill_password(QString)));

//    delete caw;
}


void LoginWindow::on_login_button_clicked() {


    if (ui->set_username->text() == "" || ui->set_pasword->text() == "") {
        QMessageBox::warning(this, tr("Warning"), tr("Please fill in all fields"));
    } else {
        User user;
        Database database;
        user = database.get_user(ui->set_username->text());

        if (user.get_username() != "") {
            if (user.get_password() == ui->set_pasword->text()) {
                MainWindow *mw = new MainWindow(user);
                mw->show();
                LoginWindow::close();
            } else {
                QMessageBox::warning(this, tr("Warning"), tr("Wrong Password"));
            }

        } else {
            QMessageBox::warning(this, tr("Warning"), tr("Username Is Not Exists"));
        }

    }
}


void LoginWindow::on_forget_password_Button_clicked() {
    ForgetPasswordWindow *fpw = new ForgetPasswordWindow();

    fpw->show();

    connect(fpw, SIGNAL(signal_username(QString)), this, SLOT(fill_username(QString)));
    connect(fpw, SIGNAL(signal_password(QString)), this, SLOT(fill_password(QString)));
}

void LoginWindow::fill_username(QString str_user) {
    ui->set_username->setText(str_user);
}

void LoginWindow::fill_password(QString str_pass) {
    ui->set_pasword->setText(str_pass);
}
