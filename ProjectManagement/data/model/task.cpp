#include "task.h"
#include "QJsonObject"
#include "data/database/database.h"
#include "QJsonObject"
#include "QJsonValue"

Task::Task() {
    this->task_id = -1;
}

Task::Task(int task_id, int user_id, int project_id, QString task_name, QString task_description, QString task_status,
           QString assignment) {
    this->task_id = task_id;
    this->project_id = project_id;
    this->task_name = task_name;
    this->task_description = task_description;
    this->task_status = task_status;
    this->assignment = assignment;
    this->user_id = user_id;

}

QJsonObject Task::toJsonObject() {
    QJsonObject result;

    result["name"] = get_task_name();
    result["description"] = get_task_description();
    result["assignment"] = get_assignment();
    result["status"] = get_task_status();
    result["user_id"] = get_user_id();
    result["project_id"] = get_project_id();

    return result;
}


int Task::get_task_id() {
    return this->task_id;

}

int Task::get_project_id() {
    return this->project_id;
}

int Task::get_user_id() {
    return this->user_id;
}

QString Task::get_task_name() {
    return this->task_name;
}

QString Task::get_task_description() {
    return this->task_description;
}

QString Task::get_task_status() {
    return this->task_status;
}

QString Task::get_assignment() {
    return this->assignment;
}


void Task::set_task_id(int task_id) {
    this->task_id = task_id;
}

void Task::set_project_id(int project_id) {
    this->project_id = project_id;
}

void Task::set_task_name(QString task_name) {
    this->task_name = task_name;
}

void Task::set_task_description(QString task_description) {
    this->task_description = task_description;
}

void Task::set_task_status(QString task_status) {
    this->task_status = task_status;
}

void Task::set_assignment(QString assignment) {
    this->assignment = assignment;
}

void Task::set_user_id(int user_task_id) {
    this->user_id = user_task_id;
}

Task Task::fromJsonObject(QJsonValue value) {
    return Task(value["task_id"].toInt(), value["user_id"].toInt(), value["project_id"].toInt(),
                value["name"].toString(), value["description"].toString(), value["status"].toString(),
                value["assignment"].toString());
}


