#include "database.h"
#include "../../utils/exception.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QJsonArray>
#include <QThread>
#include <iostream>
#include "mainwindow.h"
#include <QMessageBox>
#include "addmemberwindow.h"
#include "addtaskwindow.h"


Database::Database() {

}


User Database::get_user(QString username) {

    QJsonArray users = get_users();

    foreach(QJsonValue
    value, users) {
        if (value["username"] == username)
            return User(value["name"].toString(), value["username"].toString(), value["password"].toString(),
                        value["email"].toString(), value["phone_number"].toString(), value["id"].toInt()
                        );
    }

    return User();
}

User Database::get_user_by_id(int id) {
    QJsonArray users = get_users();

    foreach(QJsonValue
    value, users) {
        if (value["id"].toInt() == id) {
            return User(value["name"].toString(), value["username"].toString(), value["password"].toString(),
                        value["email"].toString(), value["phone_number"].toString(), value["id"].toInt()
                        );
        }
    }

    return User();
}

void Database::edit_user(QString username, User user) {
    QJsonArray users = get_users();
    int index = 0;

    foreach(QJsonValue
    value, users) {
        if (value["username"].toString() == username) {
            users.replace(index, user.toJsonObject());
            break;
        }
        index += 1;
    }
    QFile DBW("Users.json");
    DBW.open(QIODevice::WriteOnly);
    QJsonObject result;
    result["Users"] = users;
    DBW.write(QJsonDocument(result).toJson());

    DBW.close();
}

void Database::edit_user_by_id(int id, User user) {

    if (user.get_username() == get_user(user.get_username()).get_username()
        && id != get_user(user.get_username()).get_id()) {
        throw Exception(0, "username is exists");
    }

    QJsonArray users = get_users();


    users.replace(id, user.toJsonObject());

    QFile DBW("Users.json");
    DBW.open(QIODevice::WriteOnly);
    QJsonObject result;
    result["Users"] = users;
    DBW.write(QJsonDocument(result).toJson());

    DBW.close();

}

void Database::add_user(User user) {
    if (user.get_username() == get_user(user.get_username()).get_username()) {
        throw Exception(0, "username is exists");
    }

    QJsonArray users = get_users();
    QJsonObject result;
    user.set_id(users.size());
    users.append(user.toJsonObject());
    result["Users"] = users;

    QJsonDocument doc_user(result);
    QFile DBW("Users.json");
    DBW.open(QIODevice::WriteOnly);
    DBW.write(doc_user.toJson());

    DBW.close();
}

QJsonArray Database::get_users() {

    QFile DBR("Users.json");
    DBR.open(QIODevice::ReadOnly);

    QByteArray qba = DBR.readAll();
    QJsonDocument qjd = QJsonDocument::fromJson(qba);
    QJsonObject qjo = qjd.object();
    QJsonArray res = qjo["Users"].toArray();

    DBR.close();

    return res;

}

void Database::add_project(Project project, int user_id) {
    QJsonArray projects = get_projects();
    QJsonObject result;
    project.setId(projects.size());
    QJsonArray members = project.getMembers();
    QJsonObject newMember;
    newMember["user_id"] = user_id;
    newMember["position"] = "leader";
    members.append(newMember);
    project.setMembers(members);
    projects.append(project.toJsonObject());
    result["Projects"] = projects;

    QJsonDocument doc_projects(result);

    QFile DBW("Projects.json");
    DBW.open(QIODevice::WriteOnly);
    DBW.write(doc_projects.toJson());

    DBW.close();
}

QJsonArray Database::get_projects() {
    QFile DBR("Projects.json");
    DBR.open(QIODevice::ReadOnly);

    QByteArray qba = DBR.readAll();
    QJsonDocument qjd = QJsonDocument::fromJson(qba);
    QJsonObject qjo = qjd.object();
    QJsonArray res = qjo["Projects"].toArray();

    DBR.close();

    return res;
}

QJsonArray Database::get_projet_of_user(int user_id) {
    QJsonArray projects = get_projects();
    QJsonArray filterdProjects;
    foreach(QJsonValue
    value, projects) {
        QJsonArray members = value["members"].toArray();
        foreach(QJsonValue
        value2, members) {
            if (value2["user_id"] == user_id) {
                filterdProjects.append(value);
            }
        }
    }
    return filterdProjects;
}

QJsonArray Database::get_my_team(int id_team) {
    Project project = get_project_by_id(id_team);
    QJsonArray result;
    foreach(QJsonValue
    value, project.getMembers()) {
        User user = get_user_by_id(value["user_id"].toInt());
        user.set_position(value["position"].toString());
        result.append(user.toJsonObject());
    }
    return result;
}

