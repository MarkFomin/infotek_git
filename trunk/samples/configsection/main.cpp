#include <iostream>

#include "../../common/configsection/configsection.h"
using namespace std;

int main()
{
    char val[MAXLENVALUE];
    int t = 0;

    ConfigSection a("file:///home/roman/git_isp/infotek_git/trunk/samples/configsection/conf", "local");
    t = a.u("timeout", 400);
    char const *tmp_buf1 = a.u("log", "failfailfailfailfailfailfailfailfailfailfailfailfailfailfail", val);

    printf("%s\n", tmp_buf1);
    printf("%d\n", t);
    a.update("file:///home/roman/git_isp/infotek_git/trunk/samples/configsection/conf", "global");

    t = a.u("potr", 666);
    char const *tmp_buf2 = a.u("ip", "kroke", val);

    printf("%s\n", tmp_buf2);
    printf("%d\n", t);
    return 0;
}
