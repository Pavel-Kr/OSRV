#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printf("\033c");

    printf("\033[%dB", w.ws_row / 2);
    printf("\033[%dC", (int)(w.ws_col / 2 - strlen("HELLO") / 2));
    printf("HELLO\n");
    return 0;
}