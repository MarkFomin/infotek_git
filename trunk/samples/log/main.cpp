#include <iostream>
#include <stdio.h>
#include "../../common/log/log.h"
using namespace std;

int main()
{

    printf("Start Log sample.\n");
    log a(2500   , true, "file5");

    for(int i=0; i<20; i++)
    {
      char trap[1024]="abcdefghijklmnopqrsabcdefghijklmnopqrsabcdefghijklmnopqrsabcdefghijklmnopqrsabcdefghijklmnopqrsabcdefghijklmnopqrsabcdefghijklmnopqrs";
        trap[18] = char(i+48);
        a.write(trap);
    }

    return 0;
}
