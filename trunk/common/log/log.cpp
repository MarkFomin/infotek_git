#include "log.h"

using namespace std;

log::log(unsigned int n_, bool c_, char const *f_, char const *fp_) : file__(f_)
{
  
    file_prefix_ = fp_;
    max_size_ = n_;
    close_ = c_;
    name_create();

    file_ptr_ = fopen(file_name_, "a");
    if(file_ptr_==nullptr)return;
    if (file_length() + 149 >= max_size_)
    {
        fclose(file_ptr_);
        file_clear();
        if(close_)
        {
            file_ptr_ = fopen(file_name_, "a+");
        }
    }
}

log::~log()
{
    if(close_)
    {
        fclose(file_ptr_);
    }
}

void log::write(char* msg)
{
    char buffer_log[256]={0};
    char buffer_msg[128]={0};
    size_t msg_len = 0;

    if (!close_)
    {
        file_ptr_ = fopen(file_name_, "a+");
    }

    msg_len = strlen(msg);

    if (msg_len > 128)
    {
        cut_msg(msg, buffer_msg);
    }
    else
    {
        memcpy(buffer_msg, msg, msg_len);
    }

    log_create(buffer_log, buffer_msg);

    msg_len = strlen(buffer_log);

    if (msg_len+file_length() > max_size_)
    {
        fclose(file_ptr_);
        file_rename();
        file_ptr_ = fopen(file_name_, "a+");
        fseek(file_ptr_, 0, SEEK_END);
        fprintf(file_ptr_, buffer_log);
    }
    else
    {
        fseek(file_ptr_, 0, SEEK_END);
        fprintf(file_ptr_, buffer_log);
    }

    if (!close_)
    {
        fclose(file_ptr_);
    }
}

size_t log::file_length()
{
    int f_l = 0;
    fseek(file_ptr_, 0, SEEK_END);

    f_l = ftell(file_ptr_);

    return f_l;
}


char* log::get_time(char* buf)
{
    struct tm *ptr;
    time_t tm;
    tm = time(NULL);
    ptr = localtime(&tm);

    strftime(buf, 80, "%g%m%d %H%M%S", ptr);

    return buf;
}


char* log::get_usec(char *buf)
{
    unsigned int usec;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    usec = tv.tv_usec;

    snprintf (buf, 80, "%d", usec);

    return buf;
}


void log::cut_msg(char* buf, char *buf_msg)
{
    strncpy(buf_msg, buf, 124);
    strcat(buf_msg, "...");
}

void log::name_create()
{
    if(file_prefix_ != NULL)
    {
        strcpy(file_name_, file_prefix_);
    }

    strcat(file_name_, file__);
    printf("%s\n", file_name_);
}

void log::log_create(char* buf_log, char* buf_msg)
{
    char buffer_time[80];
    char buffer_usec[80];
    sprintf(buf_log, "%s %s %s\n", get_time(buffer_time), get_usec(buffer_usec), buf_msg);
}

void log::file_clear()
{
    file_ptr_ = fopen(file_name_, "w");
    fclose(file_ptr_);
}

void log::file_rename()
{
    if (file_name_[strlen(file_name_)-1] == '~')
    {
        file_name_[strlen(file_name_)-1] = '\0';
    }
    else
    {
        strncat(file_name_, "~", 1);
    }
    file_clear();
}

















