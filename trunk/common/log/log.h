#ifndef LOG_H
#define LOG_H

#include <time.h>


class log
{

private:

    char* file_;
    char* file_prefix_;
    unsigned int max_size_;
    bool close_;
    FILE* file_ptr_;

public:



    log(unsigned int n = 0, bool c = true, char* f = NULL, char* fp = NULL);
    ~log();
    //void write_log(char* message);
};

#endif // LOG_H
