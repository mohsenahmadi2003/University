#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "data/database/database.h"
#include "mainwindow.h"
#include <QMessageBox>


ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    show_my_team();
    ui->text_chat->setReadOnly(true);
    ui->text_chat->setText("No Chats Slected");
    ui->text_chat->setStyleSheet("color: rgb(255,25,25)");

}

ChatWindow::~ChatWindow()
{
    delete ui;
}


void ChatWindow::show_my_team()
{
    Database databse;
    QJsonArray all_user = databse.get_my_team(MainWindow::get_id_porject());

    QListWidgetItem *widgetItem = new QListWidgetItem();
    widgetItem->setData(Qt::UserRole, -1);
    widgetItem->setText("Group Chat");
    ui->contacts->addItem(widgetItem);
    foreach(QJsonValue
    value, all_user) {
        if(value["id"].toInt() ==  MainWindow::getUser().get_id()){
            continue;
        }
        QListWidgetItem *widgetItem = new QListWidgetItem();
        widgetItem->setData(Qt::UserRole, value["id"].toInt());
        widgetItem->setText(value["username"].toString());
        ui->contacts->addItem(widgetItem);
    }
    ui->contacts->setCurrentRow(0);

}


void ChatWindow::on_clear_button_clicked()
{
    ui->text->clear();
}

void ChatWindow::on_send_button_clicked()
{
    if(ui->text->toPlainText() != ""){
            QString old_text;

            QString new_text = MainWindow::getUser().get_name() + " : " + ui->text->toPlainText() + "\n";
            Chat chat;
            Database database;
            int user_id2 = ui->contacts->currentItem()->data(Qt::UserRole).toInt();

            if(ui->contacts->currentItem()->data(Qt::UserRole).toInt() == -1){
                old_text = database.get_group_chat_by_id(MainWindow::get_id_porject());
                old_text += new_text;
                chat.set_text(old_text);
                chat.set_project_id(MainWindow::get_id_porject());
                database.edit_group_chat_by_id(MainWindow::get_id_porject(), chat);
                ui->text_chat->clear();
                ui->text_chat->setText(old_text);


            }else{

                old_text = database.get_chat_by_id(MainWindow::get_id_porject(), MainWindow::getUser().get_id(), user_id2);
                old_text += new_text;
                chat.set_text(old_text);
                chat.set_user_id1(MainWindow::getUser().get_id());
                chat.set_user_id2(user_id2);
                chat.set_project_id(MainWindow::get_id_porject());

                database.edit_chat_by_id(MainWindow::getUser().get_id(), user_id2, MainWindow::get_id_porject(), chat);
                ui->text_chat->clear();
                ui->text_chat->setText(old_text);
            }
            ui->text->clear();
    }

}

void ChatWindow::on_contacts_itemClicked(QListWidgetItem *item)
{
    ui->text_chat->setStyleSheet("color: rgb(0, 85, 255);");
    QString text;
    Database database;
    Chat chat;


    bool existChat = database.exist_chat(MainWindow::get_id_porject(), MainWindow::getUser().get_id()
                                     , item->data(Qt::UserRole).toInt());
    bool existGroup = database.exsit_group(MainWindow::get_id_porject());

    if(existChat == false && item->data(Qt::UserRole).toInt() != -1){
            chat.set_user_id1(MainWindow::getUser().get_id());
            chat.set_user_id2(item->data(Qt::UserRole).toInt());
            chat.set_project_id(MainWindow::get_id_porject());
            database.add_chat(chat);

     }
    if(existGroup == false && item->data(Qt::UserRole).toInt() == -1){
            chat.set_project_id(MainWindow::get_id_porject());
            database.add_group_chat(chat);
    }

    if(item->data(Qt::UserRole).toInt() == -1){
        text = database.get_group_chat_by_id(MainWindow::get_id_porject());
    }else{
        text = database.get_chat_by_id(MainWindow::get_id_porject(), MainWindow::getUser().get_id()
                                       , item->data(Qt::UserRole).toInt());
    }


    ui->text_chat->setText(text);


}
