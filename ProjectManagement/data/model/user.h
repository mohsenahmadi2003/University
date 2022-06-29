#ifndef USER_H
#define USER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include<QObject>

class User {

private:

    QString name;
    QString username;
    QString password;
    QString email;
    QString phone_number;
    int id;
    QString position;

public:
    User();

    User(QString name,
         QString username,
         QString password,
         QString email,
         QString phone_number,
         int id
         );

    QString get_position();

    QString get_name();

    QString get_username();

    QString get_password();

    QString get_email();

    QString get_phone_number();

    int get_id();

    void set_position(QString position);

    void set_name(QString name);

    void set_username(QString username);

    void set_password(QString password);

    void set_email(QString email);

    void set_phone_number(QString phone_number);

    void set_id(int id);

    QJsonObject toJsonObject();
};


#endif // USER_H
