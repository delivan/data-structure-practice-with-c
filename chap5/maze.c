#include <stdlib.h>
#include "queueADT.h"
#include "maze.h"

#define MOVABLE 0       // moveable path
#define WALL 1          // not moveable path

int OFFSET[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};  // north, east, west, south
int **maze;
int size;       // size of maze

int main() {
    read_maze();
    Pos cur, next;
    cur.x = 0;
    cur.y = 0;
    next.x = 0;
    next.y = 0;
    int visited = -1;
    bool forwarded = false;
    Queue pos_queue = create();
    enqueue(pos_queue, cur);
    maze[cur.x][cur.y] = visited;
    while (1) {
        cur = dequeue(pos_queue);
        if (maze[cur.x][cur.y] <= visited)
            visited--;
        for (int dir = 0; dir < 4; dir++) { // north, east, west, south
            if (is_movable(cur, dir)) {
                next = move_to(cur, dir);
                enqueue(pos_queue, next);
                maze[next.x][next.y] = visited;
                forwarded = true;
            }
        }
        if (!forwarded) {
            if (is_empty(pos_queue)) {
                printf("No path exist.\n");
                break;
            }
        }
        forwarded = false;
        if (next.x == size-1 && next.y == size-1) {
            printf("Found the path.\n");
            break;
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
