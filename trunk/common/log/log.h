#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <sys/time.h>

class log
{

private:

    char* file_;
    char* file_prefix_;
    unsigned int max_size_;
    bool close_;
    FILE* file_ptr_;

public:
    //Конструктор
    log(unsigned int n = 0, bool c = true, char* f = NULL, char* fp = NULL);
    //Деструктор
    ~log();
    //запись лога
    void write(char* msg);
    //размер файла
    int file_length();
};

#endif // LOG_H