void Database::add_member_to_project(int user_id, QString position, int id_project) {
    Project project = get_project_by_id(id_project);
    QJsonObject newMember;
    foreach(QJsonValue
    value, project.getMembers()) {
        if (value["user_id"] == user_id)
            return;
    }
    newMember["position"] = position;
    newMember["user_id"] = user_id;
    project.getMembers().append(newMember);
    edit_project_by_id(project, id_project);
}

Project Database::get_project_by_id(int id) {
    QJsonArray projects = get_projects();
    QJsonValue value = projects[id];
    return Project(value["id"].toInt(), value["name"].toString(), value["members"].toArray());
}

void Database::edit_project_by_id(Project project, int id) {
    QJsonArray projects = get_projects();
    projects.replace(id, project.toJsonObject());
    QJsonObject result;

    result["Projects"] = projects;

    QJsonDocument doc_projects(result);

    QFile DBW("Projects.json");
    DBW.open(QIODevice::WriteOnly);
    DBW.write(doc_projects.toJson());

    DBW.close();
}

QString Database::find_position(int user_id, int id_project) {
    QString position;
    Project project = get_project_by_id(id_project);
    foreach(QJsonValue
    value, project.getMembers()) {
        if (value["user_id"].toInt() == user_id) {
            position = value["position"].toString();

            break;
        }
    }
    return position;
}

void Database::add_task(Task task) {
    QJsonObject body;
    QJsonArray tasks = get_tasks();
    task.set_task_id(get_last_id_of_task());
    tasks.append(task.toJsonObject());
    body["tasks"] = tasks;
    body["last_id"] = task.get_task_id() + 1;
    QJsonDocument doc_task(body);
    QFile DBW("Tasks.json");
    DBW.open(QIODevice::WriteOnly);
    DBW.write(doc_task.toJson());
    DBW.close();
}

QJsonArray Database::get_tasks() {
    QJsonArray res;
    QFile DBR("Tasks.json");
    DBR.open(QIODevice::ReadOnly);
    QByteArray qba = DBR.readAll();
    QJsonDocument qjd = QJsonDocument::fromJson(qba);
    QJsonObject qjo = qjd.object();
    res = qjo["tasks"].toArray();

    DBR.close();

    return res;
}

int Database::get_last_id_of_task() {
    int res;
    QFile DBR("Tasks.json");
    DBR.open(QIODevice::ReadOnly);
    QByteArray qba = DBR.readAll();
    QJsonDocument qjd = QJsonDocument::fromJson(qba);
    QJsonObject qjo = qjd.object();
    res = qjo["last_id"].toInt();

    DBR.close();

    return res;
}

void Database::edit_task_by_id(int id, Task task) {


    QJsonArray tasks = get_tasks();
    int index = -1;
    int last = get_last_id_of_task();
    foreach(QJsonValue
    value, tasks) {
        index += 1;
        if (value["task_id"].toInt() == id) {

            tasks.replace(index, task.toJsonObject());
            break;
        }
    }


    QJsonObject result;

    result["tasks"] = tasks;
    result["last_id"] = last;

    QJsonDocument doc_projects(result);

    QFile DBW("Tasks.json");
    DBW.open(QIODevice::WriteOnly);
    DBW.write(doc_projects.toJson());
    DBW.close();

}

void Database::delete_task(int id) {
    QJsonArray tasks = get_tasks();
    int index = -1;
    int last = get_last_id_of_task();
    foreach(QJsonValue
    value, tasks) {
        index += 1;
        if (value["task_id"].toInt() == id) {
            tasks.removeAt(index);
        }
    }

    QJsonObject result;

    result["tasks"] = tasks;
    result["last_id"] = last;
    QJsonDocument doc_projects(result);
    QFile DBW("Tasks.json");
    DBW.open(QIODevice::WriteOnly);
    DBW.write(doc_projects.toJson());

    DBW.close();

}

void Database::add_chat(Chat chat)
{

   QJsonObject chats = get_chats();
   QJsonObject body;
   QJsonArray private_chat = chats["private"].toArray();
   QJsonArray group_chat = chats["group"].toArray();

   private_chat.append(chat.toJsonObject());

   body["private"] = private_chat;
   body["group"] = group_chat;

   QJsonDocument doc_chat(body);
   QFile DBW("Chats.json");
   DBW.open(QIODevice::WriteOnly);
   DBW.write(doc_chat.toJson());
   DBW.close();


}

