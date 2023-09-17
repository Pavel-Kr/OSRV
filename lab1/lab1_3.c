#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
  initscr();
  refresh();

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  bool flag = 0;
  int pos_x = w.ws_row / 2, pos_y = w.ws_col / 2;
  int dy = 1;
  while (true)
  {
    if (pos_y + 2 > w.ws_col)
    {
      dy = -dy;
    }

    if (pos_y - 2 < 0)
    {
      dy = -dy;
    }
    mvaddch(pos_x, pos_y, ' ');
    pos_y+= dy;
    mvaddch(pos_x, pos_y, '*');
    usleep(100000);
    refresh();
  }
  endwin();
  return 0;
}