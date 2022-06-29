#ifndef LoginWindow_H
#define LoginWindow_H

#include <QMainWindow>
#include <QDialog>

namespace Ui {
    class LoginWindow;
}

class LoginWindow : public QDialog {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

    ~LoginWindow();


private
    slots:
            void fill_username(QString
    str_user);

    void fill_password(QString str_pass);

    void on_create_account_button_clicked();

    void on_login_button_clicked();


    void on_forget_password_Button_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LoginWindow_H
