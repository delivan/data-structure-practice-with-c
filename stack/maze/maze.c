#include "stackADT.h"
#include "maze.h"

#define MOVABLE 0       // moveable path
#define WALL 1          // not moveable path
#define VISITED 2       // visited once
#define BACKTRACKED 3   // backtracked path

int OFFSET[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};  // north, east, west, south
int **maze;
int size;       // size of maze

int main() {
    read_maze();
    Pos cur;
    cur.x = 0;
    cur.y = 0;
    int init_dir = 0, back_dir = 0;
    Stack pos_stack = create();
    while (1) {
        maze[cur.x][cur.y] = VISITED;
        if (cur.x == size-1 && cur.y == size-1) {
            printf("Found the path.\n");
            break;
        }
        bool forwarded = false;
        for (int dir = init_dir; dir < 4; dir++) { // north, east, west, south
            if (is_movable(cur, dir)) {
                push(pos_stack, dir);
                cur = move_to(cur, dir);
                forwarded = true;
                init_dir = 0;
                break;
            }
        }
        if (!forwarded) {
            if (is_empty(pos_stack)) {
                printf("No path exist.\n");
                break;
            }
            maze[cur.x][cur.y] = BACKTRACKED;
            back_dir = pop(pos_stack);
            cur = move_to(cur, (back_dir+2)%4);     // backtrack
            init_dir = back_dir + 1;
        }
    }
    print_maze();

    return 0;
}

void read_maze() {
    FILE *fp = fopen("test.txt", "r");
    fscanf(fp, "%d", &size);
    printf("size: %d\n", size);

    maze = (int **)malloc(size * sizeof(int *));
    for (int x = 0; x < size; x++) {
        maze[x] = (int *)malloc(size * sizeof(int));
        for (int y = 0; y < size; y++) {
            fscanf(fp, "%d", &maze[x][y]);
            printf("%d ",maze[x][y]);
        }
        printf("\n");
    }
    fclose(fp);
}

void print_maze() {
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            printf("%d ", maze[x][y]);
        }
        printf("\n");
        free(maze[x]);
    }
    free(maze);
}

bool is_movable(Pos cur, int dir) {
    Pos next;
    next.x = cur.x + OFFSET[dir][0];
    next.y = cur.y + OFFSET[dir][1];
    if (next.x == -1 || next.x == size || next.y == -1 || next.y == size)
        return false;

    bool movable = false;
    if (maze[next.x][next.y] == MOVABLE)
        movable = true;
    
    return movable;
}

Pos move_to(Pos cur, int dir) {
    Pos next;
    next.x = cur.x + OFFSET[dir][0];
    next.y = cur.y + OFFSET[dir][1];

    return next;
}
