#ifndef CHAT_H
#define CHAT_H

#include "QString"
#include "QJsonObject"
class Chat
{

private:
    int project_id;
    int user_id1;
    int user_id2;
    QString text = "";
public:

    QJsonObject toJsonObject();
    QJsonObject toJsonObjectGroup();

    int get_user_id1();
    int get_user_id2();
    int get_porject_id();
    QString get_text();

    void set_user_id1(int id);
    void set_user_id2(int id);
    void set_project_id(int id);
    void set_text(QString text);
    Chat();

};

#endif // CHAT_H
