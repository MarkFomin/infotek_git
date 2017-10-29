#include "log.h"

using namespace std;

log::log(unsigned int n, bool c, char *f, char *fp)
{
    file__ = f;
    file_prefix__ = fp;
    max_size__ = n;
    close__ = c;
    name_create();

    file_ptr__ = fopen(file_name__, "a+");

    if(!file_ptr__)
    {
        printf("ERROR! File wasn't opened!");
        return;
    }

    if (file_length() + 149 >= max_size__)
    {
        fclose(file_ptr__);
        file_clear();
        if(close__)
        {
            file_ptr__ = fopen(file_name__, "a+");

            if(!file_ptr__)
            {
                printf("ERROR! File wasn't opened!");
                return;
            }
        }
    }
}

log::~log()
{
    if(close__)
    {
        fclose(file_ptr__);
    }
}

void log::write(const char *msg_)
{
    char buffer_log[256]={0};
    char buffer_msg[128]={0};
    size_t msg_len = 0;

    if (!close__)
    {
        file_ptr__ = fopen(file_name__, "a+");

        if(!file_ptr__)
        {
            printf("ERROR! File wasn't opened!");
            return;
        }
    }

    msg_len = strlen(msg_);

    if (msg_len > 128)
    {
        cut_msg(msg_, buffer_msg);
    }
    else
    {
        memcpy(buffer_msg, msg_, msg_len);
    }

    log_create(buffer_log, buffer_msg);

    msg_len = strlen(buffer_log);

    if (msg_len+file_length() > max_size__)
    {
        fclose(file_ptr__);
        file_rename();
        file_ptr__ = fopen(file_name__, "a+");

        if(!file_ptr__)
        {
            printf("ERROR! File wasn't opened!");
            return;
        }
        fseek(file_ptr__, 0, SEEK_END);
        fprintf(file_ptr__, buffer_log);
    }
    else
    {
        fseek(file_ptr__, 0, SEEK_END);
        fprintf(file_ptr__, buffer_log);
    }

    if (!close__)
    {
        fclose(file_ptr__);
    }
}

size_t log::file_length()
{
    int f_l = 0;

    fseek(file_ptr__, 0, SEEK_END);

    f_l = ftell(file_ptr__);

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


void log::cut_msg(const char *buf, char *buf_msg)
{
    strncpy(buf_msg, buf, 124);
    strcat(buf_msg, "...");
}

void log::name_create()
{
    if(file_prefix__ != NULL)
    {
        strcpy(file_name__, file_prefix__);
    }

    strcat(file_name__, file__);
}

void log::log_create(char* buf_log, char const *buf_msg)
{
    char buffer_time[80];
    char buffer_usec[80];
    sprintf(buf_log, "%s %s %s\n", get_time(buffer_time), get_usec(buffer_usec), buf_msg);
}

void log::file_clear()
{
    file_ptr__ = fopen(file_name__, "w");

    if(!file_ptr__)
    {
        printf("ERROR! File wasn't opened!");
        return;
    }

    fclose(file_ptr__);
}

void log::file_rename()
{
    if (file_name__[strlen(file_name__)-1] == '~')
    {
        file_name__[strlen(file_name__)-1] = '\0';
    }
    else
    {
        strncat(file_name__, "~", 1);
    }
    file_clear();
}

/*
void log::writeb(void const* buf_, size_t len_, char const *info_)
{
    char buffer_time[80];
    char buffer_usec[80];

    if(file_ptr__)
    {
        fclose(file_ptr__);
    }

    file_ptr__ = fopen(file_name__, "ab+");

    if(!file_ptr__)
    {
        printf("ERROR! File wasn't opened!");
        return;
    }

    get_time(buffer_time);
    get_usec(buffer_usec);

    for(int i = 0; i < 5; i++)
   {
        //const char* tmp = (const char*)buf_;
        //const char* tmp2 = (const char*)buf_;
        size_t n = len_;
        size_t n2 = sizeof(buf_);
        fwrite(buf_, len_, 1, file_ptr__);


    //printf("%x", tmp);

    }

}
*/














