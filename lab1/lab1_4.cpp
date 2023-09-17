#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>

// int argc,char *argv[]: argv[0] - direction (check enDirections)
//                        argv[1] - color (check ncurses defines)
//                        argv[2] - thred delay

enum class enDirections
{
  RIGHT = 0,
  LEFT,
  UP,
  DOWN,
};

struct Object
{
  Object(int x, int y)
  {
    x_pos = x;
    y_pos = y;
  }

  int x_pos = 0, y_pos = 0;
  enDirections direction;
  char symbol = '*';
};

void move_left(Object *obj, int border);
void move_right(Object *obj, int border);
void move_up(Object *obj, int border);
void move_down(Object *obj, int border);

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    return 0;
  }

  int direction = atoi(argv[1]) % 4;
  int color = atoi(argv[2]) % 7;
  int delay = atoi(argv[3]);

  if (color < 0 || color > 7)
  {
    return 0;
  }

  if (can_change_color())
  {
    return 0;
  }

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  Object obj(w.ws_row / 2, w.ws_col / 2);
  obj.direction = (enDirections)direction;

  initscr();
  start_color();
  refresh();

  init_pair(1, color, COLOR_BLACK);

  while (true) {
      switch (obj.direction)
      {
      case enDirections::UP:
          move_up(&obj, 0);
          break;
      case enDirections::DOWN:
          move_down(&obj, w.ws_row);
          break;
      case enDirections::LEFT:
          move_left(&obj, 0);
          break;
      case enDirections::RIGHT:
          move_right(&obj, w.ws_col);
          break;
      default:
          fprintf(stderr, "Error: Wrong direction %d\n", (int)obj.direction);
          endwin();
          return 0;
      }
      refresh();
      usleep(delay*1000);
  }

  endwin();
  return 0;
}

void move_left(Object *obj, int border)
{
  if (obj->y_pos - 2 < border)
  {
      obj->direction = enDirections::RIGHT;
  }
  mvaddch(obj->x_pos, obj->y_pos, ' ');
  mvaddch(obj->x_pos, --obj->y_pos, obj->symbol | A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
}

void move_right(Object *obj, int border)
{
  if (obj->y_pos + 2 > border)
  {
      obj->direction = enDirections::LEFT;
  }
  mvaddch(obj->x_pos, obj->y_pos, ' ');
  mvaddch(obj->x_pos, ++obj->y_pos, obj->symbol | A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
}

void move_up(Object *obj, int border)
{
  if (obj->x_pos - 2 < border)
  {
      obj->direction = enDirections::DOWN;
  }
  mvaddch(obj->x_pos, obj->y_pos, ' ');
  mvaddch(--obj->x_pos, obj->y_pos, obj->symbol | A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
}

void move_down(Object *obj, int border)
{
  if (obj->x_pos + 2 > border)
  {
      obj->direction = enDirections::UP;
  }
  mvaddch(obj->x_pos, obj->y_pos, ' ');
  mvaddch(++obj->x_pos, obj->y_pos, obj->symbol | A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
}