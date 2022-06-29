#include "chat.h"

QJsonObject Chat::toJsonObject()
{
    QJsonObject result;

    result["project_id"] = get_porject_id();
    result["user_id1"] = get_user_id1();
    result["user_id2"] = get_user_id2();
    result["text"] = get_text();

    return result;
}

QJsonObject Chat::toJsonObjectGroup()
{
    QJsonObject result;

    result["project_id"] = get_porject_id();
    result["text"] = get_text();
    return result;

}

int Chat::get_user_id1()
{
    return this->user_id1;
}

int Chat::get_user_id2()
{
    return this->user_id2;
}

int Chat::get_porject_id()
{
    return this->project_id;
}

QString Chat::get_text()
{
    return this->text;
}

void Chat::set_user_id1(int id)
{
    this->user_id1 = id;
}

void Chat::set_user_id2(int id)
{
    this->user_id2 = id;
}

void Chat::set_project_id(int id)
{
    this->project_id = id;
}

void Chat::set_text(QString text)
{
    this->text = text;
}

Chat::Chat()
{

}
