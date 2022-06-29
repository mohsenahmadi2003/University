#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <QString>

class Exception
{
private:
    QString message;
    int code;

public:
    Exception();

    Exception(int code, QString message);

    int get_code();
    QString get_message();

    void set_code(int code);
    void set_message(QString message);

};

#endif // EXCEPTION_H
