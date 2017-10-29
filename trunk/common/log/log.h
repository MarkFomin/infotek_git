#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>

class log
{

private:

    char file_name__[256]={0};
    char* file__;
    char* file_prefix__;
    unsigned int max_size__;
    bool close__;
    FILE* file_ptr__;


    //размер файла
    size_t file_length();
    //метод получения системного времени
    char* get_time(char *buf_);
    //метд получения микросекунд
    char* get_usec(char *buf_);
    //метод обрезки сообщения, если оно превышает 128 символов
    void cut_msg(char const *buf_, char *buf_msg_);
    //формирование имени файла
    void name_create();
    //формирование сообщения для записи
    void log_create(char *buf_log_, char const *buf_msg_);
    //очистить файл
    void file_clear();
    //переименование file в file~
    void file_rename();
public:

    //Конструктор
    log(unsigned int n = 0, bool c = true, char *f = NULL, char *fp = nullptr);
    //Деструктор
    ~log();
    //запись лога
    void write(char const *msg_);
    //запись в лог содержимого произвольного буфера
    //void writeb(void const* buf_, size_t len_, char const *info_);

};

#endif // LOG_H
