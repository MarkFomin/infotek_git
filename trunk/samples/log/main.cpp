#include <iostream>
#include "log.h"
using namespace std;

int main()
{

    printf("Start Log sample.\n");
    log a(0, true, "file.txt");

    a.write("msg test");


    return 0;
}
