#ifndef PROJECT_H
#define PROJECT_H
#include "QString"
#include "QJsonArray"
#include <QJsonObject>


class Project
{
private:
    QString name;
    int id;
    QJsonArray members;

public:
    Project();

    Project(int id, QString name, QJsonArray members);

    QString getName();
    int getId();
    QJsonArray getMembers();

    void setName(QString name);
    void setId(int id);
    void setMembers(QJsonArray members);
    QJsonObject toJsonObject();

};

#endif // PROJECT_H
