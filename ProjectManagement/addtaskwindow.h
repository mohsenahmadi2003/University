#ifndef ADDTASKWINDOW_H
#define ADDTASKWINDOW_H

#include <QDialog>
#include <QListWidgetItem>
#include "data/model/task.h"

namespace Ui {
    class AddTaskWindow;
}

class AddTaskWindow : public QDialog {
    Q_OBJECT

public:
    explicit AddTaskWindow(QWidget *parent = nullptr, Task *task = nullptr);

    ~AddTaskWindow();

    void show_my_team();

    signals:
            void edit_task();


private
    slots:
            void on_pushButton_2_clicked();

    void on_save_button_clicked();

    void on_my_team_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_delete_button_clicked();

private:
    Ui::AddTaskWindow *ui;
    Task task;
};

#endif // ADDTASKWINDOW_H
