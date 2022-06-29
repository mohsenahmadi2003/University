#ifndef PROJECTS_H
#define PROJECTS_H

#include <QDialog>

namespace Ui {
    class ProjectsWindow;
}

class ProjectsWindow : public QDialog {
    Q_OBJECT

public:
    explicit ProjectsWindow(QWidget *parent = nullptr);

    ~ProjectsWindow();

    signals:
            void send_project_id(int);
private
    slots:
            void on_create_project_button_clicked();

    void on_close_button_clicked();

    void changedEvent();


    void on_close_button_2_clicked();

private:
    Ui::ProjectsWindow *ui;

    void fillList();
};

#endif // PROJECTS_H
