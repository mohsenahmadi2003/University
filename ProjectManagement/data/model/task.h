#ifndef TASK_H
#define TASK_H

#include "QString"
#include "QJsonObject"

class Task {

private:
    int task_id;
    int user_id;
    int project_id;
    QString task_name;
    QString task_description;
    QString task_status;
    QString assignment;


public:
    Task();

    Task(int task_id, int user_id, int project_id, QString task_name,
         QString task_description, QString task_status, QString assignment);

    QJsonObject toJsonObject();

    int get_task_id();

    int get_project_id();

    int get_user_id();

    QString get_task_name();

    QString get_task_description();

    QString get_task_status();

    QString get_assignment();


    void set_task_id(int task_id);

    void set_project_id(int project_id);

    void set_task_name(QString task_name);

    void set_task_description(QString task_description);

    void set_task_status(QString task_status);

    void set_assignment(QString assignment);

    void set_user_id(int user_task_id);

    Task fromJsonObject(QJsonValue value);


};


#endif // TASK_H
