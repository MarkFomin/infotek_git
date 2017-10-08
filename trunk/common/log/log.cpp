#include "log.h"

using namespace std;

log::log(unsigned int n, bool c, char *f, char *fp)
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

log::~log()
    {
        fclose(file_ptr_);
    }

void log::write(char* msg)
{


    char buffer_time[80];
    char buffer_usec[80];

    struct tm *ptr;
    time_t tm;
    tm = time(NULL);
    ptr = localtime(&tm);

    unsigned int usec;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    usec = tv.tv_usec;



    snprintf ( buffer_usec, 80, "%d ", usec);

    strftime(buffer_time, 80, "%g%m%d %H%M%S ", ptr);
    if (close_ == true)
    {
        file_ptr_ = fopen(file_, "a+");
    }


    fseek(file_ptr_, 0, SEEK_END);
    fprintf(file_ptr_, buffer_time);
    fprintf(file_ptr_, buffer_usec);
    fprintf(file_ptr_, msg);
    fprintf(file_ptr_, "\n");

    if (close_ == true)
    {
        fclose(file_ptr_);
    }

}


int log::file_length()
{
    int f_l = 0;

    fseek(file_ptr_, 0, SEEK_END);

    f_l = ftell(file_ptr_);

    return f_l;
}













