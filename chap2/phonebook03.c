#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h>

#define INIT_CAPACITY 3
#define BUFFER_SIZE 20

/* global variables here */

char **names;                /* names */
char **numbers;              /* phone numbers */
int n = 0;                   /* number of people in phonebook */
int capacity = INIT_CAPACITY;
char delim[] = " ";

/* function prototypes here */

void init_directory();
int read_line(char str[], int limit);
void process_command();
void add(char *buf1, char *buf2);
void reallocate();
void find(char *buf);
void status();
void delete(char *buf);
void read(char *fileName);
void save(char *fileName);
int search(int *index, char *buf);

int main() {
    init_directory();       // create array names, numbers     
    process_command();      // handle command

    return 0;
}

void init_directory() {
    names = (char **)malloc(capacity * sizeof(char *));
    numbers = (char **)malloc(capacity * sizeof(char *));
}

int read_line(char str[], int limit) {
    int ch, i = 0;

    while ((ch = getchar()) != '\n')
        if (i < limit-1)
            str[i++] = ch;

    str[i] = '\0';

    return i;
}

void process_command() {
    char command_line[BUFFER_SIZE];
    char *command, *argument1, *argument2;

    while (1) {
        printf("$ ");
        if (read_line(command_line, BUFFER_SIZE)<=0)
            continue;

        command = strtok(command_line, delim);
        if (strcmp(command, "read") == 0) {
            argument1 = strtok(NULL, delim);
            if (argument1 == NULL) {
                printf("File name required.\n");
                continue;
            }
            read(argument1);
        } else if (strcmp(command, "add") == 0) {
            argument1 = strtok(NULL, delim);
            argument2 = strtok(NULL, delim);
            if (argument1 == NULL || argument2 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            add(argument1, argument2);
            printf("%s was added successfully.\n", argument1);
        } else if (strcmp(command, "find") == 0) {
            argument1 = strtok(NULL, delim);
            if (argument1 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            find(argument1);
        } else if (strcmp(command, "status") == 0) {
            status();
        } else if (strcmp(command, "delete") == 0) {
            argument1= strtok(NULL, delim);
            if (argument1 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            delete(argument1);
        } else if (strcmp(command, "save") == 0) {
            argument1 = strtok(NULL, delim);
            if (argument1 == NULL) {
                printf("Invalid argments.\n");
                continue;
            }
            save(argument1);
        } else if (strcmp(command, "exit") == 0)
            break;
    }
}
            
void add(char *buf1, char *buf2) {
    int i = n;
    
    if (n >= capacity) 
        reallocate();

    while ((i != 0) && (strcmp(buf1, names[i-1]) < 0)) {
        names[i] = names[i-1];
        numbers[i] = numbers[i-1];
        i--;
    }
    names[i] = strdup(buf1);
    numbers[i] = strdup(buf2);
    n++;
}

void reallocate() {
    capacity = capacity * 2;
    char **buf1 = (char **)malloc(capacity * sizeof(char *));
    char **buf2 = (char **)malloc(capacity * sizeof(char *));
    int i;

    for (i = 0; i < n; i++) {
        buf1[i] = strdup(names[i]);
        buf2[i] = strdup(numbers[i]);
    }
    free(names);
    free(numbers);
    names = buf1;
    numbers = buf2;
}

void find(char *buf) {
    int i, match = 0;
    int *index = (int *)malloc(sizeof(int)*n);
    
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

void delete(char *buf) {
    int i = 0, j, match = 0;
    int *index = (int *)malloc(sizeof(int)*n);

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

void read(char *fileName) {
    char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
    FILE *fp;

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("File open failed\n");
        return;
    }
    while (fscanf(fp, "%s %s", buf1, buf2) != EOF) 
        add(buf1, buf2);

    fclose(fp);
}

void save(char *fileName) {
    FILE *fp;
    int i;

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

