#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <vingraph.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <math.h>

int main()
{
    ConnectGraph();
    tPoint dim;
    dim = GetDim(0);

    pid_t line_child = fork();
    if (line_child < 0){
        printf("Error: could not fork a child\n");
        return -1;
    }
    if (line_child == 0){
        int x = 0;
        int dx = 5;
        int line = Line(x, 10, x + 50, 50);
        while (1){
            MoveTo(x, 10, line);
            if (x < 0){
                dx = -dx;
            }
            if (x + 50 > dim.x){
                dx = -dx;
            }
            x += dx;
            usleep(1000000 / 60);
        }
    }

    pid_t poly_child = fork();
    if (poly_child < 0){
        printf("Error: could not fork a child\n");
        return -1;
    }
    if (poly_child == 0){
        int x = 30, y = 60, w = 30, h = 30;
        int dx = 5;
        tPoint polyline[] = {
                { x, y },
                { x, y + h },
                { x + w, y + h },
                { x, y }
        };
        int poly = Polyline(polyline, 4);
        while (1){
            MoveTo(x, y, poly);
            if (x < 0){
                dx = -dx;
            }
            if (x + w > dim.x){
                dx = -dx;
            }
            x += dx;
            usleep(1000000 / 60);
        }
    }

    pid_t rect_child = fork();
    if (rect_child < 0){
        printf("Error: could not fork a child\n");
        return -1;
    }
    if (rect_child == 0){
        int x = 50, y = 120;
        int dx = 5;
        int width = 100;
        int height = 50;
        int rect = Rect(x, y, width, height);
        while (1){
            MoveTo(x, y, rect);
            if (x < 0){
                dx = -dx;
            }
            if (x + width > dim.x){
                dx = -dx;
            }
            x += dx;
            usleep(1000000 / 60);
        }
    }

    pid_t ellipse_child = fork();
    if (ellipse_child < 0){
        printf("Error: could not fork a child\n");
        return -1;
    }
    if (ellipse_child == 0){
        int x = 90, y = 200;
        int dx = 5;
        int width = 100;
        int height = 50;
        int el = Ellipse(x, y, width, height);
        while (1){
            MoveTo(x, y, el);
            if (x < 0){
                dx = -dx;
            }
            if (x + width > dim.x){
                dx = -dx;
            }
            x += dx;
            usleep(1000000 / 60);
        }
    }

    pid_t grid_child = fork();
    if (grid_child < 0){
        printf("Error: could not fork a child\n");
        return -1;
    }
    if (grid_child == 0){
        int x = 0, y = 300;
        int dx = 5;
        int width = 150;
        int height = 100;
        int grid = Grid(x, y, width, height, 3, 2);
        while (1){
            MoveTo(x, y, grid);
            if (x < 0){
                dx = -dx;
            }
            if (x + width > dim.x){
                dx = -dx;
            }
            x += dx;
            usleep(1000000 / 60);
        }
    }

    pid_t nechto_child = fork();
    if (nechto_child < 0){
        printf("Error: could not fork a child\n");
        return -1;
    }
    if (nechto_child == 0){
        float x = 0, y = 300;
        int dx = 5;
        int width = 100;
        int height = 100;
        int nechto = Rect(x, y, width, height);
        int cx = dim.x / 2, cy = dim.y / 2;
        float rho, phi = 0, a = 100, b = 100;
        while (1){
            rho = a * cos(phi) + b;
            x = rho * cos(phi) + cx;
            y = rho * sin(phi) + cy;
            MoveTo(x, y, nechto);
            usleep(1000000 / 60);
            phi += 0.01;
        }
    }

    char c = InputChar();
    kill(line_child, SIGTERM);
    kill(poly_child, SIGTERM);
    kill(rect_child, SIGTERM);
    kill(ellipse_child, SIGTERM);
    kill(grid_child, SIGTERM);
    kill(nechto_child, SIGTERM);

    CloseGraph();
    return 0;
}