#ifndef CONFIGSECTION_H
#define CONFIGSECTION_H

#define MAXLENVALUE 256
#define MAXLENSECNAME 128
#define MAXLENVALUENAME 128
#define LEFTBRACKET 91
#define RIGHTBRACKET 93
#include <iostream>
#include <string.h>
#include <cstdio>

class ConfigSection
{
private:

    char const *file__;
    char const *section__;
    FILE *file_ptr__;
    
    int open_file();
    int copy_str(char *cur_str_, char *copy_str_, int pos_);
    int find_section();
    int get_namesec(char *cur_str_, char *sec_name_str_);
    int get_namevalue(char *cur_str_, char *val_name_str_);
    int get_value(char *cur_str_, char *val_str_, int pos_);
    bool isStop(char c);

    
public:

    ConfigSection(char const *file_ = NULL, char const *section_ = NULL);
    ~ConfigSection();
    //Метод смены файла и/или секции
    void update(char const *file_, char const *section_);
    //Метод чтения числового параметра из секции по его имени
    int u(char const *name_, int default_);
    //Метод чтения текстового параметра из секции по его имени
    char const *u(char const *name_, char const *default_, char *str_);
    int test();
};


#endif // CONFIGSECTION_H
