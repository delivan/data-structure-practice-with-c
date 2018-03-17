#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char * names[CAPACITY];     /* names */
char * numbers[CAPACITY];   /* phone numbers */
int n = 0;                  /* number of people in phonebook */

void add();
void find();
void status();
void delete();
void read();
void save();
int search(int *index, char *buf);

int main() {
    char command[BUFFER_SIZE];
   
    while (1) {
        printf("$ ");
        scanf("%s", command);
        if (strcmp(command, "add") == 0)
            add();
        else if (strcmp(command, "find") == 0)
            find();
        else if (strcmp(command, "status") == 0)
            status();
        else if (strcmp(command, "delete") == 0)
            delete();
        else if (strcmp(command, "read") == 0)
            read();
        else if (strcmp(command, "save") == 0)
            save();
        else if (strcmp(command, "exit") == 0)
            break;
    }

    return 0;
}

void add() {
    char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
    int i = n;

    scanf("%s", buf1);
    scanf("%s", buf2);


    while ((i != 0) && (strcmp(buf1, names[i-1]) < 0)) {
        names[i] = names[i-1];
        numbers[i] = numbers[i-1];
        i--;
    }
    names[i] = strdup(buf1);
    numbers[i] = strdup(buf2);
    n++;

    printf("%s was added successfully.\n", buf1);
}

void find() {
    int i, match = 0;
    int *index = (int *)malloc(sizeof(int)*n);
    char buf[BUFFER_SIZE];
    
    scanf("%s", buf);
    match = search(index, buf);
    for (i = 0; i < match; i++)  
        printf("%s\n", numbers[index[i]]);
    
    free(index);
}

void status() {
    int i;

    for (i = 0; i < n; i++)
        printf("%s %s\n", names[i], numbers[i]);
    printf("Total %d persons.\n", n);
}

void delete() {
    int i = 0, j, match = 0;
    int *index = (int *)malloc(sizeof(int)*n);
    char buf[BUFFER_SIZE];

    scanf("%s", buf);
    match = search(index, buf);
    if (match != 0) {
        for (i = index[0]; i < (n-match); i++) {
            names[i] = names[i+match];
            numbers[i] = numbers[i+match];
        }
        printf("%s was deleted successfully.\n", buf);
        n = n - match;
    }
}

void read() {
    char fileName[CAPACITY];
    char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
    FILE * fp;

    scanf("%s", fileName);
    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("File open failed\n");
        return;
    }
    while (fscanf(fp, "%s %s", buf1, buf2) != EOF) {
        names[n] = strdup(buf1);
        numbers[n] = strdup(buf2);
        n++;
    }
    fclose(fp);
}

void save() {
    char fileName[CAPACITY];
    FILE * fp;
    int i;

    scanf("%s", fileName);
    fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("File open failed\n");
        return;
    }
    for (i = 0; i < n; i++)
        fprintf(fp, "%s %s\n", names[i], numbers[i]);

    fclose(fp);
}

int search(int *index, char *buf) {
    int i, match = 0;

    for (i = 0; i < n; i++) {
        if (strcmp(names[i], buf) == 0) {
            index[match] = i;
            match++;
        }
    }
    if (match == 0)
        printf("No person names '%s' exists.\n", buf);

    return match;
}


