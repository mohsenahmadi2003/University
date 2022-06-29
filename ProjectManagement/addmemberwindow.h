#ifndef ADDMEMBERWINDOW_H
#define ADDMEMBERWINDOW_H

#include <QDialog>
#include "QListWidgetItem"

namespace Ui {
    class AddMemberWindow;
}

class AddMemberWindow : public QDialog {
    Q_OBJECT

public:
    explicit AddMemberWindow(QWidget *parent = nullptr);

    ~AddMemberWindow();

private
    slots:

            void on_add_member_button_clicked();

    void on_cancel_button_clicked();

    void on_my_team_list_itemDoubleClicked(QListWidgetItem *item);

    void on_save_button_clicked();

    void on_add_elder_button_clicked();

private:
    Ui::AddMemberWindow *ui;

    void show_all_user();

    void show_my_team();
};

#endif // ADDMEMBERWINDOW_H
