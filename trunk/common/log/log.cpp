#include "log.h"

log::log(unsigned int n = 0, bool c = true, char* f = NULL, char* fp = NULL)
{

    file_ = f;
    file_prefix_ = fp;
    max_size_ = n;
    close_ = c;

    if (close_)
    {
        file_ptr_ = fopen(file_, "a+");
    }

}

log::~log(){}

//log::write_log(char *message){}
