#ifndef CREATEPROJECTWINDOW_H
#define CREATEPROJECTWINDOW_H

#include <QDialog>

namespace Ui {
    class CreateProjectWindow;
}

class CreateProjectWindow : public QDialog {
    Q_OBJECT

public:
    explicit CreateProjectWindow(QWidget *parent = nullptr);

    ~CreateProjectWindow();

private
    slots:
            void on_save_button_clicked();

    void on_close_button_clicked();

    signals:
            void changedEvent();

private:
    Ui::CreateProjectWindow *ui;
};

#endif // CREATEPROJECTWINDOW_H
