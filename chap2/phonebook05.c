#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h>

#define INIT_CAPACITY 2
#define BUFFER_SIZE 50

/* global variables here */

typedef struct {
    char *name;
    char *phone_number;
    char *email;
    char *group;
} Person;

Person **directory;
int capacity;
int n;          // number of people in phone directory

/* function prototypes here */

void init();
int read_line(FILE *fp, char str[], int limit);
void process_command();
int compose_name(char str[]);
void reallocate();
void add(char *name, char *phone_number, char *email, char *group);
void handle_add(char *name);
void find(char *buf);
void status();
void delete(char *buf);
void read(char *file_name);
void save(char *file_name);
int search(int *index, char *buf);
void print_person(Person *p);

int main() {
    init();
    process_command();      // handle command

    return 0;
}

void init() {
    directory = (Person **)malloc(INIT_CAPACITY * sizeof(Person *));
    capacity = INIT_CAPACITY;
    n = 0;
}

int read_line(FILE *fp, char str[], int limit) {
    int ch, i = 0;

    while (((ch = fgetc(fp)) != '\n') && (ch != EOF))
        if (i < limit-1)
            str[i++] = ch;

    str[i] = '\0';

    return i;
}

void process_command() {
    char command_line[BUFFER_SIZE];
    char *command, *argument;
    char delim = ' ';
    char name_str[BUFFER_SIZE];

    while (1) {
        printf("$ ");
        if (read_line(stdin, command_line, BUFFER_SIZE)<=0)
            continue;

        command = strtok(command_line, &delim);
        if (strcmp(command, "read") == 0) {
            argument = strtok(NULL, &delim);
            if (argument == NULL) {
                printf("File name required.\n");
                continue;
            }
            read(argument);
        } else if (strcmp(command, "add") == 0) {
            if (compose_name(name_str) <= 0) { 
                printf("Invalid arguments.\n");
                continue;
            }
            handle_add(name_str);
        } else if (strcmp(command, "find") == 0) {
            if (compose_name(name_str) <= 0) { 
                printf("Invalid arguments.\n");
                continue;
            }
            find(name_str);
        } else if (strcmp(command, "status") == 0) {
            status();
        } else if (strcmp(command, "delete") == 0) {
            if (compose_name(name_str) <= 0) { 
                printf("Invalid arguments.\n");
                continue;
            }
            delete(name_str);
        } else if (strcmp(command, "save") == 0) {
            argument = strtok(NULL, &delim);
            if (argument == NULL) {
                printf("Invalid argments.\n");
                continue;
            }
            save(argument);
        } else if (strcmp(command, "exit") == 0)
            break;
    }
}

int compose_name(char str[]) {
    char *ptr;
    int length = 0;

    ptr = strtok(NULL, " ");
    if (ptr == NULL)
        return 0;
    
    strcpy(str, ptr);
    length += strlen(ptr);
    while ((ptr = strtok(NULL, " ")) != NULL) {
        str[length++] = ' ';
        str[length] = '\0';
        strcat(str, ptr);
        length += strlen(ptr);
    }
    return length;
}

void reallocate() {
    Person **tmp;
    int i;

    capacity = 2 * capacity;
    tmp = (Person **)malloc(capacity * sizeof(Person *));
    for (i = 0; i < n; i++)
        tmp[i] = directory[i];
    free(directory);
    directory = tmp;
}
            
void add(char *name, char *phone_number, char *email, char *group) {
    int i = n;
    
    if (n >= capacity)
        reallocate();
    
    /* insertion sort */
    while ((i > 0) && (strcmp(directory[i-1]->name, name) > 0)) {
        directory[i] = directory[i-1];
        i--;
    }

    directory[i] = (Person *)malloc(sizeof(Person));
    directory[i]->name = strdup(name);
    if (strcmp(phone_number, " ") == 0)
        directory[i]->phone_number = NULL;
    else
        directory[i]->phone_number = strdup(phone_number);
    if (strcmp(email, " ") == 0)
        directory[i]->email = NULL;
    else
        directory[i]->email = strdup(email);
    if (strcmp(group, " ") == 0)
        directory[i]->group = NULL;
    else
        directory[i]->group = strdup(group);
    n++;
}

void handle_add(char *name) {
    char phone_number[BUFFER_SIZE], email[BUFFER_SIZE], group[BUFFER_SIZE];
    char empty[] = " ";

    printf("  Phone Number: ");
    read_line(stdin, phone_number, BUFFER_SIZE);
    printf("  Email: ");
    read_line(stdin, email, BUFFER_SIZE);
    printf("  Group: ");
    read_line(stdin, group, BUFFER_SIZE);

    add(name, (char *)((strlen(phone_number) > 0) ? phone_number : empty)
            , (char *)((strlen(email) > 0) ? email : empty)
            , (char *)((strlen(group) > 0) ? group : empty));
}
void find(char *buf) {
    int i, match = 0;
    int *index = (int *)malloc(sizeof(int)*n);
    
    match = search(index, buf);
    for (i = 0; i < match; i++)  
        print_person(directory[index[i]]);
    
    free(index);
}

void status() {
    int i;

    for (i = 0; i < n; i++)
        print_person(directory[i]);

    printf("Total %d persons.\n", n);
}

void delete(char *buf) {
    Person *deleting_person;
    int i, match;
    int *index = (int *)malloc(n * sizeof(int));

    match = search(index, buf);
    if (match != 0) {
        for (i = 0; i < match; i++) {
            deleting_person = directory[index[i]];
            free(deleting_person->name);
            free(deleting_person->phone_number);
            free(deleting_person->email);
            free(deleting_person->group);
            free(deleting_person);
        }
        for (i = index[0]; i < (n-match); i++) 
            directory[i] = directory[i+match];
        
        n = n - match;
        printf("%s was deleted successfully.\n", buf);
    } else
        return;

}


void read(char *file_name) {
    char buf[BUFFER_SIZE];
    char *name, *phone_number, *email, *group;
    FILE *fp;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("File open failed\n");
        return;
    }
    while (1) {
        if (read_line(fp, buf, BUFFER_SIZE) <= 0)
            break;
        name = strtok(buf, "/");
        phone_number = strtok(NULL, "/");
        email = strtok(NULL, "/");
        group = strtok(NULL, "/");
        add(name, phone_number, email, group);
    }       
    fclose(fp);
}

void save(char *file_name) {
    int i;
    FILE *fp;

    fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("File open failed\n");
        return;
    }
    for (i = 0; i < n; i++) {
        fprintf(fp, "%s/", directory[i]->name);
        fprintf(fp, "%s/", directory[i]->phone_number);
        fprintf(fp, "%s/", directory[i]->email);
        fprintf(fp, "%s\n", directory[i]->group);
    }
    fclose(fp);
}

int search(int *index, char *buf) {
    int i, match = 0;

    for (i = 0; i < n; i++) {
        if (strcmp(directory[i]->name, buf) == 0) {
            index[match] = i;
            match++;
        }
    }
    if (match == 0)
        printf("No person name '%s' exists.\n", buf);

    return match;
}

void print_person(Person *p) {
    printf("%s:\n", p->name);
    printf("  Phone Number: %s\n", p->phone_number);
    printf("  Email: %s\n", p->email);
    printf("  Group: %s\n", p->group);
}
