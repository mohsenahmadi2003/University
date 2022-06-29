#ifndef FORGETPASSWORDWINDOW_H
#define FORGETPASSWORDWINDOW_H

#include <QDialog>

namespace Ui {
    class ForgetPasswordWindow;
}

class ForgetPasswordWindow : public QDialog {
    Q_OBJECT


public:
    explicit ForgetPasswordWindow(QWidget *parent = nullptr);

    ~ForgetPasswordWindow();

    signals:
            void signal_username(QString);

    void signal_password(QString);

private
    slots:

            void on_save_button_clicked();

    void on_cancel_button_clicked();

private:
    Ui::ForgetPasswordWindow *ui;
};

#endif // FORGETPASSWORDWINDOW_H
