#include "exception.h"

Exception::Exception()
{


}

Exception::Exception(int code, QString message)
{
    this->code = code;
    this->message = message;

}

int Exception::get_code()
{
    return code;
}

QString Exception::get_message()
{
    return message;
}

void Exception::set_code(int code)
{
    this->code = code;
}

void Exception::set_message(QString message)
{
    this->message = message;
}
