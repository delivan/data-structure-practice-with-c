#ifndef MAZE_H
#define MAZE_H

typedef struct position Pos;
struct position {
    int x, y;
};

void read_maze();
void print_maze();
bool is_movable(Pos cur, int dir);
Pos move_to(Pos cur, int dir);

#endif
