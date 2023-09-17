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
  bool flag_x = 0, flag_y = 0;
  char symbol = '*';
};

void move_left(Object *obj, int border);
void move_right(Object *obj, int border);
void move_up(Object *obj, int border);
void move_down(Object *obj, int border);

int main(int argc, char *argv[])
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  Object obj(w.ws_row / 2, w.ws_col / 2);
  std::vector<Object> object_pool;
  object_pool.push_back(obj);
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

  initscr();
  start_color();
  refresh();

  init_pair(1, color, COLOR_BLACK);

  bool start_flag = 0;
  if (direction == 1 || direction == 3)
  {
    start_flag = 1;
  }

  while (true)
  {
    if (direction == (int)enDirections::RIGHT || direction == (int)enDirections::UP)
    {
      if (start_flag)
      {
        object_pool[0].flag_y = 1;
        start_flag = 0;
      }
      if (object_pool[0].flag_y == 0)
      {
        move_right(&object_pool[0], w.ws_col);
      }
      if (object_pool[0].flag_y == 1)
      {
        move_left(&object_pool[0], 0);
      }
    }
    else if (direction == (int)enDirections::LEFT || direction == (int)enDirections::DOWN)
    {
      if (start_flag)
      {
        object_pool[0].flag_x = 1;
        start_flag = 0;
      }
      if (object_pool[0].flag_x == 0)
      {
        move_up(&object_pool[0], 0);
      }
      if (object_pool[0].flag_x == 1)
      {
        move_down(&object_pool[0], w.ws_row);
      }
    }
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }

  endwin();
  return 0;
}

void move_left(Object *obj, int border)
{
  if (obj->y_pos - 2 < border)
  {
    obj->flag_y = 0;
  }
  mvaddch(obj->x_pos, obj->y_pos, ' ');
  mvaddch(obj->x_pos, --obj->y_pos, obj->symbol | A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
}

void move_right(Object *obj, int border)
{
  if (obj->y_pos + 2 > border)
  {
    obj->flag_y = 1;
  }
  mvaddch(obj->x_pos, obj->y_pos, ' ');
  mvaddch(obj->x_pos, ++obj->y_pos, obj->symbol | A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
}

void move_up(Object *obj, int border)
{
  if (obj->x_pos - 2 < border)
  {
    obj->flag_x = 1;
  }
  mvaddch(obj->x_pos, obj->y_pos, ' ');
  mvaddch(--obj->x_pos, obj->y_pos, obj->symbol | A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
}

void move_down(Object *obj, int border)
{
  if (obj->x_pos + 2 > border)
  {
    obj->flag_x = 0;
  }
  mvaddch(obj->x_pos, obj->y_pos, ' ');
  mvaddch(++obj->x_pos, obj->y_pos, obj->symbol | A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
}