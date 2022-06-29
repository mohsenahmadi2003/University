#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include "QListWidgetItem"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
    void show_my_team();

private slots:

    void on_clear_button_clicked();

    void on_send_button_clicked();

    void on_contacts_itemClicked(QListWidgetItem *item);

private:
    Ui::ChatWindow *ui;
};

#endif // CHATWINDOW_H
