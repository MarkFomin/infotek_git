#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>

class log
{

private:

    char file_name_[256]={0};
    char* file_;
    char* file_prefix_;
    unsigned int max_size_;
    bool close_;
    FILE* file_ptr_;

public:
    //Конструктор
    log(unsigned int n = 0, bool c = true, char* f = NULL, char* fp = nullptr);
    //Деструктор
    ~log();
    //запись лога
    void write(char* msg);
    //размер файла
    size_t file_length();
    //метод получения системного времени
    char* get_time(char* buf);
    //метд получения микросекунд
    char* get_usec(char* buf);
    //метод обрезки сообщения, если оно превышает 128 символов
    void cut_msg(char* buf, char* buf_msg);
    //формирование имени файла
    void name_create();
    //формирование сообщения для записи
    void log_create(char* buf_log, char* buf_msg);
    //очистить файл
    void file_clear();
    //переименование file в file~
    void file_rename();

};

#endif // LOG_H
