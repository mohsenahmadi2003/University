#ifndef CREATEACCOUNTWINDOW_H
#define CREATEACCOUNTWINDOW_H

#include <QDialog>
#include <QString>

namespace Ui {
    class CreateAccountWindow;
}

class CreateAccountWindow : public QDialog {
    Q_OBJECT

public:
    explicit CreateAccountWindow(QWidget *parent = nullptr);

    ~CreateAccountWindow();

    signals:
            void signal_username(QString);

    void signal_password(QString);

private
    slots:
            void on_create_button_clicked();

    void on_exitBtn_clicked();

private:
    Ui::CreateAccountWindow *ui;
};

#endif // CREATEACCOUNTWINDOW_H
