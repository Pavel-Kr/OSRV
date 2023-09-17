#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int z;
    printf("\033c");
    while (z != ' ')
    {
        if (z = getchar())
        {
            if (z == 'e')
            {
                printf("\033c");
                return 0;
            }
            printf("\e[31;40;1m %d\e[m", z);
        }
    }
    printf("\033c");
    return 0;
}