void Database::add_group_chat(Chat chat)
{
    QJsonObject chats = get_chats();
    QJsonObject body;
    QJsonArray private_chat = chats["private"].toArray();
    QJsonArray group_chat = chats["group"].toArray();

    group_chat.append(chat.toJsonObjectGroup());

    body["private"] = private_chat;
    body["group"] = group_chat;

    QJsonDocument doc_chat(body);
    QFile DBW("Chats.json");
    DBW.open(QIODevice::WriteOnly);
    DBW.write(doc_chat.toJson());
    DBW.close();


}

QJsonObject Database::get_chats()
{
    QJsonObject res;
    QFile DBR("Chats.json");
    DBR.open(QIODevice::ReadOnly);
    QByteArray qba = DBR.readAll();
    QJsonDocument qjd = QJsonDocument::fromJson(qba);
    QJsonObject qjo = qjd.object();
    res = qjo;

    DBR.close();

    return res;
}

void Database::edit_chat_by_id(int user_id1, int user_id2, int project_id, Chat chat)
{
    QJsonObject chats = get_chats();
    QJsonArray private_chat = chats["private"].toArray();
    QJsonArray group = chats["group"].toArray();
    int index = -1;

    foreach(QJsonValue
    value, private_chat) {
        index+=1;

        if( value["project_id"].toInt() == project_id){

            if (value["user_id1"].toInt() == user_id1 && value["user_id2"].toInt() == user_id2) {
                        private_chat.replace(index, chat.toJsonObject());

                        break;
            }else if (value["user_id1"].toInt() == user_id2 && value["user_id2"].toInt() == user_id1) {
                             private_chat.replace(index, chat.toJsonObject());

                             break;
            }
        }

    }

    QJsonObject result;

    result["private"] = private_chat ;
    result["group"] = group ;

    QJsonDocument doc_projects(result);
    QFile DBW("Chats.json");
    DBW.open(QIODevice::WriteOnly);
    DBW.write(doc_projects.toJson());
    DBW.close();

}

QString Database::get_chat_by_id(int project_id, int user_id1, int user_id2)
{
    QJsonObject chats = get_chats();
    QJsonArray private_chat = chats["private"].toArray();
    QString text;
    foreach (QJsonValue value, private_chat) {
        if(value["project_id"].toInt() == project_id){
            if(value["user_id1"].toInt() == user_id1 && value["user_id2"].toInt() == user_id2){
                        text = value["text"].toString();
                        return text;

            }if(value["user_id1"].toInt() == user_id2 && value["user_id2"].toInt() == user_id1){
                text = value["text"].toString();
                return text;
            }
    }

    }
    return text;
}

QString Database::get_group_chat_by_id(int project_id)
{
    QJsonObject chats = get_chats();
    QJsonArray group = chats["group"].toArray();
    QString text;
    foreach (QJsonValue value, group)
    {
        if(value["project_id"].toInt() == project_id){
            text = value["text"].toString();
            return text;
            }
    }
    return text;

}

void Database::edit_group_chat_by_id(int project_id, Chat chat)
{
    QJsonObject chats = get_chats();
    QJsonArray private_chat = chats["private"].toArray();
    QJsonArray group = chats["group"].toArray();
    int index = -1;
    foreach(QJsonValue
    value, group) {
        index+=1;
        if (value["project_id"].toInt() == project_id) {
                    group.replace(index, chat.toJsonObjectGroup());
                    break;
        }
    }

    QJsonObject body;

    body["private"] = private_chat;
    body["group"] = group;

    QJsonDocument doc_chat(body);
    QFile DBW("Chats.json");
    DBW.open(QIODevice::WriteOnly);
    DBW.write(doc_chat.toJson());
    DBW.close();
}

bool Database::exist_chat(int project_id, int user_id1, int user_id2)
{
    QJsonObject chats = get_chats();
    QJsonArray private_chat = chats["private"].toArray();
    bool exist = false;

        foreach (QJsonValue value, private_chat) {
            if(value["project_id"].toInt() == project_id){
                if(value["user_id1"].toInt() == user_id1 && value["user_id2"].toInt() == user_id2){
                            exist = true;
                            return exist;

                }if(value["user_id1"].toInt() == user_id2 && value["user_id2"].toInt() == user_id1){
                            exist = true;
                            return exist;
                }
        }

    }
       return exist;
}

bool Database::exsit_group(int project_id)
{
    QJsonObject chats = get_chats();
    QJsonArray group_chat = chats["group"].toArray();
    bool exist = false;
            foreach(QJsonValue
            value, group_chat)
            {
                if(value["project_id"].toInt() == project_id)
                {

                   exist = true;
                   return exist;

                }
            }

           return exist;

}








