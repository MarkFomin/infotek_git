#include <iostream>
#include <stdio.h>
#include "../../common/log/log.h"
using namespace std;

int main()
{

    printf("Start Log sample.\n");
    log a(250 , true, "file", "");
    //a.writeb((void const*)"12345stid", 9,  "test: ");
    for(int i=0; i<20; i++)
    {
        char trap[20]="abcdefghijklmnopqrs";
        trap[18] = char(i+48);
        a.write(trap);
    }

    return 0;
}
