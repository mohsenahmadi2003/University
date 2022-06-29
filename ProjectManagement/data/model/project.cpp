#include "project.h"

Project::Project() {

}

Project::Project(int id, QString name, QJsonArray members) {
    this->id = id;
    this->name = name;
    this->members = members;
}

QString Project::getName() {
    return name;
}

int Project::getId() {
    return id;
}

QJsonArray Project::getMembers() {
    return members;
}

void Project::setName(QString name) {
    this->name = name;
}

void Project::setId(int id) {
    this->id = id;
}

void Project::setMembers(QJsonArray members) {
    this->members = members;
}

QJsonObject Project::toJsonObject() {
    QJsonObject res;
    res["name"] = getName();
    res["id"] = getId();
    res["members"] = getMembers();
    return res;
}
